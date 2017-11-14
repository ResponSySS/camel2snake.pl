# The case of camelCase

An UpperCamelCased or lowerCamelCased word is composed of atoms. The atom is either `[A-Z]` or `[A-Z][a-z]+` or `[0-9]+`.  
However you can't compose any word you want, there are composition rules:
1. first atom can't be a number
2. in lowerCamelCase, first atom must be lowercase

Examples:
* `a55Magnum` is valid (3 atoms)
* `A55Magnum` is valid (3 atoms)
* `55Magnum` is not valid
* `A55magnum` is not valid
* `aDoom3BFGGame` is valid (7 atoms)

## Matching pattern

To match [Cc]amelCase words, we can use the following regex pattern:

	<|    FIRST_ATOM    ||       ATOM       ||       ATOM       ||...|>
	<([A-Z]|[A-Z]?[a-z]+)([0-9]+|[A-Z][a-z]*)([0-9]+|[A-Z][a-z]*)(...)>

`[A-Z]|[A-Z]?[a-z]+` matches the unique first atom (FIRST_ATOM).  
`[0-9]+|[A-Z][a-z]*` matches remaining atoms (ATOM).

### Problem

It can match UPPERCASE words as well: the word `OUCH` can be considered as having 4 atoms!

### Revision

We thus have to consider adding a condition in order to prevent false positives such as `OUCH` or `RGB`. 
The arbitrary condition I've chosen is:
* the first atom must have lowercase letter(s)

It will then match `AnRGBV` but not `RGB`.

	<| FIRST_ATOM ||       ATOM       ||       ATOM       ||...|>
	<([A-Z]?[a-z]+)([0-9]+|[A-Z][a-z]*)([0-9]+|[A-Z][a-z]*)(...)>

`[A-Z]?[a-z]+`       matches a unique first atom with at least one lowercase letter (*FIRST_ATOM*).  
`[0-9]+|[A-Z][a-z]*` matches remaining atoms (*ATOM*).
