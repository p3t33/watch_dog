#ifndef _LIFE_CHECKER_
#define _LIFE_CHECKER_
/*******************************************************************************
*                                  life checker
*                             =====================
* File Name: life_checker.hpp
* Related files: life_checker.cpp
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 10.12.19
* Last update: 11.12.19
*******************************************************************************/


/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                      standard  directories */
/*                                                      ~~~~~~~~~~~~~~~~~~~~~ */

#include <semaphore.h> // sem_t
#include <string> // std::string
#include <thread> // std::thread
#include  <sys/types.h> //pid_t
#include <csignal> // std::sig_atomic_t
#include <string> // std::string

#include <fcntl.h>      /* O_CREAT */
#include <sys/stat.h>   /* S_IRUSR, S_IWUSR */
/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */
#include "scheduler.hpp"

/*============================================================================*/

namespace med
{

//TODO: without the static I have multiply definition.
sig_atomic_t revive_threshold = 5;

class LifeChecker
{
    private:
    enum semaphore_type {CLIENT, WATCH_DOG};
    enum status {SUCCESS, FAILURE};

    static const size_t buffer_length = 50;
    // number of times the partner on the other side have not sent a signal
    //static const size_t revive_threshold = 5;

/*     static constexpr const char* file_name = "./watch_dog_proc.out";
    static constexpr const  char* watch_dog_sem = "/watch_dog_sem";
    static constexpr const  char* client_sem = "/client_sem"; */

    // used to store file and named semaphores names.
    static const std::string file_name;
    static const std::string watch_dog_sem;
    static const std::string client_sem;

    public:
        LifeChecker(pid_t partner_pid,
                    char *partner_args[], 
                    std::string partner_exec_name, 
                    int is_first_run);

        // Interface / API
        // ---------------------------------------------------------------------
        pid_t get_partner_pid(void);
        void stop_live_checking(void);

    private:
        // auxiliary functions
        // ---------------------------------------------------------------------

        // ctor 
        /* fill schedular with task_i_alive and task_partner_alive */
        void set_signal_handlers(void);
        int set_schedular_for_comunication(void);

        /* wait for partner to start sending and handeling SIGUSR1 together 
        (wd and client) */
        int wait_for_partner(void);

        // tasks to be added to scheduler 
        int i_am_alive(void); // signles the partner that this side is alive.

        // This task counts backwards from the predefined threshold and it is
        // met revives the partner. 
        int is_partner_alive(void); 

        /* the main feature of this program */
        void revive_partner(void);

        /* handle SIGUSR1, which represents that partner is alive */
        static void siguser1_handler(int signal_number,
                              siginfo_t *sending_signal_info,
                              void *data);
        static void siguser2_handler(int signal_number,
                        siginfo_t *sending_signal_info,
                        void *data);

        


        // managing variables
        // ---------------------------------------------------------------------
        Scheduler m_scheduler;
        pid_t m_partner_pid; // pid of the other side of the "communication"
        char **m_partner_args;
        std::string m_partner_exec_name;
        sem_t *m_name_semaphore[2];
};

} // namespace med
#endif // _LIFE_CHECKER_