# Better parsing with perl

PATTERN="(FIRST_ATOM)(ATOM)+"

/*
1. parse all lines in files
2. find matching strings, saves them
3. if a matching string matches an exclusion pattern, discard
4. change remaining strings to proper snake_case formatting
*/

if STRING match PATTERN 
		saves STRING

for W in WORDS ; do
	if STRING ! match W
		change STRING to
			if $8 exists
				=> \l$1_\l$2_\l$3_\l$4_\l$5_\l$6_\l$7_\l$8
			if $7 exists
				=> \l$1_\l$2_\l$3_\l$4_\l$5_\l$6_\l$7
			if $6 exists
				=> \l$1_\l$2_\l$3_\l$4_\l$5_\l$6
			if $5 exists
				=> \l$1_\l$2_\l$3_\l$4_\l$5
			if $4 exists
				=> \l$1_\l$2_\l$3_\l$4
			if $3 exists
				=> \l$1_\l$2_\l$3
