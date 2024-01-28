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
    ex indet=realsymbol("x");
    Die white{indet,{blank,blank,1,1,2,{2,critical}},"white"};
    Die yellow{indet,{blank,blank,1,2,3,{3,critical}},"yellow"};
    Die red{indet,{blank,blank,2,3,3,{4,critical}},"red"};
    Die black{indet,{blank,blank,3,3,4,{5,critical}},"black"};
    exvector blank_indets() const {return {white.blank_indet(), yellow.blank_indet(), red.blank_indet(), black.blank_indet()};}
};

class RollResult {
    ex blank;
    ex indet;
    ex series;
    ex truncated_series(int order) const {
        auto x=series_to_poly(GiNaC::series(series,indet,order));
        x=x.collect(blank);
        return x.coeff(blank,0)+x.coeff(blank,1);  
    }
    static ex replace_indets(ex series, const exvector& blank_indets, ex blank) {
        lst subs;
        for (auto b: blank_indets) subs.append(b==blank);
        return series.subs(subs);
    }
public:
    RollResult(ex series,ex indet, const exvector& blank_indets) : blank{blank_indets.front()}, indet{indet}, series{replace_indets(series,blank_indets,blank)} {
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
        while (--n) {
            auto x=result.series_.collect(dice->white.blank_indet());
            cout<<"x "<<x<<endl;
            cout<<x.coeff(dice->white.blank_indet(),1)<<endl;
            cout<<x.coeff(dice->white.blank_indet(),2)<<endl;
        }
    }
    RollResult result() const {
        return RollResult{series_, dice->indet, dice->blank_indets()};
    }
};

