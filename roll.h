class Memory; 

class Roll {
    int black_=0, red_=0, yellow_=0, white_=0, reroll_=0;
    ex reroll_blank(ex series, const Dice& dice) const {
        series=series.expand();
        ex result;
        for (auto& die : dice) {
            auto blank_indet=die.blank_indet();
            ex without_blank=series.subs(blank_indet==0);
            ex with_blank=series-without_blank;
            ex with_rerolled_blank=with_blank/blank_indet * die.series();
            result+=with_rerolled_blank;
            series=without_blank;
        }
        return result+series;
    }
    static unique_ptr<Memory> memory;
public:
    Roll white(int n) const {
        Roll result=*this;
        result.white_+=n;
        return result;
    }
    Roll yellow(int n) const {
        Roll result=*this;
        result.yellow_+=n;
        return result;
    }
    Roll red(int n) const {
        Roll result=*this;
        result.red_+=n;
        return result;
    }
    Roll black(int n) const {
        Roll result=*this;
        result.black_+=n;
        return result;
    }
    Roll reroll_blanks(int n) const {
        Roll result=*this;
        result.reroll_+=n;
        return result;
    }
    unsigned int hash() const {return white_<<4 |yellow_<<4 | red_ <<4 |black_<<4 |reroll_;}    
     auto operator<=>(const Roll& rhs) const =default; 
    ex series(const Dice& dice) const {
        ex series=pow(dice.white.series(),white_)*pow(dice.yellow.series(),yellow_)*pow(dice.red.series(),red_)*pow(dice.black.series(),black_);
        for (int i=0;i<reroll_;++i)
            series=reroll_blank(series,dice);
        return series;
    }
    const RollResult& result() const;
};

class Memory {
    Dice dice;
    map<Roll,RollResult> memory;
public:
    const RollResult& get(const Roll& o) {
        auto i=memory.find(o);
        if (i==memory.end()) 
            return  memory[o]=RollResult{o.series(dice), dice.indet, dice.blank_indets()};
        else return i->second;
    }
};

 const RollResult& Roll::result() const {
    return memory->get(*this);
}

unique_ptr<Memory> Roll::memory =make_unique<Memory>();