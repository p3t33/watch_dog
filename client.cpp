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
#include <iostream> // std::cout
#include "./include/watch_dog.hpp" 


using namespace med;

#define UNUSED(x) (void)(x)

int main(int argc, char *argv[])
{
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