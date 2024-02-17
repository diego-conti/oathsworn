# oathsworn
A program to compute success probabilities when rolling dice in Oathsworn

# Usage:

There are currently four modes. Default mode is invoked by 

        ./oathsworn --white W --yellow Y --red R --black B --reroll K --bonus B --target T

and it gives the probabilty of obtaining T or more when rolling W white dice and so on, using up to K rerolls, with a +B bonus on the roll.

The 'advise' mode is invoked by

        ./oathsworn --yellow Y --red R --black B --reroll K --target T --empower E --bonus B --mode=advise

and it suggests optimal choice of dice to obtain T or more on a roll with empower E, R rerolls and a +B bonus where Y yellow dice and so on are available.

The 'success-chance-csv' mode is invoked by 

        ./oathsworn --yellow maxY --red maxR --black maxB --target maxTarget --reroll maxReroll --bonus maxBonus --mode=success-chance-csv

ant it prints a CSV where each line takes the form 
        
        B,R,Y,W,reroll,bonus,target,chance,chance_float

Each line indicates the chance of reaching a given target with the given dice, rerolls and bonus. The computation is run for all values of B,R,Y, empower, reroll, bonus between 0 and maxB, maxR, maxY, maxEmpower, maxReroll, maxBonus respectively. 

The 'advise-csv' mode is invoked by 

        ./oathsworn --yellow maxY --red maxR --black maxB --target maxTarget --reroll maxReroll --bonus maxBonus --mode=advise-csv [--success success_file]

ant it prints a CSV where each line takes the form 
        
        B,R,Y,reroll,empower,bonus,target, advisedB, advisedR, advisedY, advisedW

If success_file is specified, a csv in the same format as the one output by using '--mode=success-chance-csv' is written to the file, including the rolls used in the computation.

Each line indicates the optimal choice of dice to obtain a given target on a roll with B black dice, R red dice, Y yellow dice available, plus the given amount of empower, rerolls and bonus

The computation is run for all values of B,R,Y, empower, reroll, bonus between 0 and maxB, maxR, maxY, maxEmpower, maxReroll, maxBonus respectively. Similarly, target ranges between 1 and maxTarget (though in reversed order; this allows the program to reuse truncated series of higher degree)

# Notes

Results with two or more blanks are counted as zero, as they should be. In particular this implies that die rolls with a bonus require separate computation rather than subtracting the bonus from the target, e.g. rolling two blanks with a +3 bonus results in zero, not 3.

Blank reroll policy is only rerolling blanks, starting with most effective dice (i.e. black to white).


