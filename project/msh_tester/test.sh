# MSH-TESTER-2021.09

RESET="\033[0m"
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"

BOLDBLACK="\033[1m\033[30m"
BOLDRED="\033[1m\033[31m"
BOLDGREEN="\033[1m\033[32m"
BOLDYELLOW="\033[1m\033[33m"
BOLDBLUE="\033[1m\033[34m"
BOLDMAGENTA="\033[1m\033[35m"
BOLDCYAN="\033[1m\033[36m"
BOLDWHITE="\033[1m\033[37m"

# Compile and set executable rights
make -C ../ > /dev/null
cp ../minishell .
chmod 755 minishell


GOOD=0
TOTAL=0

pipe=/tmp/testpipe
trap "rm -f $pipe" EXIT
if [[ ! -p $pipe ]]; then
    mkfifo $pipe
fi

function exec_test()
{

  # execute commands, separated by ';' in minishell, using nfifo
  ./minishell <$pipe >msh_log 2>&-  &
  mshpid=$!
  IFS=';' read -ra CMND <<< "$@"
  for command in "${CMND[@]}"; do
    echo $command > $pipe
  done

  # only leaks mode
  if [ $LEAKSMODE  ]; then
    echo "leaks $mshpid | grep 'leaks for' | grep -v ' 0 leaks' >> leaks" > $pipe
    echo 'exit' > $pipe
    sleep 0.02
    wait $!
    sleep 0.02
    if [[ $(cat leaks 2>&-) != "" ]]; then
      printf "\n$BOLDRED LEAKS! $YELLOW%s$RESET\n" "$@"
      rm -f leaks
    else
      printf "$BOLDGREEN%s$RESET" "✓ "
    fi
    return
  fi

  echo 'exit' > $pipe
  sleep 0.01
  wait $!
  ES_1=$?
  TEST1=$(cat msh_log)

  # execute commands in bash
  bash < $pipe >msh_log 2>&-  &
  IFS=';' read -ra CMND <<< "$@"
  for command in "${CMND[@]}"; do
    echo $command > $pipe
  done
  echo 'exit' > $pipe
  wait $!
  ES_2=$?
  TEST2=$(cat msh_log)

  # compare result
  if [ "$TEST1" == "$TEST2" ] && [ "$ES_1" == "$ES_2" ]; then
    printf "$BOLDGREEN%s$RESET" "✓ "
    ((GOOD++))
  else
    printf "\n$BOLDRED%s$RESET" "✗ "
    printf "$CYAN \"$@\" $RESET"
  fi
  if [ "$TEST1" != "$TEST2" ]; then
    echo
    printf $BOLDRED"Your output : \n%.20s\n$BOLDRED$TEST1\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
    printf $BOLDGREEN"Expected output : \n%.20s\n$BOLDGREEN$TEST2\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
    echo
  fi
  if [ "$ES_1" != "$ES_2" ]; then
    echo
    printf $BOLDRED"Your exit status : $BOLDRED$ES_1$RESET\n"
    printf $BOLDGREEN"Expected exit status : $BOLDGREEN$ES_2$RESET\n"
    echo
  fi
  ((TOTAL++))
  sleep 0.08
}

if [ "$1" == "" ] || [ "$1" == "help" ]; then
  printf "$BOLDMAGENTA\n\tAvailable arg: \n$YELLOW\tall$RESET echo cd pipe env export redirect multi syntax exit custom_1 custom_2 custom_3\n\
      $GREEN\tbonus$RESET quote wildcard oper\n"
fi
if [ "$1" == "all" ]; then
  printf "$BOLDMAGENTA ___  ___  _____  __   _  _____   _____  _   _  _____  _       _\n"
  printf "|   \/   ||_   _||  \ | ||_   _| / ____|| | | || ____|| |     | |\n"
  printf "| |\  /| |  | |  | | \| |  | |  | (___  | |_| || |___ | |     | |\n"
  printf "| | \/ | |  | |  | |. \` |  | |   \___ \ |  _  ||  ___|| |     | |\n"
  printf "| |    | | _| |_ | | \  | _| |_  ____) || | | || |___ | |____ | |____ \n"
  printf "|_|    |_||_____||_|  \_||_____||_____/ |_| |_||_____||______||______|\n$RESET"
fi

if [ "$2" == "leaks" ]; then
  printf $BOLDBLUE"\n\tONLY LEAKS MODE\n"$RESET
  LEAKSMODE=1
  rm -f leaks
fi

# ECHO TESTS
if [ "$1" == "echo" ] || [ "$1" == "all" ]; then
  printf $BOLDMAGENTA"\n\tECHO TESTS\n"$RESET
  exec_test 'echo test tout'
  exec_test 'echo test tout'
  exec_test 'echo -n test tout'
  exec_test 'echo -n -n -n test tout'
fi

# CD TESTS
if [ "$1" == "cd" ] || [ "$1" == "all" ]; then
  printf $BOLDMAGENTA"\n\tCD TESTS\n"$RESET
  exec_test 'cd .. ; pwd'
  exec_test 'cd /Users ; pwd'
  exec_test 'cd ; pwd'
  exec_test 'cd . ; pwd'
  exec_test 'cd -; pwd; cd; cd -'
  exec_test 'mkdir test_dir ; cd test_dir ; rm -rf ../test_dir ; cd . ; cd .. ; pwd'
fi

# PIPE TESTS
if [ "$1" == "pipe" ] || [ "$1" == "all" ]; then
  printf $BOLDMAGENTA"\n\tPIPE TESTS\n"$RESET
  exec_test '/bin/ls'
  exec_test 'cat tests/lorem.txt | grep arcu | cat -e'
  exec_test 'echo test | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e'
  exec_test 'cat /dev/random | head -c 100 | wc -c'
  exec_test 'ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls'
  exec_test 'ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls'
  exec_test 'ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls'
  head -c 2000000 /dev/zero > big_file
  exec_test ' cat big_file | ls'
  exec_test ' cat big_file | echo lol'
fi

# ENV EXPANSIONS
if [ "$1" == "env" ] || [ "$1" == "all" ]; then
  printf $BOLDMAGENTA"\n\tENV EXPANSIONS TESTS\n"$RESET
	exec_test 'echo test test'
	exec_test 'echo test'
	exec_test 'echo $TEST'
	exec_test "echo \"$TEST\""
	exec_test "echo \'$TEST\'"
	exec_test "echo \"$TEST$TEST$TEST\""
	exec_test "echo \"$TEST$TEST=lol$TEST\""
	exec_test "echo \" $TEST lol $TEST\""
	exec_test "echo $TEST$TEST$TEST"
	exec_test "echo $TEST$TEST=lol$TEST\"\"lol"
	exec_test "echo $TEST lol $TEST"
	exec_test "echo test \"$TEST\" test \"$TEST \" test"
	exec_test "echo \"$=TEST\""
	exec_test "echo \"$\""
	exec_test "echo \"$?TEST\""
	exec_test "echo $TEST $TEST"
	exec_test "echo \"$1TEST\""
	exec_test "echo \"$T1TEST\""
fi

# EXPORT
if [ "$1" == "export" ] || [ "$1" == "all" ]; then
  printf $BOLDMAGENTA"\n\tEXPORT TESTS\n"$RESET
  ENV_SHOW="env | sort | grep -v SHLVL | grep -v _="
  EXPORT_SHOW="export | sort | grep -v SHLVL | grep -v _= | grep -v OLDPWD"
  exec_test $ENV_SHOW
  exec_test $EXPORT_SHOW
  exec_test 'export ='
  exec_test 'export 1TEST= ;' $ENV_SHOW
  exec_test 'export TEST ;' $EXPORT_SHOW
  exec_test 'export ""="" ; ' $ENV_SHOW
  exec_test 'export TES=T="" ; ' $ENV_SHOW
  exec_test 'export TE+S=T="" ; ' $ENV_SHOW
  exec_test 'export TEST=LOL ; echo $TEST ; ' $ENV_SHOW
  exec_test 'export TEST=LOL ; echo $TEST$TEST$TEST=lol$TEST'
  exec_test 'export TEST1=LOL TEST2=PIKAPIKA; echo $TEST ; ' $ENV_SHOW
  exec_test 'export TEST1=LOL TEST2' $ENV_SHOW
  exec_test 'export TEST=LOL; unset TEST' $ENV_SHOW
  exec_test 'export TEST=LOL ; export TEST+=LOL ; echo $TEST ; ' $ENV_SHOW
  exec_test $ENV_SHOW
  exec_test $EXPORT_SHOW
  exec_test 'export TEST="ls -l - a" ; echo $TEST ; ' $ENV_SHOW
fi


# REDIRECTIONS
if [ "$1" == "redirect" ] || [ "$1" == "all" ]; then
  printf $BOLDMAGENTA"\n\tREDIRECTION TESTS\n"$RESET
  exec_test 'echo test > ls ; cat ls'
  exec_test 'echo test > ls >> ls >> ls ; echo test >> ls ; cat ls'
  exec_test '> lol echo test lol ; cat lol'
  exec_test '>lol echo > test>lol>test>>lol>test mdr >lol test >test ; cat test'
  exec_test 'cat < ls'
  exec_test 'rm -f ls; cat > ls < ls; rm -f ls'
  exec_test 'ls > ls'
  exec_test 'cat <ls'
  exec_test 'pwd >pwd; cat pwd'
  exec_test 'pwd >pwd; cat pwd | echo'
#   exec_test 'cat | <Makefile cat; hello'
  exec_test 'cat < test.sh < ls'
  exec_test 'cat <test.sh <ls'
  exec_test 'cat << stop;1;stop;'
  exec_test 'cat << stop;1\EOF;stopa;stop'
  exec_test 'cat <test.sh <<stop;1;stop'
#   exec_test 'cat <<stop<ls;1;stop'
#   exec_test 'cat <test.sh << stop1 <<stop2;a;;b;c;stop1; run2;stop2'
  exec_test 'rm -f ls >ls'
fi


# MULTI TESTS
if [ "$1" == "multi" ] || [ "$1" == "all" ]; then
  printf $BOLDMAGENTA"\n\tMULTI TESTS\n"$RESET
  exec_test 'echo testing multi >lol ; echo <lol <lola ; echo "test 1  | and 2" >>lol ; cat <lol ; cat ../Makefile <lol | grep minishell'
  exec_test 'unset PATH; /bin/ls'
  exec_test 'unset PATH; ./Makefile'
  exec_test 'echo 5 > ls; <5 cat; rm 5'
  exec_test 'ls | echo 6 > ls; <6 cat; rm 6'
  exec_test 'cd; unset HOME; cd'
  exec_test 'cd .. > 1; pwd'
  exec_test 'cd .. > 1| pwd'
  exec_test 'pwd > 1'
  exec_test 'pwd > 1; cat 1'
  exec_test 'pwd > 1; pwd'
  exec_test 'pwd > 1| pwd'
  exec_test 'pwd; unset HOME; pwd; cd; pwd'
  exec_test 'ls | export TEST=5; echo $TEST'
  exec_test 'export TEST1=LOL TEST2=PIKAPIKA; unset TEST1 TEST2; echo $TEST1; echo $TEST2'
fi

# SYNTAX
if [ "$1" == "syntax" ] || [ "$1" == "all" ]; then
  printf $BOLDMAGENTA"\n\tSYNTAX\n"$RESET
  exec_test ''
  exec_test '" echo" lol'
  exec_test '"echo " lol'
  exec_test '" echo" | " pwd"'
  exec_test '"echo " | "pwd "'
  exec_test '/bin/lsa'
  exec_test './Makefile'
  exec_test '| test'
  exec_test 'echo > <'
  exec_test 'echo | |'
  exec_test 'echo "||"'
  exec_test '<'
  exec_test 'rm -f ls; cat < ls > ls'
  exec_test "grep -z"
  exec_test "ls'| 'wc -l"
  exec_test "ls\'| \'wc -l"
  exec_test "/ls"
fi

# EXIT
if [ "$1" == "exit" ] || [ "$1" == "all" ]; then
  printf $BOLDMAGENTA"\n\tEXIT\n"$RESET
  exec_test "exit 42"
  exec_test "exit 42 53 68"
  exec_test "exit 259"
  exec_test "exit 9223372036854775807"
  exec_test "exit -9223372036854775808"
  exec_test "exit 9223372036854775808"
  exec_test "exit -9223372036854775810"
  exec_test "exit 99999999999999999999999"
  exec_test "exit -99999999999999999999999"
  exec_test "exit -4"
  exec_test "exit wrong"
  exec_test "exit  2 wrong_command"
  exec_test "gdagadgag"
  exec_test "ls -Z"
  exec_test "cd gdhahahad"
  exec_test "ls -la | wtf"
fi

# CUSTOM RANDOM 1
if [ "$1" == "custom_1" ] || [ "$1" == "all" ]; then
  printf $BOLDMAGENTA"\n\tCUSTOM RANDOM 1\n"$RESET
#   exec_test "\'\' "
#   exec_test "\"\""
  exec_test ""
  exec_test "\" \""
  exec_test "\' \'"
  exec_test "pwd"
  exec_test "ls"
  exec_test "\" \""
  exec_test ";;"
  exec_test ";;"
  exec_test ";"
  exec_test "|"
  exec_test "||"
  exec_test "@@;"
  exec_test ";@@;"
  exec_test "| |"
  exec_test "ls;;"
  exec_test "ls; ;"
  exec_test ";;"
  exec_test "ls||"
  exec_test "ls | |"
  exec_test "echo \""
#   exec_test "echo \'"
#   exec_test "echo \'\'\'"
  exec_test "echo \"hello\"\""
  exec_test "echo \$PWD"
  exec_test "echo \$321"
  exec_test "echo \$fdsgbkldmbklfdsmklfmd"
  exec_test "echo str1\"\'str2\'\""
  exec_test "echo str1\"\'\$str2\'\""
  exec_test "echo \'str1\'str2\"str3 \$PWD str4\" \"str5\"\'\$PWD\' \$PWD \"\$PWD\""
  exec_test "echo \"hello><; world\""
  exec_test "echo \'hello><; world\'"
  exec_test "echo \$hfkdghldf\$PWD"
  exec_test "echo \'\$hfkdghldf\$PWD\'"
  exec_test " echo \' """" \' "
  exec_test "echo \" \'\'\'\'\'\' \""
  exec_test "echo \"\"\"\"\"\"\"\""
  exec_test "echo \'\'\'\'\'\'\'\'"
  exec_test "echo \"\"\"\"\"\"\"\"\"\"       :\"\""
  exec_test "echo \"\"\"\"\"\"\"\"\"\",     wtf   :\"\""
  exec_test "echo \'\"\"\"\"\"\"\"\"\"\",     wtf   :\"\"\'"
fi

# # CUSTOM RANDOM 2
# if [ "$1" == "custom_2" ] || [ "$1" == "all" ]; then
#   printf $BOLDMAGENTA"\n\tCUSTOM RANDOM 2\n"$RESET
#   exec_test "echo hello            happy                man"
#   exec_test "export = ; echo \$?"
#   exec_test "echo \$?"
#   exec_test "export str1 2str = _3str str4=str5"
#   exec_test "	\'e\'\"x\"p\'o\'r\'t\'"
#   exec_test "ec\"ho\" \$str1 \$str4"
#   exec_test "	\'export\' \'q\'=e \"w\"=c e=\"h\" r=\'o\' \'t\'=\'x\' \"y\"=\"p\" u=r i=t"
#   exec_test "	\'e\'\"x\"p\'o\'r\'t\' \"t\"\$q\'s\'\$i=\'h\'\"e\"\'l\'l\$r"
#   exec_test "echo \"first;\"; \$q\'c\'\"h\"o \$test"
#   exec_test "\$q\$w\$e\'o\' \$PWD;  cd .. ;  \$q\"c\"\$e\'o\' \$PWD  ;"
#   exec_test "cd -; pwd"
#   exec_test "\$lkjlkjllkdfs\$q\$w\$e\$r \"\$e\"\$q\"l\"\'l\'\$r;"
#   exec_test "	echo     \'\"\\"
#   exec_test "echo hello sad man"
#   exec_test "echo \$?"
#   exec_test ">fil\$q\'1\' e\$w\"ho\" s\$i\"r\"ing f\$r\$u file1"
#   exec_test "pwd ; cat file1"
#   exec_test "ls lskdgjdhgisdoigjiredg"
#   exec_test "echo \$?"
#   exec_test "echo \$?"
#   exec_test "unset PWD; echo \$PWD"
#   exec_test "ls; unset PATH; ls   ;"
#   exec_test "echo \$?"
#   exec_test "echo \$?"
#   exec_test "export PATH=/ ; ls"
#   exec_test "echo \$?"
#   exec_test "export PATH=/bin ; ls"
#   exec_test "echo \$?"
#   exec_test "echo \$PWD; unset PWD"
#   exec_test "echo \$PWD; export PWD=/ ; echo \$PWD;"
#   exec_test "pwd; echo \$PWD"
#   exec_test "cd; echo \$PWD; cd -"
#   exec_test "echo \$PWD; echo \$OLDPWD"
#   exec_test "unset OLDPWD; echo \$OLDPWD"
#   exec_test "cd; echo \$OLDPWD"
#   exec_test "cd ; echo \$PWD; echo \$OLDPWD"
#   exec_test "cd -"
#   exec_test "ls -la"
#   exec_test "ls \"-la\" ; cd -"
#   exec_test "echo \'\\\'"
#   exec_test "echo \'\\'"
#   rm fil\'1\'
# fi

# # CUSTOM RANDOM 3
# if [ "$1" == "custom_3" ] || [ "$1" == "all" ]; then
#   printf $BOLDMAGENTA"\n\tCUSTOM RANDOM 3\n"$RESET
# #   exec_test "echo ~"
#   exec_test "echo \\hello \\\$PWD"
#   exec_test "echo \'\\hello \\\$PWD\'"
#   exec_test "echo \"\\hello \\\$PWD\""
#   exec_test "echo \"\\\$PWD\" \"\\PWD\""
#   exec_test "echo \'\"\\ \"hello\$PWD\""
#   exec_test "echo \"\"\""
#   exec_test "echo \"\'\""
#   exec_test "\"echo f\" hello"
#   exec_test "export t=n; echo -\$t -n \"-\"\'n\' hello"
#   exec_test "echo -\$t \"-n\" \'-\'\'n\' \'-n;\'     -n hello"
#   exec_test "export a=l d=s; \$a\$d"
#   exec_test "echo \$PWD > as ; cat as; rm as"
#   exec_test "echo \'\'\\'\'\"a|\"\\\'q\'a\'\\a\'w\'"
#   exec_test "echo \\\"\\\|\\;\\\"\\\| cat -e > \\q\\w\\e\\r\\t\\y ; cat qwerty; rm qwerty"
#   exec_test "pwd >a1>a2>a3; echo s1 >q1 s2>q2 s3; cat a2; cat a3; cat q1; cat q2;"
#   exec_test "echo"
#   exec_test "echo hello '\' ';' "  '\' \" " \" "\$PWD\\\"\~\;"\; >> t1 \' \ \ \\"
#   exec_test "echo hello '\' ';' "  '\' \" " \" "\$PWD\\\"\~\;"\; >> t1 \' \ \ \\ ; cat t1"
#   exec_test "\\ls\" \";"
#   exec_test "ec\"ho;\";pwd"
#   exec_test "/bin/ls -la"
# fi

# rm a1 a2 a3 q1 q2 t1

# BONUS
if [ "$1" == "bonus" ] || [ "$1" == "quote" ] || [ "$1" == "wildcard" ] || [ "$1" == "oper" ]; then
  Compile and set executable rights
  make bonus -C ../ > /dev/null
  cp ../minishell .
  chmod 755 minishell
fi

# BONUS QUOTES
if [ "$1" == "bonus" ] || [ "$1" == "quote" ]; then
  printf $BOLDMAGENTA"\n\tBONUS QUOTE\n"$RESET
  exec_test "echo \'"$USER"\'"
  exec_test "echo \'"$USER"\' "$USER" "$USERr""
  exec_test "echo \'"$USERr"\'"
  exec_test "echo \"'$USER'\""
  exec_test "echo \"'$USERr'\""
  exec_test 'cat < Makefile 1>1'
  exec_test 'cat < Makefile 222>1 ; rm 1'
  exec_test 'rm 1'
fi

# BONUS WILDCARD
if [ "$1" == "bonus" ] || [ "$1" == "wildcard" ]; then
  printf $BOLDMAGENTA"\n\tBONUS WILDCARD\n"$RESET
  exec_test "echo * | wc"
  exec_test "cd .. ; echo * | wc"
  exec_test "echo .* | wc"
  exec_test "echo M*e"
  exec_test "echo *a*e"
  exec_test "echo *.mp3"
  exec_test "mkdir empty; cd empty; pwd; echo *; cd ..; rm -rf empty"
fi

# BONUS OPERATOR && || ()
if [ "$1" == "bonus" ] || [ "$1" == "oper" ]; then
  printf $BOLDMAGENTA"\n\tBONUS OPERATOR \$\$ || () \n"$RESET

  exec_test 'true && ls'
  exec_test 'false&&ls'
  exec_test 'true||ls'
  exec_test 'false || ls'
  exec_test 'true || echo 1 && echo 2'
  exec_test 'false || echo 1 && echo 2'
  exec_test 'true || (echo 1 && echo 2)'
  exec_test 'true || echo 1 && echo 2 || echo 3'
  exec_test '(ls)'
  exec_test '( ls )'
  exec_test 'export TEST=456 && (export TEST=abc && echo $TEST && (export TEST=def && echo $TEST)) && echo $TEST'
  exec_test 'true || (echo 1 && echo 2) || echo 3'
  exec_test 'true || (echo 1 && echo 2) && echo 3'
  exec_test '(true || (echo 1 && echo 2) && echo 3)'
  exec_test 'true || ((echo 1 && echo 2) && echo 3)'
  exec_test '( )'
  exec_test ')'
  exec_test ' )'
  exec_test ' &&'
  exec_test '&& '
  exec_test '&&'
  exec_test ' ls )'
  exec_test '( ls '
  exec_test 'ls && (touch 1 && pwd) && rm 1'
fi

if [[ "$1" != "" ]] && (( $TOTAL > 0)); then
  PROCENT=$(( $GOOD * 100  / $TOTAL ))
  if (( $PROCENT > 90)); then
    printf $GREEN
  elif (( $PROCENT <= 90 )) && (( $PROCENT > 60 )); then
    printf $YELLOW
  else
    printf $RED
  fi
  printf "\nPASS: $GOOD / $TOTAL ($PROCENT%%)$RESET\n"
fi

rm -f $pipe lol ls 1 test big_file msh_log leaks pwd
