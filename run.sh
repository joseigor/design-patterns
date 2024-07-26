#!/bin/sh

set -eu

. ./project_config.sh

BUILDDIR=${BUILDDIR:-"./build"}
APP_PATH=${APP_PATH:-"${BUILDDIR}/src/${PROJECT_NAME}"}

echo "==============================================================================="
echo "Starting application ..."
echo "==============================================================================="

"${APP_PATH}" "${@}"
