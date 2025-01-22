#!/bin/bash

GTEST_BUILD_DIR="output/tests/gtest/"

GTEST_LIBS="$GTEST_BUILD_DIR""lib/libgmock.a"" ""$GTEST_BUILD_DIR""lib/libgtest.a"

TESTS_BINARY="output/tests/test.out"

compile_tests(){
	make -f Makefile_gtest ARG_GTEST_BUILD_DIR="$GTEST_BUILD_DIR" ARG_GTEST_LIBS="$GTEST_LIBS"
	if [ $? -ne 0 ]; then
		echo -e "\033[1;31mWebserv: Compilation of googletest library failed\033[0m"
		return 1
	fi
	make COMPILE=tests -j$(nproc) ARG_GTEST_BUILD_DIR="$GTEST_BUILD_DIR" ARG_GTEST_LIBS="$GTEST_LIBS" ARG_TESTS_BINARY="$TESTS_BINARY"
	if [ $? -ne 0 ]; then
		echo -e "\033[1;31mWebserv: Compilation of test files failed\033[0m"
		return 1
	fi
	return 0
}

the_tests(){

	local filter=$1

    $(cd tests/integration/ && chmod +x set_permissions.sh && ./set_permissions.sh)
	if [ $? -ne 0 ]; then
		echo -e "\033[1;31mWebserv: Error trying to create the environment for integration tests\033[0m"
		return 1
	fi

	compile_tests
	if [ $? -ne 0 ]; then
		return 1
	fi

	if [ -z "$filter" ]; then
		"./""$TESTS_BINARY"
	else
		"./""$TESTS_BINARY" --gtest_filter="$filter"'.*'
		echo -e "\033[33mWebserver: **Filter applied to: ""$filter"" Test Suite!**\033[0m"
	fi

    $(cd tests/integration/ && chmod +x remove_permissions.sh && ./remove_permissions.sh)
	if [ $? -ne 0 ]; then
		echo -e "\033[1;31mWebserv: error when trying to change the permissions of the integration test files, this can cause problems at commit time\033[0m"
		return 1
	fi
	return 0
}




















if [ -z "$1" ]; then
    echo -e "    please pass a parameter!"
	echo -e "    valid parameters:\n"
	echo -e "        compile"
	echo -e "        clean"
	echo -e "        tests"
    exit 1
fi

USER_OPTION=$1

if [ "$USER_OPTION" == "compile" ]; then
	make COMPILE=binary -j$(nproc)
fi

if [ "$USER_OPTION" == "clean" ]; then
	make clean
fi

if [ "$USER_OPTION" == "tests" ]; then

	if [ -z "$2" ]; then
		the_tests
		if [ $? -ne 0 ]; then
			exit 1
		fi
	else
		the_tests "$2"
		if [ $? -ne 0 ]; then
			exit 1
		fi
	fi

fi
