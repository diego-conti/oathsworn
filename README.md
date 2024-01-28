# oathsworn
A program to compute success probabilities when rolling dice in Oathsworn

# Usage:

        ./oathsworn --white W --yellow Y --red R --black B --reroll K --target T
gives the probabilty of obtaining T or more when rolling W white dice and so on, using up to K rerolls. 

Double blanks are counted as zero.

Blank reroll policy is only rerolling blanks, starting with most effective dice (i.e. black to white).


