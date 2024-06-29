#!/bin/bash

set -e

# Common directories
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
ROOT_DIR=${SCRIPT_DIR}/../
BUILD_DIR=${ROOT_DIR}/build

python3 -m multimetric ${ROOT_DIR}/src/*.h ${ROOT_DIR}/src/*.c ${ROOT_DIR}/src/*/*.h ${ROOT_DIR}/src/*/*.c | tee ${BUILD_DIR}/code_stats.json