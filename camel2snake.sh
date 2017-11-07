#!/bin/bash - 
#===============================================================================
#
#          FILE: camel2snake.sh
# 
#         USAGE: ./camel2snake.sh 
# 
#   DESCRIPTION: Convert camelCase (or CamelCase!) to snake_case.
# 		(Only tested on C files)
# 
#       OPTIONS: ---
#  REQUIREMENTS: sed
#          BUGS: ---
#         NOTES: ---
#        AUTHOR: Sylvain S. (ResponSyS), mail@systemicresponse.com
#  ORGANIZATION: 
#       CREATED: 11/07/2017 15:47
#      REVISION:  ---
#===============================================================================

#TODO ::: Tue 07 Nov 2017 08:05:47 PM CET
# * figure out general rules for flawless C file parsing (ignore keywords, etc.)
# * ADD AN OPTION:
# 	* -x PATTERN to ignore words starting or ending with PATTERN


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
SED_FLAGS_BASE="-n"
SED_FLAGS=""
SED_CMD="gp"
EXCL_PATT=""
EXCL_PATT_LIST=""
IN_PLACE_EDIT=0
FORCE=0
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
    Convert all camelCase (or CamelCase) words to snake_case using \`sed\` (only tested on C files).

USAGE
    $PROGRAM_NAME [OPTIONS] FILE

OPTIONS
    -x PATTERNS         PATTERNS is a colon-separated list of regex patterns; matching strings won't be altered
    -i[SUFFIX], --in-place[=SUFFIX]
                        edit files in place, passed to \`sed\` as is, see \`man sed\`
    -f, --force         force in-place editing
    -a FLAGS            pass FLAGS to \`sed\` as is

EXAMPLE
    $ $PROGRAM_NAME -x "sf\w\+:\w\+_e" *.c *.h
        test output, won't change lines containing strings like \"sfSpriteSize\" or \"enState_e\"
    $ $PROGRAM_NAME -x "fn\w\+:s_\w\+" -i.ORIG program.c
        make a backup of program.c to program.c.ORIG, change case while ignoring words like \"fnGameRender\" or \"s_obj\"

AUTHOR
    Written by Sylvain Saubier (<http://SystemicResponse.com>)

REPORTING BUGS
    Mail at: <feedback@systemicresponse.com>
EOF
}

fn_showParams() {
	printf "\
FILES            %s \n\
EXCL_PATT_LIST   %s \n\
SED_CMD          %s \n\
SED_FLAGS_BASE   %s \n\
SED_FLAGS        %s \n\
IN_PLACE_EDIT    %s \n\
FORCE            %s \n\
" "$FILES" "$EXCL_PATT_LIST" $SED_CMD $SED_FLAGS_BASE "$SED_FLAGS" $IN_PLACE_EDIT $FORCE
}

fn_needCmd "sed"
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
			SED_CMD="g"
			SED_FLAGS_BASE="$1"
			IN_PLACE_EDIT=1
			;;
		"-a")
			SED_FLAGS="$SED_FLAGS $2"
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

# Generate list of excluded words
if test -n "$EXCL_PATT"; then
	fn_createTmpDir "$TMP_DIR_PATT"
	F_PATT_LIST="$DIR_TMP/list.tmp"
	F_PATT_LIST_SORT="$DIR_TMP/list"
	EXCL_PATT_LIST="$(echo $EXCL_PATT | tr ':' ' ')"
	if test -z "$EXCL_PATT_LIST"; then
		fn_err "$EXCL_PATT: wrong exclusion pattern" 4
	fi
	echo "" > "$F_PATT_LIST"
	for i in $EXCL_PATT_LIST; do
		m_say "treating ${i}"
		sed -n "s/.*\b\(${i}\)\b.*/\1/p" $FILES >> "$F_PATT_LIST"
	done
	cat "$F_PATT_LIST" | sort | uniq > "$F_PATT_LIST_SORT"
fi

if test $FORCE -eq 0 && test $IN_PLACE_EDIT -eq 1; then
	echo WARNING NOOOOOOOOOOOOO && exit
fi

if test $SHOW_PARAMS -eq 1; then
	fn_showParams
	test -f "$F_PATT_LIST_SORT" && less "$F_PATT_LIST_SORT"
fi

# "[^\\]" avoid matching format string in C such as "\nthisVar" which would turn it in "\n_this_var"

echo -en "SAMPLE OUTPUT:\n\t"
cat << EOF
sed "s/[^\\]\b\([A-Z]\?[a-z]\+\)\([A-Z][a-z]*\)\b/\l\1_\l\2/ ${SED_CMD}"  		$FILES $SED_FLAGS_BASE $SED_FLAGS
EOF
exit

sed "s/[^\\]\b\([A-Z]\?[a-z]\+\)\([A-Z][a-z]*\)\b/\l\1_\l\2/ 											${SED_CMD}" $FILES ${SED_FLAGS_BASE} ${SED_FLAGS}
sed "s/[^\\]\b\([A-Z]\?[a-z]\+\)\([A-Z][a-z]*\)\([A-Z][a-z]*\)\b/\l\1_\l\2_\l\3/ 								${SED_CMD}" $FILES ${SED_FLAGS_BASE} ${SED_FLAGS}
sed "s/[^\\]\b\([A-Z]\?[a-z]\+\)\([A-Z][a-z]*\)\([A-Z][a-z]*\)\([A-Z][a-z]*\)\b/\l\1_\l\2_\l\3_\l\4/  						${SED_CMD}" $FILES ${SED_FLAGS_BASE} ${SED_FLAGS}
sed "s/[^\\]\b\([A-Z]\?[a-z]\+\)\([A-Z][a-z]*\)\([A-Z][a-z]*\)\([A-Z][a-z]*\)\([A-Z][a-z]*\)\b/\l\1_\l\2_\l\3_\l\4_\l\5/  			${SED_CMD}" $FILES ${SED_FLAGS_BASE} ${SED_FLAGS}
sed "s/[^\\]\b\([A-Z]\?[a-z]\+\)\([A-Z][a-z]*\)\([A-Z][a-z]*\)\([A-Z][a-z]*\)\([A-Z][a-z]*\)\([A-Z][a-z]*\)\b/\l\1_\l\2_\l\3_\l\4_\l\5_\l\6/  	${SED_CMD}" $FILES ${SED_FLAGS_BASE} ${SED_FLAGS}
