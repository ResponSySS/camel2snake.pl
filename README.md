# camel2snake.pl 0.8
Convert all camelCase (or CamelCase) words to snake_case (works great on C files).

## USAGE
    ./camel2snake.pl [OPTIONS] FILE

## OPTIONS
    -x PATTERNS         PATTERNS is a '|'-separated list of regex patterns; 
                        matching strings won't be altered
    -i [SUFFIX]         edit files in place (makes backup if SUFFIX supplied)
    -f, --force         force in-place editing
    -h, --help          show this help message

## BASE PATTERN
The base regex pattern for matching [cC]amelCase words is:

        < |-FIRST_ATOM-||-------ATOM-------||-------ATOM-------||...|  >
        \b([A-Z]?[a-z]+)([0-9]+|[A-Z][a-z]*)([0-9]+|[A-Z][a-z]*)(...)\b

## EXAMPLES
    $ ./camel2snake.pl -x "\bsf\w+|\w+En\b" *.c *.h
change case and send result to standard output, won't change strings like 
"sfSpriteSize" and "stateEn".

    $ ./camel2snake.pl -x '\bfn\w+|\bst\w+|thatDankIntType' -i=.ORIG program.c
make a backup of program.c to program.c.ORIG, prompt then change case in 
the file while ignoring words like "fnGameRender", "stObj" and "thatDankIntType".

    $ ./camel2snake.pl -f -i .old program.c
make a backup of program.c to program.c.old, change case in the file without 
prompting.

## BUGS
Only problem is it pokes on formatting string such as "\nThis is" (which becomes 
"\n_this is"). As a workaround, camel2snake.pl does not impact quoted strings (i.e. 
strings found between two " or ' quotes *on the same line*).

## AUTHOR
Written by Sylvain Saubier (<http://SystemicResponse.com>)

## REPORTING BUGS
Mail at: <feedback@systemicresponse.com>
