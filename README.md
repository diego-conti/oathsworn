# oathsworn
A program to compute success probabilities when rolling dice in Oathsworn

# Usage:

There are currently two modes. Default mode is invoked by 

        ./oathsworn --white W --yellow Y --red R --black B --reroll K --target T

and it gives the probabilty of obtaining T or more when rolling W white dice and so on, using up to K rerolls. 

The 'advise' mode is invoked by

        ./oathsworn --yellow Y --red R --black B --reroll K --target T --empower E --mode=advise

and it suggests optimal choice of dice to obtain T or more on a roll with empower E and R rerolls where Y yellow dice and so on are available.

Double blanks are counted as zero.

Blank reroll policy is only rerolling blanks, starting with most effective dice (i.e. black to white).


