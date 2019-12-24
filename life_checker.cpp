/*******************************************************************************
*                                  life checker
*                             =====================
* File Name: life_checker.cpp
* Related files: life_checker.hpp
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 10.12.19
* Last update: 24.12.19
*******************************************************************************/


/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                      standard  directories */

#include <signal.h> // sigaction
#include <iostream> // std::cout
#include <functional>
#include <stdio.h>
/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */
#include "./include/life_checker.hpp" 

#define UNUSED(x) (void)(x)
namespace med
{
sig_atomic_t revive_threshold = 5;
/*============================================================================*/
/*                                                   static memers definition */
/*                                                   ~~~~~~~~~~~~~~~~~~~~~~~~ */
const std::string LifeChecker::file_name = "./watch_dog_proc.out";
const std::string LifeChecker::watch_dog_sem_name = "/watch_dog_sem";
const std::string LifeChecker::client_sem_name = "/client_sem";

/*============================================================================*/
/*                                  LifeChecker                               */
/*============================================================================*/
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                               special functions                            */
/*                               ~~~~~~~~~~~~~~~~~                            */
/*  									                   Constructor / ctor */
/*                                                         ~~~~~~~~~~~~~~~~~~ */
LifeChecker::LifeChecker(pid_t partner_pid,
                        char *partner_args[], 
                        std::string partner_exec_name, 
                        int is_first_run): 
                              m_scheduler(),
                              m_partner_pid(partner_pid),
                              m_partner_args(partner_args),
                              m_partner_exec_name(partner_exec_name),
                              m_name_semaphore{}
                            
{
    set_signal_handlers();
    set_schedular_for_comunication();

    
    int return_value = SUCCESS;

/*  if (0 != is_first_run)
    {
        return_value += wait_for_partner();
    } */

    
    return_value += m_scheduler.execute_schedule();
    puts("scheduler executing");
}

/*============================================================================*/
/*                     API functions / Public member functions                */
/*============================================================================*/
/*                                                                  FUnctionE */
/*                                                                  ~~~~~~~~~ */
pid_t LifeChecker::get_partner_pid(void)
{
    return (m_partner_pid);
}
        
/*----------------------------------------------------------------------------*/
/*                      Auxiliary functions for FUnctionE                     */
/*----------------------------------------------------------------------------*/
/*                                                                  FUnctionE */

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  FUnctionF */
/*                                                                  ~~~~~~~~~ */
void LifeChecker::stop_live_checking(void)
{
    m_scheduler.stop();
}
/*----------------------------------------------------------------------------*/
/*                      Auxiliary functions for FUnctionF                     */
/*----------------------------------------------------------------------------*/
/*                                                                  FUnctionF */

/*============================================================================*/
/*                             auxiliary functions                            */
/*============================================================================*/
/*                                                                  FUnctionG */
/*                                                                  ~~~~~~~~~ */

// TODO: throw error handling
// TODO: sa_sigaction and memberfunction
void LifeChecker::set_signal_handlers(void)
{
    struct sigaction sigusr1 = {};
    struct sigaction sigusr2 = {};



    // all previous set signals to be blocked until signal handler is finished
    // are removed from the set 
    sigemptyset(&sigusr1.sa_mask);
    sigemptyset(&sigusr2.sa_mask);

    // flags are restarted 
    sigusr1.sa_flags = SA_RESTART | SA_SIGINFO;
    sigusr2.sa_flags = SA_RESTART | SA_SIGINFO;


    // all desired signals to be blocked until signal handler is finished are
    // set. 
    sigaddset(&sigusr1.sa_mask, SIGUSR1);
    sigaddset(&sigusr2.sa_mask, SIGUSR2);

    // Action to be taken when specified signal received is set at sigaction
    // struct
    // TODO: if this-> will compile then no need for global revive_threshold
    //
    // std::mem_fun(&LifeChecker::siguser1_handler, this);
    sigusr1.sa_sigaction = siguser1_handler;
    sigusr2.sa_sigaction = siguser2_handler;

    // signal handler with specified signal are bound to sigaction struct
    sigaction(SIGUSR1, &sigusr1, nullptr);
    sigaction(SIGUSR2, &sigusr2, nullptr);

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  FUnctionG */
/*                                                                  ~~~~~~~~~ */
int LifeChecker::set_schedular_for_comunication(void)
{
    std::shared_ptr <STask<size_t>> task_1 =    
             m_scheduler.add_task(std::bind(&LifeChecker::i_am_alive, this), 1);

    std::shared_ptr <STask<size_t>> task_2 =                              
       m_scheduler.add_task(std::bind(&LifeChecker::is_partner_alive, this), 1);

    if (task_1->get_uid().is_bad_id() ||
        task_2->get_uid().is_bad_id() ||
        task_1 == task_2)
    {
        throw (std::runtime_error("failed to add tasks to scheduler"));
        return(FAILURE);
    }

    return (SUCCESS);
}

/*----------------------------------------------------------------------------*/
/*                      Auxiliary functions for FUnctionG                     */
/*----------------------------------------------------------------------------*/
/*                                                                  FUnctionG */

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  FUnctionH */
/*                                                                  ~~~~~~~~~ */
int LifeChecker::wait_for_partner(void)
{
    m_name_semaphore[WATCH_DOG] = sem_open(watch_dog_sem_name.c_str(), O_CREAT, S_IRUSR | S_IWUSR, 0);
    m_name_semaphore[CLIENT] = sem_open(client_sem_name.c_str(), O_CREAT, S_IRUSR | S_IWUSR, 0);

    if (SEM_FAILED == m_name_semaphore[WATCH_DOG] || SEM_FAILED == m_name_semaphore[CLIENT])
    {
        return (FAILURE);
    }
    
    // TODO: was done with strcmp 
    if (m_partner_exec_name == file_name)
    {
        sem_post(m_name_semaphore[CLIENT]);
        sem_wait(m_name_semaphore[WATCH_DOG]); 
    }
    else  /* partner is client */
    {
        sem_post(m_name_semaphore[WATCH_DOG]);
        sem_wait(m_name_semaphore[CLIENT]); 
    }

    sem_close(m_name_semaphore[WATCH_DOG]);
    sem_close(m_name_semaphore[CLIENT]);

    /* unlink only once */
    // TODO: mot sure about this if statemnt
    if (m_partner_exec_name == file_name)
    {
        sem_unlink(watch_dog_sem_name.c_str());
        sem_unlink(client_sem_name.c_str());
    }

    return (SUCCESS);
}

/*----------------------------------------------------------------------------*/
/*                      Auxiliary functions for FUnctionH                     */
/*----------------------------------------------------------------------------*/
/*                                                                  FUnctionH */

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  FUnctionI */
/*                                                                  ~~~~~~~~~ */
int LifeChecker::i_am_alive(void)
{
    
    kill(m_partner_pid, SIGUSR1);
    
    return (SUCCESS);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  FUnctionI */
/*                                                                  ~~~~~~~~~ */
int LifeChecker::is_partner_alive(void)
{
    if (0 == revive_threshold)
    {
        revive_partner();
    }
    else
    {
        --revive_threshold;
    }

    return (SUCCESS);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  FUnctionI */
/*                                                                  ~~~~~~~~~ */
//TODO: what about stopping the scheduler?
void LifeChecker::revive_partner(void)
{
    pid_t new_pid = 0;
    // threshold is reset
    revive_threshold = 5;

    new_pid = fork();

    if (0 == new_pid)  // this is the child.
    {
        execv(m_partner_exec_name.c_str(), m_partner_args);
    }
    else // this is the parent.
    {
        m_partner_pid = new_pid;
    }
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  FUnctionI */
/*                                                                  ~~~~~~~~~ */
void LifeChecker::siguser1_handler(int signal_number,
                   siginfo_t *sending_signal_info,
                   void *data)
{
    UNUSED(data);
    //data
    // a single received from the partner so he is a live and 
    // revive_threshold is reset to defult value.

    revive_threshold = 5;
    std::cout << "process " 
                << getpid()
                << " got signal number "
                << signal_number
                << " from process id "
                << sending_signal_info->si_pid
                << std::endl;
}


void LifeChecker::siguser2_handler(int signal_number,
                siginfo_t *sending_signal_info,
                void *data)
{
    UNUSED(data);
    std::cout << "process " 
                << getpid()
                << " got signal number "
                << signal_number
                << " from process id "
                << sending_signal_info->si_pid
                << std::endl;
}

/*----------------------------------------------------------------------------*/
/*                      Auxiliary functions for FUnctionI                     */
/*----------------------------------------------------------------------------*/
/*                                                                  FUnctionI */

} // namespace med