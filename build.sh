#!/bin/sh

set -eu

. ./project_config.sh

BUILDDIR=${BUILDDIR:-"./build"}
BUILDTYPE=${BUILDTYPE:-"Debug"}

fast_build=0
build_gcov="false"
unit_test="false"

usage()
{
	echo "Usage: ${0} [OPTIONS]"
	echo "Build and compile whole project."
	echo "Available options:"
	echo "    -h   Print this help (usage)."
	echo "    -f   Incremental build."
}

cleanup() {
	trap EXIT
}

main()
{
	_start_time="$(date "+%s")"

	while getopts ":hfgu" _options; do
		case "${_options}" in
		h)
			usage
			exit 0
			;;
		f)
			fast_build=1
			echo "info" "Fast building..."
			;;
		g)
			build_gcov="true"
			echo "info" "Build with Gcov"
			;;
		u)
			unit_test="true"
			echo "info" "Build with unit tests"
			;;
		:)
			echo "Option -${OPTARG} requires an argument."
			exit 1
			;;
		?)
			echo "Invalid option: -${OPTARG}"
			exit 1
			;;
		esac
	done

	if [ $fast_build = 0 ]; then
		rm -rf "${BUILDDIR}"
		cmake -B "${BUILDDIR}" -DCMAKE_BUILD_TYPE="${BUILDTYPE}"
	fi

	cmake --build "${BUILDDIR}"

	cleanup

	echo "==============================================================================="
	echo "Ran build and compile processes in $(($(date "+%s") - _start_time)) seconds"
	echo "==============================================================================="
}

main "${@}"

exit 0
