/*******************************************************************************
*                                    scheduler
*                             =====================
* File Name: scheduler_test.cpp
* Related files: scheduler.hpp scheduler.cpp
* #Version: V 1.1
* Writer: Kobi Medrish       
* Created: 28.11.19
* Last update: 9.12.19
*******************************************************************************/

// create and destroy tested via valgrind
/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                      standard  directories */
/*                                                      ~~~~~~~~~~~~~~~~~~~~~ */
#include <iostream> // std::cout

/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */
#include "../include/scheduler.hpp"
using namespace med;

/*============================================================================*/
/*                                                                     Colors */
/*                                                                     ~~~~~~ */
const char* const green = "\033[1;32m";
const char* const red = "\033[1;32m";
const char* const reset = "\033[0m"; 

/*============================================================================*/
/*                             ~~~~~~~~~~~~~~~~~~~                            */
/*                             Forward declaration                            */
/*                             ~~~~~~~~~~~~~~~~~~~                            */
/*                                                                 Unit tests */
/*                                                                 ~~~~~~~~~~ */
static void unit_test_add_task(void);
static void Unit_test_remove_task(void);
static void unit_test_execute_schedule(void);

/*============================================================================*/
/*                                                              User function */
/*                                                              ~~~~~~~~~~~~~ */
int user_print(void);
int user_print_once(void);
int poison_pill_task(void);

/*============================================================================*/

int main()
{
    unit_test_add_task();
    Unit_test_remove_task();
    unit_test_execute_schedule();
    return (0);
}

/*============================================================================*/
/*                                 unit_test_s                                */
/*============================================================================*/
/*                                                         unit_test_add_task */
/*                                                         ~~~~~~~~~~~~~~~~~~ */

static void unit_test_add_task(void)
{  
    std::cout << "==================== unit_test_add_task ====================="
              << std::endl;
    
    Scheduler scheduler;
    std::shared_ptr<STask<size_t>> task_uid = scheduler.add_task(user_print, 5);
    task_uid.get()->execute();

    std::cout << "print out of the UID of the added task" << std::endl;
           
    task_uid.get()->get_uid().print_uid();
    task_uid = scheduler.add_task(user_print_once, 10);
    task_uid.get()->get_uid().print_uid();

    if (2 == scheduler.get_number_of_tasks())
    {
        std::cout << "num of tasks is 2 " << green << "SUCCESS" << reset
                  << std::endl;
    }
    else
    {
        std::cout << "num of tasks is 2 " << red << "FAILURE" << reset
                  << std::endl;
    }

    if (false == scheduler.is_empty())
    {
        std::cout << "queue of tasks is not empty " 
                  << green << "SUCCESS" << reset
                  << std::endl;
    }
    else
    {
        std::cout << "queue of tasks is not empty "
                  << red << "FAILURE" << reset
                  << std::endl;
    }
    std::cout << "============================================================="
              << std::endl
              << std::endl
              << std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                      Unit_test_remove_task */
/*                                                      ~~~~~~~~~~~~~~~~~~~~~ */
static void Unit_test_remove_task(void)
{
    std::cout << "===================== Unit_test_remove_task ================="
              << std::endl;    
    
    Scheduler scheduler;

    std::shared_ptr<STask<size_t>> 
    task_1 (std::make_shared<STask<size_t>>(user_print_once, 5));

    
    if (nullptr == scheduler.remove_task(task_1))
    {
        std::cout << "removing a task from an empty queue " 
                  << green << "SUCCESS" << reset
                  << std::endl;    
    }
    else
    {
        std::cout << "removing a task from an empty queue" 
                  << green << "FAILURE" << reset
                  << std::endl; 
    }
    
    std::shared_ptr<STask<size_t>> task_2 = scheduler.add_task(user_print, 5);
    std::shared_ptr<STask<size_t>> 
                               task_3 = scheduler.add_task(user_print_once, 10);
    

    if (2 == scheduler.get_number_of_tasks())
    {
        std::cout << "num of tasks after adding 2 tasks " 
                  << green << "SUCCESS" << reset
                  << std::endl;
    }
    else
    {
        std::cout << "num of tasks  after adding 2 tasks  " 
                  << red << "FAILURE" << reset
                  << std::endl;
    }

    if (nullptr == scheduler.remove_task(task_1))
    {
        std::cout << "removing a task that is not in the list from the queue " 
                  << green << "SUCCESS" << reset
                  << std::endl;    
    }
    else
    {
        std::cout << "removing a task from an empty queue" 
                  << green << "FAILURE" << reset
                  << std::endl; 
    }


    task_1 = scheduler.remove_task(task_2);
    if (task_1 == task_2)
    {
        std::cout << "existing task in queue was removed  " 
                  << green << "SUCCESS" << reset
                  << std::endl;    
    }
    else
    {
        std::cout << "removing a task from an empty queue" 
                  << green << "FAILURE" << reset
                  << std::endl; 
    }

    scheduler.remove_task(task_3);


    if (0 == scheduler.get_number_of_tasks())
    {
        std::cout << "num of tasks after removing 2 tasks should be 0 " 
                  << green << "SUCCESS" << reset
                  << std::endl;
    }
    else
    {
        std::cout << "num of tasks  after removing 2 tasks should be 0" 
                  << red << "FAILURE" << reset
                  << std::endl;
    }

    std::cout << "============================================================="
              << std::endl
              << std::endl
              << std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                 unit_test_execute_schedule */
/*                                                 ~~~~~~~~~~~~~~~~~~~~~~~~~~ */
static void unit_test_execute_schedule(void)
{
    std::cout << "============ unit_test_execute_schedule ========"<< std::endl;    
   
    Scheduler scheduler;

    std::cout <<"~~~~~~~~~~~~~~~ schedule printout ~~~~~~~~~~~~~~~"<< std::endl;    

    scheduler.add_task(user_print, 5);
    scheduler.add_task(user_print_once, 2);
    scheduler.add_task(poison_pill_task, 20);

    scheduler.execute_schedule();

    std::cout << "============================================================="
              << std::endl
              << std::endl
              << std::endl;
}


/*============================================================================*/
/*                                  User function                             */             
/*============================================================================*/
/*                                                            user_print_once */
/*                                                            ~~~~~~~~~~~~~~~ */
int user_print_once(void)
{
    std::cout << "This massage should be first and printed only once"
              << std::endl;

    return (1);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                 user_print */
/*                                                                 ~~~~~~~~~~ */
int user_print(void)
{
    std::cout << "This massage should be printed indefinitely"
              << std::endl;
    return (0);
} 

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                           poison_pill_task */
/*                                                           ~~~~~~~~~~~~~~~~ */  
int poison_pill_task(void)
{
    std::cout << " this task stops the execution of scheduler" << std::endl;

    return (-1);
} 
