#!/usr/bin/env bash
PROJECT_HOME=$(cd "$(dirname "${BASH_SOURCE[0]}")"; pwd)

export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${PROJECT_HOME}/output/lib
export PATH=/sdc/xdl/env/cmake-3.9.1-Linux-x86_64/bin/:$PATH