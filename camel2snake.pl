#!/usr/bin/env perl 
#===============================================================================
#
#          FILE: camel2snake.pl
# 
#         USAGE: ./camel2snake.pl 
# 
#   DESCRIPTION: Convert camelCase (or CamelCase!) to snake_case.
# 		(Works perfectly on C files)
# 
#       OPTIONS: ---
#  REQUIREMENTS: ---
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

use strict;
use warnings;

use Getopt::Long;

my $prog_name 	= "camel2snake.pl";
our $VERSION 	= "0.5";

my $files = "";
my $help = 0;
my $excl_patt = "";
my $inpl_suffix;
my $force = 0;
my $show_params = 0;

# error message (string), return code (int)
sub fn_say {
	print( "$prog_name: ". shift() );
}

# error message (string), return code (int)
sub fn_err {
	die( "$prog_name: ERROR: ". shift() );
}
# command to test (string)
sub fn_needCmd {
	my $cmd = shift();
	if (system( "command -v $cmd > /dev/null") != 0) {
		fn_err( "need $cmd (command not found)" );
	}
}
sub fn_help {
	print( <<EOF );
$prog_name $VERSION
    Convert all camelCase (or CamelCase) words (works great on C files).

USAGE
    $prog_name [OPTIONS] FILE

OPTIONS
    -x PATTERNS         PATTERNS is a '|'-separated list of regex patterns; 
                        matching strings won't be altered
    -i [SUFFIX]		edit files in place (makes backup if SUFFIX supplied)
    -f, --force         force in-place editing
    -h, --help          show this help message

BASE PATTERN
    The base regex pattern for matching [cC]amelCase words is:
        <  |-FIRST_ATOM-||-------ATOM-------||-------ATOM-------||...|  >
        \\b([A-Z]?[a-z]+)([0-9]+|[A-Z][a-z]*)([0-9]+|[A-Z][a-z]*)(...)\\b

EXAMPLES
    \$ $prog_name -x "sf\\w+|\\w+En" *.c *.h
        test output, won't change strings like "sfSpriteSize" and "stateEn"
    \$ $prog_name -x "fn\\w+|st\\w+|thatDankIntType" -i.ORIG program.c
        make a backup of program.c to program.c.ORIG, change case while ignoring words like "fnGameRender", "stObj" and "thatDankIntType"

BUGS
    Only problem is it pokes on formatting string such as "\\nThis is" (which becomes "\\n_this is").

AUTHOR
    Written by Sylvain Saubier (<http://SystemicResponse.com>)

REPORTING BUGS
    Mail at: <feedback\@systemicresponse.com>
EOF
}

sub fn_showParams {
	my $inpl_edit = 0;
	no warnings 'uninitialized';
	if (defined( $inpl_suffix )) { $inpl_edit = 1; }
	print( <<EOF );
FILES           $files
EXCLUSION PATT  $excl_patt
IN_PLACE_EDIT   $inpl_edit
IN_PLACE_SUFFIX $inpl_suffix
FORCE           $force
EOF
	use warnings;
}

GetOptions ( 'x=s' => \$excl_patt, 'i:s' => \$inpl_suffix, 'f|force' => \$force, 'h|help' => \$help, 'hack' => \$show_params );

if ($show_params) {
	fn_showParams();
}
if ($help) {
	fn_help();
	exit;
}
if (defined( $inpl_suffix )) {
	if (length( $inpl_suffix )) {
		;
	}
}
{
	my $arg;
	while ($arg = shift()) {
		print( "ARGS =".$arg );
	}
}

# How do you handle files?
#if test -z "$files"; then
#	fn_err "no FILE argument provided (see --help)" 10
#fi

# SED
# Generate list of excluded words
#if test -n "$excl_patt"; then
# 	fn_createTmpDir "$tmp_dir_patt"
# 	F_PATT_LIST="$dir_tmp/list.tmp"
# 	F_PATT_LIST_SORT="$dir_tmp/list"
# 	EXCL_PATT_LIST="$(echo $excl_patt | tr ':' ' ')"
# 	if test -z "$excl_patt_list"; then
# 		fn_err "$excl_patt: wrong exclusion pattern" 4
# 	fi
# 	echo > "$f_patt_list"
# 	for i in $excl_patt_list; do
# 		sed -n "s/.*\b\(${i}\)\b.*/\1/p" $files >> "$f_patt_list"
# 	done
# 	cat "$f_patt_list" | sort | uniq > "$f_patt_list_sort"
# 	# F_PATT_LIST_SORT will contain original text, F_PATT_LIST will contain transformed text
# 	cp "$f_patt_list_sort" "$f_patt_list"
# 	FILES="$files $f_patt_list"
#fi

#if test -n "$excl_patt"; then
#	EXCL_PATT="(?!$excl_patt)"
#fi

# PERL
#FIRST_ATOM="[A-Z]?[a-z]+"
#ATOM="[A-Z][a-z]*|[0-9]+"
#BOUND="(?!.*[\'\"].*)"
#EXCL_LKHD="(?!sf|\w+En|intThatType)"

#echo -en "SAMPLE OUTPUT:\n\t"
#cat << EOF
#perl $perl_flags 's/$bound \b $excl_lkhd ($first_atom)($atom) \b$bound	/\l\1_\l\2/ xg ;
#EOF
#if test $force -eq 0 && test $in_place_edit -eq 1; then
#	fn_say "$prog_name: will now edit the following files:\ $files.\nPress CTRL+C to abort, ENTER to continue." && read
#fi

#perl ${perl_flags} '\
# 	$bound="(?!.*["].*)" 											;\
# 	$excl_lkhd="(?!sf|\w+En|intThatType)" 									;\
# 	$first_atom="[A-Z]?[a-z]+" 										;\
# 	$atom="[A-Z][a-z]*|[0-9]+"  										;\
# 	s/$bound \b $excl_lkhd ($first_atom)($atom) 						\b$bound	/\l$1_\l$2/ 					xg ;\
# 	s/$bound \b $excl_lkhd ($first_atom)($atom)($atom) 					\b$bound 	/\l$1_\l$2_\l$3/ 				xg ;\
# 	s/$bound \b $excl_lkhd ($first_atom)($atom)($atom)($atom)				\b$bound 	/\l$1_\l$2_\l$3_\l$4/ 				xg ;\
# 	s/$bound \b $excl_lkhd ($first_atom)($atom)($atom)($atom)($atom)			\b$bound 	/\l$1_\l$2_\l$3_\l$4_\l$5/ 			xg ;\
# 	s/$bound \b $excl_lkhd ($first_atom)($atom)($atom)($atom)($atom)($atom)			\b$bound 	/\l$1_\l$2_\l$3_\l$4_\l$5_\l$6/			xg ;\
# 	s/$bound \b $excl_lkhd ($first_atom)($atom)($atom)($atom)($atom)($atom)($atom)		\b$bound 	/\l$1_\l$2_\l$3_\l$4_\l$5_\l$6_\l$7/		xg ;\
# 	s/$bound \b $excl_lkhd ($first_atom)($atom)($atom)($atom)($atom)($atom)($atom)($atom)	\b$bound 	/\l$1_\l$2_\l$3_\l$4_\l$5_\l$6_\l$7_\l$8/	xg ;\
# 	' ${files}
