enum DieColor {WHITE=0, YELLOW=1, RED=2, BLACK=3};

DieColor& operator++(DieColor& die_color) {
    switch (die_color) {
    case WHITE:
        return die_color=DieColor::YELLOW;
    case YELLOW:
        return die_color=DieColor::RED;
    case RED:
        return die_color=DieColor::BLACK;
    case BLACK:
    default:
        throw logic_error("incrementing BLACK");
        return die_color;
    }    
}

ostream& operator<< (ostream& os, DieColor die_color) {
    switch (die_color) {
    case WHITE:
        os<<"W";break;
    case YELLOW:
        os<<"Y";break;
    case RED:
        os<<"R";break;
    case BLACK:
        os<<"B";break;
    }    
    return os;
}

class PadWithWhiteIterator {
    const vector<DieColor>& v;
    int i;
    PadWithWhiteIterator(const vector<DieColor>& v,    int i) : v{v},i{i} {}
public:
    PadWithWhiteIterator operator+(int n) {return PadWithWhiteIterator{v,i+n};}
    static PadWithWhiteIterator begin(const vector<DieColor>& v) {
        return PadWithWhiteIterator(v,0);
    }
    DieColor operator*() const {
        return i<v.size() ? v[i] : DieColor::WHITE;
    }
    PadWithWhiteIterator& operator++() {
        ++i;
        return *this;
    }
    bool operator!=(const PadWithWhiteIterator& o) const {
        return i!=o.i;
    }
};

template<>
struct std::iterator_traits<PadWithWhiteIterator> {
    using difference_type=int;
};

class DieSequence {
    vector<DieColor> decreasing_sequence;
    bool can_increase(int i) const { 
        return decreasing_sequence.size()<=i || 
            i==0 && decreasing_sequence[0]!=DieColor::BLACK ||
            i>0 && decreasing_sequence[i]<decreasing_sequence[i-1];
    }
    bool not_white(int i) const {
        return i<decreasing_sequence.size();    //trailing white dice are not inserted in the vector
    }
    DieSequence increase_at(int i) const {
        DieSequence result=*this;
        if (result.decreasing_sequence.size()<=i)
            result.decreasing_sequence.resize(i+1);
        ++result.decreasing_sequence[i];
        return result;
    }
    list<DieSequence> empower(int empower, int modify_from) const {
        if (empower==0) return {*this};
        list<DieSequence> with_modified;
        if (can_increase(modify_from)) 
            with_modified=increase_at(modify_from).empower(empower-1,modify_from);
        if (not_white(modify_from)) {
            auto with_unvaried = this->empower(empower,modify_from+1);
            with_modified.splice(with_modified.end(),with_unvaried);
        }
        return with_modified;
    }
public:
    DieSequence(int black, int red, int yellow) {
        decreasing_sequence.insert(decreasing_sequence.end(),black,DieColor::BLACK);
        decreasing_sequence.insert(decreasing_sequence.end(),red,DieColor::RED);
        decreasing_sequence.insert(decreasing_sequence.end(),yellow,DieColor::YELLOW);
    }
    list<DieSequence> empower(int empower) const {
        return this->empower(empower,0);
    }
    string to_string() const {
        stringstream s;
        for (auto x: decreasing_sequence) s<<x;
        return s.str();
    }
    string to_string(int n) const {
        stringstream s;
        auto begin = PadWithWhiteIterator::begin(decreasing_sequence);
        auto end = begin+n;
        s<<count(begin,end,DieColor::BLACK)<<",";
        s<<count(begin,end,DieColor::RED)<<",";
        s<<count(begin,end,DieColor::YELLOW)<<",";
        s<<count(begin,end,DieColor::WHITE);
//        for (auto i =PadWithWhiteIterator::begin(decreasing_sequence);i!=PadWithWhiteIterator::begin(decreasing_sequence)+n;++i)            s<<*i;
        return s.str();
    }
    Roll roll_n_dice(int n) const {
        auto begin = PadWithWhiteIterator::begin(decreasing_sequence);
        auto end = begin+n;
        return Roll{}
            .black(count(begin,end,DieColor::BLACK))
            .red(count(begin,end,DieColor::RED))
            .yellow(count(begin,end,DieColor::YELLOW))
            .white(count(begin,end,DieColor::WHITE));
    }
};

class AvailableDice {
    int empower_=0,yellow_=0,red_=0,black_=0;
public:
    AvailableDice yellow(int n) const {
        AvailableDice result=*this;
        result.yellow_+=n;
        return result;
    }
    AvailableDice red(int n) const {
        AvailableDice result=*this;
        result.red_+=n;
        return result;
    }
    AvailableDice black(int n) const {
        AvailableDice result=*this;
        result.black_+=n;
        return result;
    }
    AvailableDice empower(int n) const {
        AvailableDice result=*this;
        result.empower_+=n;
        return result;
    }
    list<DieSequence> sequences_without_white() const {
        auto sequence = DieSequence{black_,red_,yellow_};
        return sequence.empower(empower_);
    }
};

