# oathsworn
A program to compute success probabilities when rolling dice in Oathsworn

# Usage:

There are currently three modes. Default mode is invoked by 

        ./oathsworn --white W --yellow Y --red R --black B --reroll K --target T

and it gives the probabilty of obtaining T or more when rolling W white dice and so on, using up to K rerolls. 

The 'advise' mode is invoked by

        ./oathsworn --yellow Y --red R --black B --reroll K --target T --empower E --mode=advise

and it suggests optimal choice of dice to obtain T or more on a roll with empower E and R rerolls where Y yellow dice and so on are available.

The 'csv' mode is invoked by 

        ./oathsworn --yellow Y --red R --black B --mode=csv

ant it prints a CSV where each line takes the form 
        
        B,R,Y,reroll,empower,target,sequence,chance,chance_float

where B,R,Y are the command line parameters, which determine the available dice. Each line indicates the optimal choice of dice to obtain a given target on a roll with those available dice and the given amount of rerolls and the corresponding chance, as a fraction and a floating point number

# Notes

Results with two or more blanks are counted as zero, as they should be.

Blank reroll policy is only rerolling blanks, starting with most effective dice (i.e. black to white).


