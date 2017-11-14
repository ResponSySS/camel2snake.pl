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

# TODO: MORE AND MORE TESTING
# TODO: Use $INPLACE_EDIT

use strict;
use warnings;

use Getopt::Long;
use File::Copy;

my $prog_name 	= "camel2snake.pl";
our $VERSION 	= "0.8";

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
	die( "$prog_name: ERROR: ". shift() ."\n");
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
    Convert all camelCase (or CamelCase) words to snake_case (works great on C files).

USAGE
    ./$prog_name [OPTIONS] FILE

OPTIONS
    -x PATTERNS         PATTERNS is a '|'-separated list of regex patterns; 
                        matching strings won't be altered
    -i [SUFFIX]         edit files in place (makes backup if SUFFIX supplied)
    -f, --force         force in-place editing
    -h, --help          show this help message

BASE PATTERN
    The base regex pattern for matching [cC]amelCase words is:
        < |-FIRST_ATOM-||-------ATOM-------||-------ATOM-------||...|  >
        \\b([A-Z]?[a-z]+)([0-9]+|[A-Z][a-z]*)([0-9]+|[A-Z][a-z]*)(...)\\b

EXAMPLES
    \$ ./$prog_name -x "\\bsf\\w+|\\w+En\\b" *.c *.h
        change case and send result to standard output, won't change strings like 
        "sfSpriteSize" and "stateEn".
    \$ ./$prog_name -x '\\bfn\\w+|\\bst\\w+|thatDankIntType' -i=.ORIG program.c
        make a backup of program.c to program.c.ORIG, prompt then change case in 
        the file while ignoring words like "fnGameRender", "stObj" and "thatDankIntType".
    \$ ./$prog_name -f -i .old program.c
        make a backup of program.c to program.c.old, change case in the file without 
        prompting.

BUGS
    Only problem is it pokes on formatting string such as "\\nThis is" (which becomes 
    "\\n_this is"). As a workaround, $prog_name does not impact quoted strings (i.e. 
    strings found between two \" or \' quotes *on the same line*).

AUTHOR
    Written by Sylvain Saubier (<http://SystemicResponse.com>)

REPORTING BUGS
    Mail at: <feedback\@systemicresponse.com>
EOF
}
# Show main variables
sub fn_showParams {
	no warnings 'uninitialized';
	print( STDERR <<EOF );
files           $files
exclusion patt  $excl_patt
in_place_edit   $in_place_edit
in_place_suffix $in_place_suffix
force           $force
EOF
	use warnings;
}
# line (string), exclusion pattern (string)
# TODO: there's probably a way to optimize the regex by looping it
sub fn_camelToSnake {
	my $line = shift();
	my $at_1 = '[A-Z]?[a-z]+';
	my $at = '[0-9]+|[A-Z][a-z]*';
	#my $bnd_1 = '(?![\'"]\W+\b)';
	#my $bnd_2 = '(?!\W+\b[\'"])';
	my $bnd_1 = '(?![\'"]\W*)';
	my $bnd_2 = '(?!\W*[\'"])';
	my $lookahd = '';
	if (length( my $excl_patt = shift() )) { $lookahd = '(?!'.$excl_patt.')'; }
	$line =~ s/ ${bnd_1} \b ${lookahd} ($at_1)($at) 						\b ${bnd_2} /\l$1_\l$2/gx;
	$line =~ s/ ${bnd_1} \b ${lookahd} ($at_1)($at)($at) 						\b ${bnd_2} /\l$1_\l$2_\l$3/gx;
	$line =~ s/ ${bnd_1} \b ${lookahd} ($at_1)($at)($at)($at) 			  		\b ${bnd_2} /\l$1_\l$2_\l$3_\l$4/gx;
	$line =~ s/ ${bnd_1} \b ${lookahd} ($at_1)($at)($at)($at)($at) 					\b ${bnd_2} /\l$1_\l$2_\l$3_\l$4_\l$5/gx;
	$line =~ s/ ${bnd_1} \b ${lookahd} ($at_1)($at)($at)($at)($at)($at) 				\b ${bnd_2} /\l$1_\l$2_\l$3_\l$4_\l$5_\l$6/gx;
	$line =~ s/ ${bnd_1} \b ${lookahd} ($at_1)($at)($at)($at)($at)($at)($at)			\b ${bnd_2} /\l$1_\l$2_\l$3_\l$4_\l$5_\l$6_\l$7/gx;
	$line =~ s/ ${bnd_1} \b ${lookahd} ($at_1)($at)($at)($at)($at)($at)($at)($at) 			\b ${bnd_2} /\l$1_\l$2_\l$3_\l$4_\l$5_\l$6_\l$7_\l$8/gx;
	$line =~ s/ ${bnd_1} \b ${lookahd} ($at_1)($at)($at)($at)($at)($at)($at)($at)($at) 		\b ${bnd_2} /\l$1_\l$2_\l$3_\l$4_\l$5_\l$6_\l$7_\l$8_\l$9/gx;
	$line =~ s/ ${bnd_1} \b ${lookahd} ($at_1)($at)($at)($at)($at)($at)($at)($at)($at)($at)($at) 	\b ${bnd_2} /\l$1_\l$2_\l$3_\l$4_\l$5_\l$6_\l$7_\l$8_\l$9_\l$10/gx;
	return $line;
}

GetOptions ( 'x=s' => \$excl_patt, 'i:s' => \$in_place_suffix, 'f|force' => \$force, 'h|help' => \$help, 'hack' => \$show_params );

if ($help) {
	fn_help();
	exit;
}
no warnings 'uninitialized';
if (defined( $in_place_suffix )) {
	$in_place_edit = 1;
	# if $in_place_suffix provided = $temp_suffix is unset
	if (length( $in_place_suffix )) {
		$temp_suffix = "";
	# if no $in_place_suffix provided = $temp_suffix is set
	} else {
		$in_place_suffix = "";

	}
	# so in both cases: backup to $file.$in_place_suffix.$temp_suffix
}
use warnings;
if ($show_params) {
	fn_showParams();
}
# FILE LOOPING AND REPLACING
{
	if (! @ARGV ) { fn_err( "no file specified" ); }
	# Warning: are you sure you want to edit these files?
	if (! $force && $in_place_edit) {
		my $files = "";
		foreach my $file (@ARGV) {
			$files .= "$file ";
		}
		if (length( $in_place_suffix )) {
			fn_say_err( "You are about to edit the following files:\n\t$files\nThe exclusion pattern is: \"$excl_patt\"\nBackup suffix is: \"$in_place_suffix\"\nContinue? [y/N] " );
		} else {
			fn_say_err( "You are about to edit the following files:\n\t$files\nThe exclusion pattern is: \"$excl_patt\"\nNo backup suffix provided.\nContinue? [y/N] " );
		}
		my $in = <STDIN>;
		chomp( $in );
		# it's actually also matching "yES" too but hey it's funny lmfao lol xD
		unless ($in =~ /[Yy](es|ES)?/) {
			fn_say_err( "not editing files - exiting\n" );
			exit;
		}
	}
	foreach my $file (@ARGV) {
		fn_say_err( "parsing $file\n" );
		if ($in_place_edit) {
			move( $file, $file.$in_place_suffix.$temp_suffix )
				|| fn_err( "can't rename \"$file\" to \"$file$in_place_suffix$temp_suffix\"" );
			open( my $fh_in, "<", $file.$in_place_suffix.$temp_suffix ) 
				|| fn_err( "can't open \"$file$in_place_suffix$temp_suffix\" for reading" );
			open( my $fh_out, ">", $file ) 
				|| fn_err( "can't open \"$file\" for writing" );
			while (my $line = <$fh_in>) {
				$line = fn_camelToSnake( $line, $excl_patt );
				print( $fh_out $line );
			}
			close( $fh_in ); close( $fh_out );
			# remove temp file
			if (length( $temp_suffix )) {
				# It means $in_place_suffix == "" so we can ignore it
				unlink( $file.$temp_suffix ) || fn_err( "can't remove \"$file$temp_suffix\"" );
			}
		} else {
			open( my $fh_in, "<", $file ) 
				|| fn_err( "can't open \"$file\" for reading" );
			while (my $line = <$fh_in>) {
				$line = fn_camelToSnake( $line, $excl_patt );
				print( STDOUT $line );
			}
			close( $fh_in );
		}
	}
}
# No need for end message
#fn_say_err( "all done\n" );
#TODO: proper exit?
exit;

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
