struct critical_tag {} critical;
struct blank_tag {} blank;

struct DieResult {
    int value;
    bool critical=false;
    DieResult(int value) : value{value} {}
    DieResult(int value, critical_tag) : value{value}, critical{true} {}
    DieResult(blank_tag) : DieResult{0} {}
};

class Die {
    ex blank_indet_;
    ex series_;
public:
    Die(ex x, std::initializer_list<DieResult> results, string name) : blank_indet_{realsymbol{name+"_blank"}} {
        ex noncritical_poly, critical_poly;
        for (auto result: results) {
            ex monomial=result.value? pow(x,result.value) : blank_indet_;
            if (result.critical) critical_poly+=monomial;
            else noncritical_poly+=monomial;
        }
        int faces=static_cast<int>(results.size());
        critical_poly/=faces;
        noncritical_poly/=faces;
        series_ = noncritical_poly/ (1-critical_poly);
    }
    ex blank_indet() const {return blank_indet_;}
    ex series() const {return series_;}
};

struct Dice {
    const ex indet=realsymbol("x");
    const vector<Die> dice {
        {indet,{blank,blank,1,1,2,{2,critical}},"white"},
        {indet,{blank,blank,1,2,3,{3,critical}},"yellow"},
        {indet,{blank,blank,2,3,3,{4,critical}},"red"},
        {indet,{blank,blank,3,3,4,{5,critical}},"black"}
    };
    const Die& white=dice[0];
    const Die& yellow=dice[1];
    const Die& red=dice[2];
    const Die& black=dice[3];
    exvector blank_indets() const {return {white.blank_indet(), yellow.blank_indet(), red.blank_indet(), black.blank_indet()};}
    auto begin() const {return dice.rbegin();}  //iterate from most to least effective die
    auto end() const {return dice.rend();}
};

class RollResult {
    ex indet;
    ex series;
    ex truncated_series(int order) const {                        
        return series_to_poly(GiNaC::series(series.expand(),indet,order));        
    }
    static ex replace_blank_indets(ex series, const exvector& blank_indets, ex blank) {
        lst subs;
        for (auto b: blank_indets) subs.append(b==blank);
        return series.subs(subs);
        
    }
    static ex replace_fails(ex series, ex blank, ex indet) {
        series=series.expand();
        ex success=(series.coeff(blank,0)+blank*series.coeff(blank,1)).expand();    //one or zero blanks
        ex fail=(series-success).expand();                                          //two blanks or more
        return (success+fail.subs(indet==1)).subs(blank==1);
    }
public:
    RollResult(ex series,ex indet, const exvector& blank_indets) :  indet{indet} {
        auto blank{blank_indets.front()};
        auto with_one_blank_indet=replace_blank_indets(series,blank_indets,blank);
        this->series=replace_fails(with_one_blank_indet,blank, indet);
    }
    ex chance_of_at_least(int k) const {
        return 1-chance_of_less_than(k);
    }
    ex chance_of_less_than(int k) const {
        return truncated_series(k).subs(indet==1);
    }
};

class Roll {
    ex series_=1;
    shared_ptr<Dice> dice=make_shared<Dice>();
    ex reroll_blank(ex series) const {
        series=series.expand();
        ex result;
        for (auto& die : *dice) {
            auto blank_indet=die.blank_indet();
            ex without_blank=series.subs(blank_indet==0);
            ex with_blank=series-without_blank;
            ex with_rerolled_blank=with_blank/blank_indet * die.series();
            result+=with_rerolled_blank;
            series=without_blank;
        }
        return result+series;
    }
public:
    Roll white(int n) const {
        Roll result=*this;
        result.series_*=pow(dice->white.series(),n);
        return result;
    }
    Roll yellow(int n) const {
        Roll result=*this;
        result.series_*=pow(dice->yellow.series(),n);
        return result;
    }
    Roll red(int n) const {
        Roll result=*this;
        result.series_*=pow(dice->red.series(),n);
        return result;
    }
    Roll black(int n) const {
        Roll result=*this;
        result.series_*=pow(dice->black.series(),n);
        return result;
    }
    Roll reroll_blanks(int n) const {
        Roll result=*this;
        while (n--) {
            result.series_=reroll_blank(result.series_);            
        }
        return result;
    }
    RollResult result() const {
        return RollResult{series_, dice->indet, dice->blank_indets()};
    }
};

