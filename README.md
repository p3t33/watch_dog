# Watch dog

The watch dog is a service for monitoring a process and making sure it executes
properly, in case the monitored process fails to do so due to a crash the 
watch dog is responsible to lunch the process again. 

In my implementations I had two extra objectives
* usually only a small part of the process code is critical, and so there should
be an option to activate the watch dog just before entering the critical
section and disabling it just after it is over instead of monitoring the entire
execution of the process.
* In some rare cases the watch dog itself may crush and the monitored process
should be able to relaunch it again. the process and the watch dog should keep
each other safe.

There are 4 main files to this implementation
* **client.cpp** - will be compiled to a binary that is the monitored process,
    it will have some critical section to be monitored by the watch dog.
* **watch_dog_process.cpp** - will be compiled to a binary that is the watch dog
    service that will run in parallel with client.cpp and keep it safe.  
* **watch_dog.cpp** - is the API of the watch dog. 
* **life_checker.cpp** - is a shared library that is used to synchronies between
    client.out and watch_dog_process.out
      - big part of the synchronization is done by **scheduler.cpp** class that
        schedules the execution of tasks. client.out and watch_dog_process.out
        each has one and use its task to send and handle signals.


### Next on the Todo list

- [x] life checker
  - [ ] synchronization logic
  - [x]<del> implement scheduler</del> 
    - [x]<del> Task</del> 
      - [x]<del> UID + counter</del> 
      - [x]<del> priority queue</del> 
- [ ] client
- [ ] watch dog process
- [ ] watch dog API
- [ ] To add UML diagram.


### Getting Started
clone the project by typing in the command line:
```bash
git clone https://github.com/p3t33/watch_dog.git
```

### Compiling and running the server and clients
In order to compile source code to binary and run the 3 clients and server: 
```sh
./compile_and_run.sh
```
to compile ony:
```sh
./compile.sh
```

unit testing is available at ./unit_testing, to compile them:
```sh
./compile_unit_tests.sh
```
run each individual .out file to run the specific unit test.


### Compilers and operating systems
* Development was done on ubuntu 18.04 LTS OS.
* Source code was compiled with GNU g++ v7.4 and clang++ v6.0.0, std=11
* Tested for memory leaks using Valgrind v3.13.0

### Authors

**Kobi Medrish** - [p3t33](https://github.com/p3t33)

### License
Licensed under the [GPLv3](http://www.gnu.org/licenses/gpl-3.0.html) license.