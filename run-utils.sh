#!/bin/bash

set -eu

. ./project_config.sh

#McCabe related environment variables
CI_MCCABE_THRESHOLD_POOR=20
CI_MCCABE_THRESHOLD=${CI_MCCABE_THRESHOLD:-$CI_MCCABE_THRESHOLD_POOR}


usage()
{
	echo "Usage: ${0} [OPTIONS]"
	echo "Run lint tools on this repository."
	echo "The following environment variables can be set to pass additional parameters:"
	echo "    [CI_MCCABE_THRESHOLD] McCabe score threshold, default is "$CI_MCCABE_THRESHOLD_POOR.""
	echo "Available options:"
	echo "    -h   Print this help (usage)."
	echo "    -m   Calculate McCabe-style cyclomatic complexity."
	echo "    -f   Check if source code is correctly formated."
	echo "    -c   Format all project's source files."
	echo "    -t   Run clang-tidy to source files."
}

cleanup() {
	trap EXIT
}

# Function to find source files, excluding specified directories
find_source_files() 
{
    local search_path="$1"
    local exclude_dirs=("$2")

    find "$search_path" -type d \( -path "${exclude_dirs[0]}" \) -prune \
        -o -iname "*.h" -print \
        -o -iname "*.hpp" -print \
        -o -iname "*.hxx" -print \
        -o -iname "*.c" -print \
        -o -iname "*.cpp" -print \
        -o -iname "*.cc" -print \
        -o -iname "*.cxx" -print
}

clang_format_check()
{
	echo "Checking if source code files are correctly formated..."

	find_source_files . "$BUILDDIR" | xargs clang-format --dry-run --Werror

	echo "Source code files are correctly formated."
}

clang_format_apply()
{
	echo "Applying clang-format to project's source files..."

	find_source_files . "$BUILDDIR" |  xargs clang-format style=file -i -fallback-style=none

	echo "Project's source files formated."

}

clang_tidy_run()
{
	echo "Running clang-tidy to project's source files..."

	find_source_files . "$BUILDDIR" |  xargs clang-tidy -p "$BUILDDIR"

	echo "Project's source files formated."

}
calculates_mccabe_complexity()
{
	echo "+---------------------------------------------------------------+"
	echo "|------------- McCabe Cyclomatic Complexity report -------------|"
	echo "|---------------------------------------------------------------|"
	find "$SRCDIR" -type f -iname "*.[c,h]" | xargs  pmccabe -v -c

	echo ""
	echo "+---------------------------------------------------------------+"
	echo "|------------- McCabe Cyclomatic Complexity reference ----------|"
	echo "|---------------------------------------------------------------|"
	echo "|                            Scores                             |"
	echo "|   Excellent                                             < 5   |"
	echo "|   Very Good                                          6  - 7   |"
	echo "|   Good                                               8  - 10  |"
	echo "|   Mediocre                                           11 - 20  |"
	echo "|   Poor                                               20 - 40  |"
	echo "|   Very poor                                             > 40  |"
	echo "|                                                               |"
	echo "+---------------------------------------------------------------+"

	echo "Project McCabe threshold for this project is : $CI_MCCABE_THRESHOLD "

	eval \
		"find \$SRCDIR -type f -iname \"*.[c,h]\" \
		| xargs  pmccabe \
		| awk '{if(\$1>='$CI_MCCABE_THRESHOLD' || \$2>='$CI_MCCABE_THRESHOLD')print}' \
		> temp_mccab_result"


	if [ -s temp_mccab_result ]; then
		echo ""
		echo "The following functions have a McCabe score above the $CI_MCCABE_THRESHOLD, please fix them: "
		cat temp_mccab_result
		rm -f temp_mccab_result
		exit 1
	else
		echo "All functions are scored below McCabe $CI_MCCABE_THRESHOLD, good work! "
		rm -f temp_mccab_result
	fi
}

main()
{
	while getopts ":hmfct" _options; do
		case "${_options}" in
		h)
			usage
			exit 0
			;;
		m)
			calculates_mccabe_complexity
			exit 0
			;;
		f)
			clang_format_check
			exit 0
			;;
		c)
			clang_format_apply
			exit 0
			;;
		t)
			clang_tidy_run
			exit 0
			;;
		:)
			echo "Option -${OPTARG} requires an argument."
			exit 1
			;;
		?)
			echo "Invalid option: -${OPTARG}"
			exit 1
			;;
		 *)
		 	echo "Invalid option: -${OPTARG}"
			exit 1
			;;
		esac
	done
	shift "$((OPTIND - 1))"

	cleanup

}

main "${@}"

exit 0
