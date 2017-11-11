#!/bin/bash - 
#===============================================================================
#
#          FILE: camel2snake.sh
# 
#         USAGE: ./camel2snake.sh 
# 
#   DESCRIPTION: Convert camelCase (or CamelCase!) to snake_case.
# 		(Works perfectly on C files)
# 
#       OPTIONS: ---
#  REQUIREMENTS: perl
#          BUGS: ---
#         NOTES: ---
#        AUTHOR: Sylvain S. (ResponSyS), mail@systemicresponse.com
#  ORGANIZATION: 
#       CREATED: 11/07/2017 15:47
#      REVISION:  ---
#===============================================================================

#TODO ::: Tue 07 Nov 2017 08:05:47 PM CET
# * EXCLUSION PATTERNS
# 	* -x PATTERN : ignore words matching PATTERN
# 	* ignore strings preceded by \n, \t, \a, \b, \f, \v, \xHH, \e, \uHHH, \uHHH
# 		like \nthisVarHere or \tthatParam
# 	* OR just ignore strings between quotes
# TODO: convert this to a perl script

set -o nounset
set -o errexit

PROGRAM_NAME="camel2snake.sh"
PROGRAM_VER="0.5"

FMT_BOLD='\e[1m'
FMT_UNDERL='\e[4m'
FMT_OFF='\e[0m'

TMP_DIR_PATT="c2s.XXX"
F_PATT_LIST=""
F_PATT_LIST_SORT=""

FILES=""
PERL_FLAGS="-npe"
EXCL_PATT=""
IN_PLACE_EDIT=0
FORCE=0
IGNORE_PRINTF=0
SHOW_PARAMS=0

# path to dir (string)
m_checkDir() {
	test -d "$1"
}
# template for temp dir name (string), optional: set TMP_DIR (string)
fn_createTmpDir() {
	TMP_DIR=${TMP_DIR:-/tmp}                          # Defaults to /tmp if unset 
	m_checkDir "$TMP_DIR" || fn_err "$TMP_DIR is not a directory or is weird" 100

	# Make full path to actual temp dir
	DIR_TMP="${TMP_DIR}/${1}"

	#-------------------------------------------------------------------------------
	# Creates a particular temporary directory inside $TMP_DIR.
	#-------------------------------------------------------------------------------
	DIR_TMP="`mktemp -d "$DIR_TMP"`" || fn_err "ERROR creating a temporary file" $ERR_WRONG_TMP_DIR

	#-------------------------------------------------------------------------------
	# When the program exits, it tries to remove the temporary folder.
	# This code is executed even if the process receives a signal 1,2,3 or 15.
	#-------------------------------------------------------------------------------
    trap '[ "$DIR_TMP" ] && rm -rf --verbose "$DIR_TMP"' 0

    #touch $TEMPORARY_DIR/tempfile                   # new tempfile inside folder
    DIR_TMP_CREATED=1
}
# message (string)
m_say() {
	echo -e "$PROGRAM_NAME: $1"
}
# error message (string), return code (int)
fn_err() {
	m_say "${FMT_BOLD}ERROR${FMT_OFF}: $1" >&2
	exit $2
}
# command to test (string)
fn_needCmd() {
if ! command -v "$1" > /dev/null 2>&1
	then fn_err "need '$1' (command not found)" 60
fi
}
fn_help() {
	cat << EOF
$PROGRAM_NAME $PROGRAM_VER
    Convert all camelCase (or CamelCase) words to snake_case using \`perl\` (works great on C files).

USAGE
    $PROGRAM_NAME [OPTIONS] FILE

OPTIONS
    -x PATTERNS         PATTERNS is a '|'-separated list of regex patterns; matching strings won't be altered
    -i[SUFFIX]		edit files in place (makes backup if SUFFIX supplied), passed to \`perl\` as is (see \`man perlre\` and \`man perleretut\`)
    -f, --force         force in-place editing
    -a FLAGS            pass FLAGS to \`perl\` as is

EXAMPLES
    $ $PROGRAM_NAME -x "sf\w+|\w+En" *.c *.h
        test output, won't change strings like \"sfSpriteSize\" and \"stateEn\"
    $ $PROGRAM_NAME -x "fn\w+|st\w+|thatDankIntType" -i.ORIG program.c
        make a backup of program.c to program.c.ORIG, change case while ignoring words like \"fnGameRender\", \"stObj\" and \"thatDankIntType\"

BUGS
    Only problem is it pokes on formatting string such as "\nThis is" (which becomes \"\n_this is\").

AUTHOR
    Written by Sylvain Saubier (<http://SystemicResponse.com>)

REPORTING BUGS
    Mail at: <feedback@systemicresponse.com>
EOF
}

fn_showParams() {
	printf "\
FILES            %s \n\
PERL_FLAGS       %s \n\
IN_PLACE_EDIT    %s \n\
FORCE            %s \n\
" "$FILES" "$PERL_FLAGS" $IN_PLACE_EDIT $FORCE
}

fn_needCmd "perl"
fn_needCmd "sort"
fn_needCmd "uniq"

# Arguments parsing
while test $# -ge 1; do
	case "$1" in
		"--help"|"-h")
			fn_help
			exit
			;;
		"-x")
			EXCL_PATT="$2"
			shift
			;;
		"-i"*|"--in-place="*)
			PERL_FLAGS="$PERL_FLAGS $1"
			IN_PLACE_EDIT=1
			;;
		"-a")
			PERL_FLAGS="$PERL_FLAGS $2"
			shift
			;;
		"-f"|"--force")
			FORCE=1
			;;
		"--show-params")
			SHOW_PARAMS=1
			;;
		*)
			FILES="$FILES $1"
			;;
	esac	# --- end of case ---
	# Delete $1
	shift
done

if test -z "$FILES"; then
	fn_err "no FILE argument provided (see --help)" 10
fi

# SED
# Generate list of excluded words
#if test -n "$EXCL_PATT"; then
# 	fn_createTmpDir "$TMP_DIR_PATT"
# 	F_PATT_LIST="$DIR_TMP/list.tmp"
# 	F_PATT_LIST_SORT="$DIR_TMP/list"
# 	EXCL_PATT_LIST="$(echo $EXCL_PATT | tr ':' ' ')"
# 	if test -z "$EXCL_PATT_LIST"; then
# 		fn_err "$EXCL_PATT: wrong exclusion pattern" 4
# 	fi
# 	echo > "$F_PATT_LIST"
# 	for i in $EXCL_PATT_LIST; do
# 		sed -n "s/.*\b\(${i}\)\b.*/\1/p" $FILES >> "$F_PATT_LIST"
# 	done
# 	cat "$F_PATT_LIST" | sort | uniq > "$F_PATT_LIST_SORT"
# 	# F_PATT_LIST_SORT will contain original text, F_PATT_LIST will contain transformed text
# 	cp "$F_PATT_LIST_SORT" "$F_PATT_LIST"
# 	FILES="$FILES $F_PATT_LIST"
#fi
if test -n "$EXCL_PATT"; then
	EXCL_PATT="(?!$EXCL_PATT)"
fi
if test $SHOW_PARAMS -eq 1; then
	fn_showParams
fi

# PERL
FIRST_ATOM="[A-Z]?[a-z]+"
ATOM="[A-Z][a-z]*|[0-9]+"
BOUND="(?!.*[\'\"].*)"
EXCL_LKHD="(?!sf|\w+En|intThatType)"

echo -en "SAMPLE OUTPUT:\n\t"
cat << EOF
perl $PERL_FLAGS 's/$BOUND \b $EXCL_LKHD ($FIRST_ATOM)($ATOM) \b$BOUND	/\l\1_\l\2/ xg ;
EOF
if test $FORCE -eq 0 && test $IN_PLACE_EDIT -eq 1; then
	m_say "$PROGRAM_NAME will now edit the following files:\ $FILES.\nPress CTRL+C to abort, ENTER to continue." && read
fi

perl ${PERL_FLAGS} '\
	$BOUND="(?!.*["].*)" 											;\
	$EXCL_LKHD="(?!sf|\w+En|intThatType)" 									;\
	$FIRST_ATOM="[A-Z]?[a-z]+" 										;\
	$ATOM="[A-Z][a-z]*|[0-9]+"  										;\
	s/$BOUND \b $EXCL_LKHD ($FIRST_ATOM)($ATOM) 						\b$BOUND	/\l$1_\l$2/ 					xg ;\
 	s/$BOUND \b $EXCL_LKHD ($FIRST_ATOM)($ATOM)($ATOM) 					\b$BOUND 	/\l$1_\l$2_\l$3/ 				xg ;\
 	s/$BOUND \b $EXCL_LKHD ($FIRST_ATOM)($ATOM)($ATOM)($ATOM)				\b$BOUND 	/\l$1_\l$2_\l$3_\l$4/ 				xg ;\
 	s/$BOUND \b $EXCL_LKHD ($FIRST_ATOM)($ATOM)($ATOM)($ATOM)($ATOM)			\b$BOUND 	/\l$1_\l$2_\l$3_\l$4_\l$5/ 			xg ;\
 	s/$BOUND \b $EXCL_LKHD ($FIRST_ATOM)($ATOM)($ATOM)($ATOM)($ATOM)($ATOM)			\b$BOUND 	/\l$1_\l$2_\l$3_\l$4_\l$5_\l$6/			xg ;\
 	s/$BOUND \b $EXCL_LKHD ($FIRST_ATOM)($ATOM)($ATOM)($ATOM)($ATOM)($ATOM)($ATOM)		\b$BOUND 	/\l$1_\l$2_\l$3_\l$4_\l$5_\l$6_\l$7/		xg ;\
 	s/$BOUND \b $EXCL_LKHD ($FIRST_ATOM)($ATOM)($ATOM)($ATOM)($ATOM)($ATOM)($ATOM)($ATOM)	\b$BOUND 	/\l$1_\l$2_\l$3_\l$4_\l$5_\l$6_\l$7_\l$8/	xg ;\
	' ${FILES}
