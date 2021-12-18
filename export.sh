BOBBY_ROOT="$(dirname "$BASH_SOURCE")"
export PS1="\033[1;32m(bobby-sourced)\033[;0m$PS1"

if [[ ! -f "${BOBBY_ROOT}/esp-idf/export.sh" ]]
then
    echo "esp-idf is missing, please check out all needed submodules!"
    echo "git submodule update --init --recursive"
    return
fi

. ${BOBBY_ROOT}/esp-idf/export.sh

complete -W "$(./switchconf.sh --list)" ./switchconf.sh
complete -W "$(./switchconf.sh --list)" switchconf

BOBBY_INIT_FAILED=

if [[ -e "build" ]] && [[ ! -L "build" ]]
then
    echo "ERROR: build folder exists but isnt a symlink!"
    BOBBY_INIT_FAILED=1
fi

if [[ -e "sdkconfig" ]]
then
    if [[ ! -L "sdkconfig" ]]
    then
        echo "ERROR: sdkconfig exists but isnt a symlink!"
        BOBBY_INIT_FAILED=1
    fi
else
    echo "ERROR: sdkconfig does not exist"
    BOBBY_INIT_FAILED=1
fi

if [[ -e "config.cmake" ]]
then
    if [[ ! -L "config.cmake" ]]
    then
        echo "ERROR: config.cmake exists but isnt a symlink!"
        BOBBY_INIT_FAILED=1
    fi
else
    echo "ERROR: config.cmake does not exist"
    BOBBY_INIT_FAILED=1
fi

if [[ ! -z "$BOBBY_INIT_FAILED" ]]
then
    echo "run ./switchconf.sh to fix all listed issues"
    return
fi
export PATH=$PATH:$(pwd)/tools
alias open-ide=open_ide
alias switchconf=./switchconf.sh
alias bobby-build="idf.py build"
