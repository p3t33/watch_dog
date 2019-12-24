/*******************************************************************************
*                                    watch dog
*                             =====================
* File Name: watch_dog.cpp
* Related files: watch_dog.hpp
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 9.12.19
* Last update: 24.12.19
*******************************************************************************/


/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                      standard  directories */
/*                                                      ~~~~~~~~~~~~~~~~~~~~~ */
#include <iostream>
#include <stdio.h>
/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */
#include "./include/watch_dog.hpp"
/*============================================================================*/
/*                                                                     Macros */
/*                                                                     ~~~~~~ */
#define BUF_LEN 50
#define DEC_BASE 10



/*============================================================================*/
/*                                                                    structs */
/*                                                                    ~~~~~~~ */
namespace med
{
/*============================================================================*/
/*                                                   static memers definition */
/*                                                   ~~~~~~~~~~~~~~~~~~~~~~~~ */
const std::string WatchDog::watch_dog_environment_variable_name = "ENV_WATCH_DOG_PID";
const std::string WatchDog::watch_dog_executable_name = "./watch_dog_exec.out";


/*============================================================================*/
/*                                  Class name                                */
/*============================================================================*/
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                               special functions                            */
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                                                         Constructor / ctor */
/*                                                         ~~~~~~~~~~~~~~~~~~ */
WatchDog::WatchDog(char *client_args[]):
                  m_life_checker(nullptr),
                  m_thread(),
                  m_client_args(client_args),
                  m_pid_wd(),
                  m_return_val_thread_func(0),
                  m_is_first_run(1), // 1 = first run
                  m_thread_sem{0}
            

{



}


/*============================================================================*/
/*                     API functions / Public member functions                */
/*============================================================================*/
/*                                                                  FUnctionE */
/*                                                                  ~~~~~~~~~ */
void WatchDog::keep_me_alive()
{
    char buff[buffer_size] = {0};
    

    if (nullptr == getenv(watch_dog_environment_variable_name.c_str())) 
    // if true this is the first run - no watchdog is running
    {
        m_is_first_run = 1;

        m_pid_wd = fork();

        sprintf(buff, "%d", m_pid_wd);
        setenv(watch_dog_environment_variable_name.c_str(), buff, 1);/*1(non-zero) to overwrite*/

        if (0 == m_pid_wd)  /* child --> watchdog */
        {
            execv(watch_dog_executable_name.c_str(), (char **)m_client_args); 
        }
    }
    else
    {
        m_is_first_run = 0;

        /* client was created by watchdog, watchdog is parent of client */
        m_pid_wd = getppid();
    }

    create_watch_dog_checker_thread();
    
}


                                          
/*----------------------------------------------------------------------------*/
/*                      Auxiliary functions for FUnctionE                     */
/*----------------------------------------------------------------------------*/
/*                                                                  FUnctionE */

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  FUnctionF */
/*                                                                  ~~~~~~~~~ */
void WatchDog::let_me_die()
{
    kill(m_life_checker->get_partner_pid(), SIGUSR2);
    m_life_checker->stop_live_checking();

    // TODO: maybe a better place would be in the dtor
    m_thread.join();
}





/*----------------------------------------------------------------------------*/
/*                      Auxiliary functions for FUnctionF                     */
/*----------------------------------------------------------------------------*/
/*                                                                  FUnctionF */

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  FUnctionG */
/*                                                                  ~~~~~~~~~ */

/*----------------------------------------------------------------------------*/
/*                      Auxiliary functions for FUnctionG                     */
/*----------------------------------------------------------------------------*/
/*                                                                  FUnctionG */

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  FUnctionH */
/*                                                                  ~~~~~~~~~ */

/*----------------------------------------------------------------------------*/
/*                      Auxiliary functions for FUnctionH                     */
/*----------------------------------------------------------------------------*/
/*                                                                  FUnctionH */

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  FUnctionI */
/*                                                                  ~~~~~~~~~ */
/*----------------------------------------------------------------------------*/
/*                      Auxiliary functions for FUnctionI                     */
/*----------------------------------------------------------------------------*/
/*                                                                  FUnctionI */
int WatchDog::create_watch_dog_checker_thread()
{
    m_thread = std::thread(&WatchDog::check_watch_dog, this);
     

    sem_post(&m_thread_sem);
    
    return (0);
}
void WatchDog::check_watch_dog()
{

    /* client's main thread must wait the thread that ping-pong with watchdog */
    sem_wait(&m_thread_sem); 

    m_life_checker = new LifeChecker(m_pid_wd, m_client_args, watch_dog_executable_name.c_str(), m_is_first_run);
}
} // namespace med
