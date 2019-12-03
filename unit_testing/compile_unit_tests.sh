#compile uid unit tests

# uid test
g++ -std=c++11 -pedantic-errors -Wall -Wextra -g -o uid_test.out \
uid_test.cpp \
../uid.cpp

# task test
g++ -std=c++11 -pedantic-errors -Wall -Wextra -g -o task_test.out \
task_test.cpp \
../uid.cpp \
../task.cpp

# priority_queue.hpp
g++ -std=c++11 -pedantic-errors -Wall -Wextra -g -o priority_queue_test.out \
../uid.cpp \
../task.cpp \
priority_queue_test.cpp

