struct SequenceAndResult {
    int n_dice;
    string seq;
    ex result=0;
    bool operator<(const SequenceAndResult& o) {return result<o.result;}
};

SequenceAndResult best_sequence(const DieSequence& seq, int target, int reroll)  {
    SequenceAndResult best;
    for (int n=1;;++n) {
        SequenceAndResult r{n,seq.to_string(n),seq.roll_n_dice(n).reroll_blanks(reroll).result().chance_of_at_least(target)};
        if (r<best) return best;
        best=r;
    }
}
SequenceAndResult best_sequence(const AvailableDice& available_dice, int target, int reroll)  {
    list<SequenceAndResult> sequences_and_results;
    for (auto s: available_dice.sequences_without_white()) 
        sequences_and_results.push_back(best_sequence(s,target,reroll));
    auto best=max_element(sequences_and_results.begin(),sequences_and_results.end());
    return *best;
}