#!/bin/bash

set -e

# Common directories
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
ROOT_DIR=${SCRIPT_DIR}/../
BUILD_DIR=${ROOT_DIR}/build

function main() {
    if [ ! -d ${BUILD_DIR} ]; then
        cd ${ROOT_DIR}
        mkdir build
        cd build
        cmake ..
    fi
    
    # Start with clean build directory
    cd ${BUILD_DIR}
    make clean
    
    # Log build
    CodeChecker log --build "make" --output ${BUILD_DIR}/compile_commands.json
    
    # Run analysis
    CodeChecker analyze ${BUILD_DIR}/compile_commands.json --enable sensitive --output ${BUILD_DIR}/reports --ignore ${SCRIPT_DIR}/static_analysis_skip.list
    
    # Generate HTML report
    CodeChecker parse --export html --output ${BUILD_DIR}/reports_html ${BUILD_DIR}/reports
}

main