# Creating dynamic library:
###########################
# position independent code object file is created.
g++ -std=c++11 -pedantic-errors -Wall -Wextra -g -c -fPIC \
life_checker.cpp scheduler.cpp uid.cpp -lpthread
# shared file created.
g++ -std=c++11 -pedantic-errors -Wall -Wextra -g -shared \
life_checker.o -o life.so

# clean all object files

# Creating static library no actual need for it
################################################
g++ -std=c++11 -pedantic-errors -Wall -Wextra -g -c \
scheduler.cpp uid.cpp

ar rcs libar.a *.o
ar -t libar.a

# compile binary to be used as the watch dog process 
g++ -std=c++11 -pedantic-errors -Wall -Wextra -g \
watch_dog_exec.cpp -o \
watch_dog_exec.out life.so libar.a -pthread


# compile binary to be used as the client that is wattched bt the watch dog process
g++ -std=c++11 -pedantic-errors -Wall -Wextra -g \
-o client.out \
client.cpp watch_dog.cpp scheduler.cpp uid.cpp life_checker.cpp -pthread

# remove object files
rm *.o

export LD_LIBRARY_PATH=$(pwd):$LD_LIBRARY_PATH