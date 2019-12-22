/*******************************************************************************
*                                     client
*                             =====================
* File Name: client.cpp
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 22.12.19
* Last update: 22.12.19
*******************************************************************************/

#include <stdio.h> /* printf */
#include <unistd.h> /* sleep */
#include "./include/watch_dog.hpp" 

using namespace med;

#define UNUSED(x) (void)(x)

int main(int argc, char *argv[])
{
	int counter = 0;
    UNUSED(argc);

    WatchDog watch_dog(argv);

    // start of critical code section
    watch_dog.keep_me_alive();

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