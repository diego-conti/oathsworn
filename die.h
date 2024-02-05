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
    mutable Series series;
    mutable map<int,ex> chance_of_less_than_;
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
    static Series series_with_zero_fails(ex series, ex indet, const exvector& blank_indets) {
        auto blank{blank_indets.front()};
        auto with_one_blank_indet=replace_blank_indets(series,blank_indets,blank);
        auto with_zeroed_fails=replace_fails(with_one_blank_indet,blank, indet).expand();
        return Series{with_zeroed_fails,indet};
    }
public:
    RollResult()=default;
    RollResult(ex series,ex indet, const exvector& blank_indets) :  indet{indet}, series{series_with_zero_fails(series,indet,blank_indets)} {
    }
    ex chance_of_at_least(int k) const {
        return 1-chance_of_less_than(k);
    }
    ex chance_of_less_than(int k) const {
        auto i=chance_of_less_than_.find(k);
        if (i!=chance_of_less_than_.end()) return i->second;
        else return chance_of_less_than_[k]=series.truncated_to_order(k).subs(indet==1);
    }
    int max_stored_target() const {
        return chance_of_less_than_.empty() ? 0 : chance_of_less_than_.rbegin()->first;
    }
};
