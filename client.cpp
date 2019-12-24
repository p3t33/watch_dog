/*******************************************************************************
*                                     client
*                             =====================
* File Name: client.cpp
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 22.12.19
* Last update: 24.12.19
*******************************************************************************/

#include <stdio.h> /* printf */
#include <unistd.h> /* sleep */
#include <iostream> // std::cout
#include "./include/watch_dog.hpp" 

/*============================================================================*/
/*                                                                     Colors */
/*                                                                     ~~~~~~ */
const char* const green = "\033[1;32m";
const char* const red = "\033[1;31m";
const char* const reset = "\033[0m"; 
const char* const blue = "\033[1;34m";
/*============================================================================*/
using namespace med;

#define UNUSED(x) (void)(x)

int main(int argc, char *argv[])
{
    std::cout << green  << std::endl 
              <<"======== client.out started runing ========" << std::endl
              << "client PID " << getpid() << std::endl
              << "==========================================="
              << reset << std::endl;
              
	int counter = 0;
    UNUSED(argc);


    WatchDog watch_dog(argv);

    std::cout << "start of keep me alive" << std::endl;
    watch_dog.keep_me_alive();
    std::cout << "keep me alive is activated" << std::endl;

    printf("start client\n");
    while(1)
    {
    	sleep(1);
        printf("client round number: %d\n", counter);

        ++counter;
    }

    watch_dog.let_me_die();
 
    return(0);
}