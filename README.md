# camel2snake.pl 0.5
__WORK IN PROGRESS__  
Convert all camelCase (or CamelCase) words (works great on C files).

## USAGE
    camel2snake.pl [OPTIONS] FILE

## OPTIONS
    -x PATTERNS         PATTERNS is a '|'-separated list of regex patterns; matching strings won't be altered
    -i [SUFFIX]         edit files in place (makes backup if SUFFIX supplied), passed to `perl` as is (see `man perlre` and `man perleretut`)
    -f, --force         force in-place editing
    -h, --help          show this help message

## BASE PATTERN
The base regex pattern for matching [cC]amelCase words is:
	<  |-FIRST_ATOM-||-------ATOM-------||-------ATOM-------||...|  >
	 \b([A-Z]?[a-z]+)([0-9]+|[A-Z][a-z]*)([0-9]+|[A-Z][a-z]*)(...)\b

## EXAMPLES
	$ camel2snake.pl -x "sf\w+|\w+En" *.c *.h
test output, won't change strings like "sfSpriteSize" and "stateEn"

	$ camel2snake.pl -x "fn\w+|st\w+|thatDankIntType" -i.ORIG program.c
make a backup of program.c to program.c.ORIG, change case while ignoring words like "fnGameRender", "stObj" and "thatDankIntType"

## BUGS
Only problem is it pokes on formatting string such as "\nThis is" (which becomes "\n_this is").

## AUTHOR
Written by Sylvain Saubier (<http://SystemicResponse.com>)

## REPORTING BUGS
Mail at: <feedback@systemicresponse.com>
