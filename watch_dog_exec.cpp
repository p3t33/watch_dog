#include <stdio.h>     /* fprintf() */
#include <signal.h>    /* sigaction(), kill() */
#include <unistd.h>    /* pid_t, getppid(), SIGUSR2 */
#include <stdlib.h>    /* exit() */

#include <iostream>
#include "include/life_checker.hpp"
#define UNUSED(x) (void)(x)
#define ENV_WD_IS_RUNNING "ENV_WD_IS_RUNNING"

using namespace med;

/*============================================================================*/
/*                                                                     Colors */
/*                                                                     ~~~~~~ */
const char* const green = "\033[1;32m";
const char* const red = "\033[1;31m";
const char* const reset = "\033[0m"; 
const char* const blue = "\033[1;34m";


int main(int argc, char **argv)
{
    std::cout << blue << std::endl 
              << "======== watch_dog_exec.out started runing =====" << std::endl
              << "watch_dog PID " << getpid() << std::endl
              << "================================================"
              << reset << std::endl;
    
    std::cout << "watch_dog_process PID " << getpid() << std::endl; 
    pid_t partner_pid = getppid();

    int is_first_run = 0;

    UNUSED(argc);


    if (NULL == getenv(ENV_WD_IS_RUNNING))  /* first run */
    {
        setenv(ENV_WD_IS_RUNNING, "1", 1); /* 1(non-zero) for overwrite */

        is_first_run = 1;
    }

    LifeChecker life_checker(partner_pid, argv, argv[0], is_first_run);
   
    return (0);
}