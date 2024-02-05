# oathsworn
A program to compute success probabilities when rolling dice in Oathsworn

# Usage:

There are currently four modes. Default mode is invoked by 

        ./oathsworn --white W --yellow Y --red R --black B --reroll K --target T

and it gives the probabilty of obtaining T or more when rolling W white dice and so on, using up to K rerolls. 

The 'advise' mode is invoked by

        ./oathsworn --yellow Y --red R --black B --reroll K --target T --empower E --mode=advise

and it suggests optimal choice of dice to obtain T or more on a roll with empower E and R rerolls where Y yellow dice and so on are available.

The 'success-chance-csv' mode is invoked by 

        ./oathsworn --yellow maxY --red maxR --black maxB --target maxTarget --reroll maxReroll --mode=success-chance-csv

ant it prints a CSV where each line takes the form 
        
        B,R,Y,W,reroll,target,chance,chance_float

Each line indicates the chance of reaching a given target with the given dice and rerolls. The computation is run for all values of B,R,Y, empower, reroll between 0 and maxB, maxR, maxY, maxEmpower, maxReroll respectively. 

The 'advise-csv' mode is invoked by 

        ./oathsworn --yellow maxY --red maxR --black maxB --target maxTarget --reroll maxReroll --mode=advise-csv

ant it prints a CSV where each line takes the form 
        
        B,R,Y,reroll,empower,target, advisedB, advisedR, advisedY, advisedW

Each line indicates the optimal choice of dice to obtain a given target on a roll with B black dice, R red dice, Y yellow dice available, plus the given amount of empower and rerolls

The computation is run for all values of B,R,Y, empower, reroll between 0 and maxB, maxR, maxY, maxEmpower, maxReroll respectively. Similarly, target ranges between 1 and maxTarget (though in reversed order; this allows the program to reuse truncated series of higher degree)

# Notes

Results with two or more blanks are counted as zero, as they should be.

Blank reroll policy is only rerolling blanks, starting with most effective dice (i.e. black to white).


