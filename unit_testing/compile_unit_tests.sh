#compile uid unit tests


g++ -std=c++11 -pedantic-errors -Wall -Wextra -g -o uid_test.out \
uid_test.cpp \
../uid.cpp