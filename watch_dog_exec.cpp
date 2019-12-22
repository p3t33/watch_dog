#include <stdio.h>     /* fprintf() */
#include <signal.h>    /* sigaction(), kill() */
#include <unistd.h>    /* pid_t, getppid(), SIGUSR2 */
#include <stdlib.h>    /* exit() */

#include "include/life_checker.hpp"
#define UNUSED(x) (void)(x)
#define ENV_WD_IS_RUNNING "ENV_WD_IS_RUNNING"

using namespace med;
/*************************** extern functions declarations ********************/



/*************************** static functions declarations ********************/


/*************************** main *********************************************/

int main(int argc, char **argv)
{
    pid_t partner_pid = getppid();
    int is_first_run = 0;

    UNUSED(argc);


    if (NULL == getenv(ENV_WD_IS_RUNNING))  /* first run */
    {
        setenv(ENV_WD_IS_RUNNING, "1", 1); /* 1(non-zero) for overwrite */

        is_first_run = 1;
    }

    LifeChecker life_checker(partner_pid, argv, argv[0], is_first_run);

    /* watch_dog_exec.out (wd) was born via execv() in file watch_dog.c
       hence argv[0] == "./watch_dog_test.out" (client) */

        
    return (0);
}