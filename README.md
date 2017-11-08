# camel2snake.sh
__WORK IN PROGRESS__
Convert all camelCase (or CamelCase) words to snake_case using `sed` (works great on C files).

## USAGE
	camel2snake.sh [OPTIONS] FILE

## OPTIONS
	-x PATTERNS 		PATTERNS is a colon-separated list of regex patterns; matching strings won't be altered
	-i[SUFFIX], --in-place[=SUFFIX]
				edit files in place, passed to `sed` as is, see `man sed`
	-f, --force 		force in-place editing
	-a FLAGS		pass FLAGS to `sed` as is
	-s			ignore lines containing \"printf\" and \"puts\" (workaround to avoid unwanted transformation of format strings)

## EXAMPLES

	$ camel2snake.sh -x "sf\w\+:\w\+_e" *.c *.h
test output, won't change lines containing strings like \"sfSpriteSize\" and \"enState_e\"

	$ camel2snake.sh -x "fn\w\+:s_\w\+:thatDankIntType" -i.ORIG program.c
make a backup of program.c to program.c.ORIG, change case while ignoring words like \"fnGameRender\", \"s_obj\" and \"thatDankIntType\"

## BUGS
Only problem is it pokes on formatting string such as "\nThis is" (which becomes \"\n_this_is\").
Check hardcoded quoted-strings in your code after running the script.

## AUTHOR
Written by Sylvain Saubier (<http://SystemicResponse.com>)

## REPORTING BUGS
Mail at: <feedback@systemicresponse.com>
