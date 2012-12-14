#!/usr/bin/env bash

# Some pre-commit scripts for styley things

if [ "-i" == "$1" ]
then
    path=`git rev-parse --show-toplevel`/.git/hooks/pre-commit
    cp pre-commit.sh $path >& /dev/null
    ret=$?
    if [ 0 -ne $ret ]
    then
        echo "Error installing commit script."
    else
        chmod 775 $path
        echo "Installed to $path"
    fi
    exit $ret
elif [ "-u" == "$1" ]
then
    path=`git rev-parse --show-toplevel`/.git/hooks/pre-commit
    echo 'Removing pre-commit hook...'
    rm $path >& /dev/null
    ret=$?
    if [ 0 -ne $ret ]
    then
        echo 'Error deleting pre-commit hook.'
    else
        echo 'Pre-commit hook removed.'
    fi
    exit $?
fi

RED=$(tput setab 1)
GREEN=$(tput setab 2)
NORMAL=$(tput sgr0)
col=$(tput cols)

fails=0

echo 'Trimming trailing whitespace...'
for file in `git ls-files | egrep '\.(cpp|h|sh)' | xargs grep -l '[[:space:]]$'`
do
    echo "Fixing $file..."
    sed -i -e 's/[[:space:]]*$//' "$file"
    fails=$(($fails + 1))
done

printmessage() {
    # Args:
    #     message - The message to print.
    #     command - Command to run.
    #     nonzero - Whether the command should return nonzero
    #     run_test - Skips test if "false"
    local message=$1
    local command=$2
    local nonzero=$3
    local run_test=$4

    if [ "$run_test" == "false" ]
    then
        echo "Skipping $message due to git config."
        return 0
    fi

    echo -n $message

    local output
    output=$(eval $command)
    local ret=$?

    local cols=$(($col - ${#message} - 4))

    local fail=0
    if [ 0 -eq $nonzero ]
    then
        if [ 0 -ne $ret ]
        then
            local fail=1
        fi
    elif [ 0 -eq $ret ]
    then
        local fail=1
    fi

    if [ 0 -ne $fail ]
    then
        local A=$(printf '%*s%s\n' $cols $RED"Failure("${ret}")" "$NORMAL")
        local B=${A// /.}
        echo $B
        echo "$output"
    else
        local A=$(printf '%*s%s\n' $cols $GREEN"Success" "$NORMAL")
        local B=${A// /.}
        echo $B
    fi
    return $fail
}

tests[0]='make'
testnames[0]='Verifying Building'
nonzero[0]=0
run_test[0]=$(git config hooks.testmake)

tests[1]='git ls-files | egrep "\.(cpp|h)" | xargs grep "//[^ ]" -H -n'
testnames[1]='Verifying space after // comments'
nonzero[1]=1
run_test[1]=$(git config hooks.testcomments)

tests[2]='git ls-files | xargs egrep -H -n "(if|for|while)\("'
testnames[2]='Verifying that if/for/while has a space after it'
nonzero[2]=1
run_test[2]=$(git config hooks.testkeyword)

tests[3]='git ls-files | xargs grep -H -n ")\B{"'
testnames[3]='Verifying that if statements look like if (...) {'
nonzero[3]=1
run_test[3]=$(git config hooks.testbrace)

tests[4]='git ls-files | egrep "\.(cpp|h)" | xargs grep -H -n -P "\t"'
testnames[4]='Verifying no tabs'
nonzero[4]=1
run_test[4]=$(git config hooks.testtabs)

tests[5]='git ls-files | egrep "\.(cpp|h)" | xargs egrep -H -n "\( "'
testnames[5]='Checking spaces after parens'
nonzero[5]=1
run_test[5]=$(git config hooks.testparenspace)

length=${#tests[@]}
for ((i=0;i<$length;i++))
do
    printmessage "${testnames[i]}" "${tests[i]}" ${nonzero[i]} "${run_test[i]}"
    ret=$?
    fails=$(($fails + $ret))
done

if [ 0 -ne $fails ]
then
    printf '%sFailures / Fixes detected.%s  Please fix and commit again.\n' $RED $NORMAL
    echo 'You could also pass --no-verify, but this is probably not what you want to do.'
    echo
    echo "Here's git status for convenience:"
    git status
fi

exit $fails
