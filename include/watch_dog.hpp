#ifndef _WATCH_DOG_
#define _WATCH_DOG_
/*******************************************************************************
*                                    watch dog
*                             =====================
* File Name: watch_dog.hpp
* Related files: watch_dog.cpp
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 9.12.19
* Last update: 10.12.19
*******************************************************************************/


/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                      standard  directories */
/*                                                      ~~~~~~~~~~~~~~~~~~~~~ */

#include <semaphore.h> // sem_t
#include <string> // std::string
#include <thread> // std::thread
/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */

#include "life_checker.hpp"
/*============================================================================*/

namespace med
{

class WatchDog
{
    private:
    enum semaphore_type {CLIENT, WATCH_DOG};
    static const size_t buffer_size = 50;

    public:
        WatchDog(char *client_args[]);


        // Interface / API
        // ---------------------------------------------------------------------
        int keep_me_alive();
        void let_me_die();


    private:

         int create_watch_dog_checker_thread();
         void check_watch_dog();
        // managing variables
        // ---------------------------------------------------------------------
        LifeChecker* m_life_checker;
        std::thread m_thread;
        char **m_client_args;
        pid_t m_pid_wd;
        int m_return_val_thread_func;
        int m_is_first_run;
        sem_t m_thread_sem; // TODO: condition variole

};

} // namespace med
#endif // _WATCH_DOG_