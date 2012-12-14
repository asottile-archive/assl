#!/usr/bin/env bash

# Parse command arguments
if [ "-h" == "$1" ]
then
    echo 'Runs Automated tests'
    echo '    -h: this message'
    echo '    -v: verbose'
    exit 0
fi

out="/dev/null"
if [ "-v" == "$1" ]
then
    out="/dev/stdout"
fi

RED=$(tput setab 1)
GREEN=$(tput setab 2)
NORMAL=$(tput sgr0)
col=$(tput cols)

# Make
echo  -e '\e[46m======= Building... =======\e[0m'
make clean >& $out
make >& $out
ret=$?

if [ 0 -ne $ret ]
then
    echo -e '\e[41mBUILD FAILED (' $ret ')\e[0m'
    exit $ret
else
    echo -e '\e[42mBuilt\e[0m'
fi

# Run Tests
echo
echo  -e '\e[46m========== Tests ==========\e[0m'
pass=1
for test in tests/*.out
do
    $test >& $out
    ret=$?

    cols=$(($col - ${#test} - 6))
    if [ 0 -ne $ret ]
    then
        pass=0
        A=$(printf '***%s%*s%s\n' $test $cols $RED"Failure("${ret}")" "$NORMAL")
        B=${A// /.}
        echo $B
    else
        A=$(printf '***%s%*s%s\n' $test $cols $GREEN"Success" "$NORMAL")
        B=${A// /.}
        echo $B
    fi
done

if [ $pass -ne 1 ]
then
    echo -e '\e[41mTEST FAILURES!\e[0m'
    exit -1
else
    echo -e '\e[42mTESTS PASS\e[0m'
fi
