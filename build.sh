#!/bin/bash

GTEST_BUILD_DIR="output/tests/gtest/"

GTEST_LIBS="$GTEST_BUILD_DIR""lib/libgmock.a"" ""$GTEST_BUILD_DIR""lib/libgtest.a"

TESTS_BINARY="output/tests/test.out"

compile_gtest_things(){
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

set_permissions_to_things_to_test(){
    $(cd tests/integration/ && chmod +x set_permissions.sh && ./set_permissions.sh)
	if [ $? -ne 0 ]; then
		echo -e "\033[1;31mWebserv: Error trying to create the environment for integration tests\033[0m"
		return 1
	fi
}

remove_permissions_to_things_to_test(){
    $(cd tests/integration/ && chmod +x remove_permissions.sh && ./remove_permissions.sh)
	if [ $? -ne 0 ]; then
		echo -e "\033[1;31mWebserv: error when trying to change the permissions of the integration test files, this can cause problems at commit time\033[0m"
		return 1
	fi
}


the_tests(){

	set_permissions_to_things_to_test
	if [ $? -ne 0 ]; then
		return 1
	fi

	compile_gtest_things
	if [ $? -ne 0 ]; then
		return 1
	fi

	local filter=$1

	if [ -z "$filter" ]; then
		"./""$TESTS_BINARY"
	else
		"./""$TESTS_BINARY" --gtest_filter="$filter"'.*'
		echo -e "\033[33mWebserver: **Filter applied to: ""$filter"" Test Suite!**\033[0m"
	fi

	remove_permissions_to_things_to_test
	if [ $? -ne 0 ]; then
		return 1
	fi

	return 0
}


the_val_tests(){

	set_permissions_to_things_to_test
	if [ $? -ne 0 ]; then
		return 1
	fi

	compile_gtest_things
	if [ $? -ne 0 ]; then
		return 1
	fi

	local filter=$1

	if [ -z "$filter" ]; then
		valgrind --error-exitcode=1 --exit-on-first-error=yes --leak-check=full --child-silent-after-fork=yes --track-fds=yes "./""$TESTS_BINARY"
		if [ $? -eq 1 ]; then
		    remove_permissions_to_things_to_test
			echo -e "\033[1;31mVALGRIND : Code failed to pass valgrind! (memory leak or open file descriptor) \033[0m"
			return 1
		fi
	else
		valgrind --error-exitcode=1 --exit-on-first-error=yes --leak-check=full --child-silent-after-fork=yes --track-fds=yes "./""$TESTS_BINARY" --gtest_filter="$filter"'.*'
		if [ $? -eq 1 ]; then
		    remove_permissions_to_things_to_test
			echo -e "\033[1;31mVALGRIND : Code failed to pass valgrind! (memory leak or open file descriptor) \033[0m"
			return 1
		fi
		echo -e "\033[33mWebserver: **Filter applied to: ""$filter"" Test Suite!**\033[0m"
	fi

	remove_permissions_to_things_to_test
	if [ $? -ne 0 ]; then
		return 1
	fi

	return 0
}



















if [ -z "$1" ]; then
    echo -e "    please pass a parameter!"
	echo -e "    valid parameters:\n"
	echo -e "        compile"
	echo -e "        clean"
	echo -e "        tests [filter]"
	echo -e "        val_tests [filter]"
	echo -e "        val_run <configuration file>"
	echo -e "        re"
	echo -e "        ci"
    exit 1
fi

USER_OPTION=$1

if [ "$USER_OPTION" == "compile" ]; then
	make COMPILE=binary -j$(nproc)
	if [ $? -eq 1 ]; then
		exit 1;
	fi
	exit 0
fi

if [ "$USER_OPTION" == "clean" ]; then
	make clean
	if [ $? -eq 1 ]; then
		exit 1;
	fi
	exit 0
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

if [ "$USER_OPTION" == "val_tests" ]; then

	if [ -z "$2" ]; then
		the_val_tests
		if [ $? -ne 0 ]; then
			exit 1
		fi
	else
		the_val_tests "$2"
		if [ $? -ne 0 ]; then
			exit 1
		fi
	fi

fi


if [ "$USER_OPTION" == "re" ]; then
	make fclean
	make COMPILE=binary -j$(nproc)
	exit 0
fi

if [ "$USER_OPTION" == "val_run" ]; then
	if [ -z "$2" ]; then
		echo -e "\033[1;31mERROR : Insert the configuration file as a parameter after ( val_run ) parameter \033[0m"
		exit 1
	fi

	local configuration_file=$2

	make COMPILE=binary -j$(nproc)
	valgrind --error-exitcode=1 --exit-on-first-error=yes --leak-check=full --track-fds=yes ./webserv "$configuration_file"
	if [ $? -eq 1 ]; then
		echo -e "\033[1;31mVALGRIND : Code failed to pass valgrind! (memory leak or open file descriptor) \033[0m"
		exit 1
	fi

fi

if [ "$USER_OPTION" == "ci" ]; then
    make fclean
    if [ $? -ne 0 ]; then
		echo -e "\033[1;31m (CI) Webserv: Error trying to clean the project\033[0m"
		exit 1
	fi

	make COMPILE=binary -j$(nproc)
    if [ $? -ne 0 ]; then
		echo -e "\033[1;31m (CI) Webserv: Error trying to compile the project\033[0m"
		exit 1
	fi

	the_val_tests
	if [ $? -ne 0 ]; then
		echo -e "\033[1;31m (CI) Webserv: Error in the tests \033[0m"
		exit 1
	fi
fi

echo -e "\033[1;31m This option is invalid \033[0m"