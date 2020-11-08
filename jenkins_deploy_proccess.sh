#!/bin/sh

SUDO_PWD=user

echo "jenkins deploy"

echo "Hello Jenkins!"

echo $SUDO_PWD | sudo -S chmod 777 ${WORKSPACE}/Makefile

# test googletest
make gtest
#sudo ./test/bin/test_finance_tdd --gtest_output=xml

# output googletest result
make run_gtest_output

# exexute coverage test
make gcov

# clean build directory for cppcheck
make clean

# execute cppcheck
make cppcheck