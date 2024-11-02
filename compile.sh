#!/bin/bash

if [[ $# -lt 1 || $# -gt 2 ]]; then
	echo -e "Enter a valid number of arguments (1 or 2)"
	echo -e "Values to 1 argument (compile, tests or tests_valgrind)"
	echo ""
	echo -e "Examples:"
	echo -e "\t./compile.sh compile               // to compile the project"
	echo -e "\t./compile.sh tests                 // to run all tests"
	echo -e "\t./compile.sh tests_valgrind        // to run all tests with valgrind"
	echo ""
	echo -e "Values to 2 argument (test GoogleFilter   or   test_valgrind GoogleFilter)"
	echo -e "  **Google Filter is a string to filter a specific suite case or test"
	echo -e "    For more info, view: https://google.github.io/googletest/primer.html#simple-tests"
	echo ""
	echo -e "Examples:"
	echo -e "\t./compile.sh tests  Suite.*                      // run all tests inside a suite"
	echo -e "\t./compile.sh tests  Suite.emptyString            // run a specific test inside the suite"
	echo -e "\t./compile.sh test_valgrind  Suite.*              // run all tests inside a suite (with valgrind)"
	echo -e "\t./compile.sh test_valgrind  Suite.emptyString    // run a specific test inside the suite (with valgrind)"
	echo ""
	exit
fi

if [[ $# -eq 1 ]] ; then
	case "$1" in
		"compile")
			make VAR=src/Main.cpp
		;;
		"tests")
			make tests
			if [ $? -ne 0 ]; then
				exit
			fi
			clear
			./output/tests/test.out
		;;
		"tests_valgrind")
			make tests
			if [ $? -ne 0 ]; then
				exit
			fi
			clear
			valgrind ./output/tests/test.out
		;;
	esac
	exit
fi

if [[ $# -eq 2 ]] ; then
	case "$1" in
		"test")
			make tests
			if [ $? -ne 0 ]; then
				exit
			fi
			./output/tests/test.out $2
		;;
		"test_valgrind")
			make tests
			if [ $? -ne 0 ]; then
				exit
			fi
			valgrind ./output/tests/test.out $2
		;;
	esac
fi