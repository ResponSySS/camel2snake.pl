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
# TODO: Use $INPLACE_EDIT
# How to copy files properly without line-per-line writing

use strict;
use warnings;

use Getopt::Long;

my $prog_name 	= "camel2snake.pl";
our $VERSION 	= "0.5";

my $files = "";
my $temp_suffix = ".c2c";
my $help = 0;
my $excl_patt = "";
my $in_place_suffix;
my $in_place_edit = 0;
my $force = 0;
my $show_params = 0;

# error message (string), return code (int)
sub fn_say {
	print( "$prog_name: ". shift() );
}
# error message (string), return code (int)
sub fn_say_err {
	print( STDERR "$prog_name: ". shift() );
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
	print( <<EOF );
FILES           $files
EXCLUSION PATT  $excl_patt
IN_PLACE_EDIT   $in_place_edit
IN_PLACE_SUFFIX $in_place_suffix
FORCE           $force
EOF
}

GetOptions ( 'x=s' => \$excl_patt, 'i:s' => \$in_place_suffix, 'f|force' => \$force, 'h|help' => \$help, 'hack' => \$show_params );

if ($show_params) {
	fn_showParams();
}
if ($help) {
	fn_help();
	exit;
}
no warnings 'uninitialized';
if (defined( $in_place_suffix )) {
	$in_place_edit = 1;
	if (length( $in_place_suffix )) {
		# will duplicate file to $file.$in_place_suffix
		fn_say_err( "SUFFIX IS: $in_place_suffix" );
		$temp_suffix = "";
	} else {
		# will duplicate file to $file.$temp_suffix
		$in_place_suffix = "";

	}
}
use warnings;
# FILE LOOPING AND REPLACING
{
	# WARNING : are you sure you want to edit these files?
	{
		my $files = "";
		foreach my $file (@ARGV) {
			$files .= "$file ";
		}
		fn_say_err( "You are about to edit the following files:\n\t$files\nContinue? [y/N] " );
		my $in = <STDIN>;
		chomp( $in );
		# it's actually also matching "yES" too but hey it's funny lmfao lol xD
		unless ($in =~ /[Yy](es|ES)?/) {
			fn_say_err( "not editing files - exiting" );
			exit;
		}
	}
	foreach my $file (@ARGV) {
		my $fh_in; my $fh_out;
		fn_say_err( "parsing $file\n" );
		open( $fh_in, "<", $file ) || fn_err( "can't open \"$file\"" );
		if ($in_place_edit) {
			open( $fh_out, ">", $file.$in_place_suffix.$temp_suffix ) || fn_err( "can't open \"$file.$in_place_suffix.$temp_suffix\" for writing" );
		}
		# 1. Copy file $file to $file.c2c or $file.$in_place_suffix
		while (my $line = <$fh_in>) {
			#$line =~ s/    [Ff][Aa][Mm]      /GUYS/x;
			if ($in_place_edit) { 	print( $fh_out $line );
			} else { 		print( STDOUT $line );
			}
		}
		# 2. Print to STDOUT or edit the $file.c2c or $file

		close( $fh_in );
		if ($in_place_edit) { close( $fh_out ); }
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
