/*******************************************************************************
*                                    scheduler
*                             =====================
* File Name: scheduler_test.cpp
* Related files: scheduler.hpp scheduler.cpp
* #Version: V 1.1
* Writer: Kobi Medrish       
* Created: 28.11.19
* Last update: 8.12.19
*******************************************************************************/

// create and destroy tested via valgrind
/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                      standard  directories */
/*                                                      ~~~~~~~~~~~~~~~~~~~~~ */
#include <iostream>
#include <stdio.h> /* printf */
/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */
#include "../include/scheduler.hpp"
using namespace med;
/*============================================================================*/
/*                                                                     Macros */
/*                                                                     ~~~~~~ */
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

/*                                                           Integration Test */ 
/*                                                           ~~~~~~~~~~~~~~~~ */  
   
/*============================================================================*/
/*                                                              User function */
/*                                                              ~~~~~~~~~~~~~ */
int UserPrint(void);
int UserPrintOnce(void);
int poison_pill_task(void);
/*============================================================================*/

int main()
{
/*     unit_test_add_task();
    Unit_test_remove_task(); */
    unit_test_execute_schedule();

  
    return (0);
}

/*============================================================================*/
/*                                 unit_test_s                                */
/*============================================================================*/
/*                                                              unit_test_add_task */
/*                                                              ~~~~~~~~~~~~~ */

static void unit_test_add_task(void)
{  
    std::cout << "======================== unit_test_add_task ======================"
              << std::endl;
    
    Scheduler scheduler;
    std::shared_ptr<STask<size_t>> task_uid = scheduler.add_task(UserPrint, 5);
    task_uid.get()->execute();

    std::cout << "print out of the UID of the added task" << std::endl;
           
    task_uid.get()->get_uid().print_uid();
    task_uid = scheduler.add_task(UserPrintOnce, 10);
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

    if (true == scheduler.is_empty())
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
/*                                                                  Unit_test_remove_task */
/*                                                                  ~~~~~~~~~ */
static void Unit_test_remove_task(void)
{
    std::cout << "========================= Unit_test_remove_task ======================="
              << std::endl;    
    
    Scheduler scheduler;
    std::shared_ptr<STask<size_t>> task_1 (new STask<size_t>(UserPrintOnce, 5));
    
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
    
    std::shared_ptr<STask<size_t>> task_2 = scheduler.add_task(UserPrint, 5);
    std::shared_ptr<STask<size_t>> 
                                 task_3 = scheduler.add_task(UserPrintOnce, 10);
    

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
/*                                                                  unit_test_execute_schedule */
/*                                                                  ~~~~~~~~~ */
static void unit_test_execute_schedule(void)
{
    std::cout << "============== unit_test_execute_schedule ================"<< std::endl;    
   
    Scheduler scheduler;

    printf("===================== SCHRun print log ====================\n\n");

    //scheduler.add_task(UserPrintOnce, 10);
/*     scheduler.add_task(UserPrint, 5);
    scheduler.add_task(UserPrintOnce, 15); */

/*     if (0 == scheduler.execute_schedule())
    {
        std::cout << "empty scheduler run as expected " 
                  << green << "SUCCESS" << reset
                  << std::endl;    
    }
    else
    {
 
        std::cout << "empty scheduler run as expected " 
                  << green << "FAILURE" << reset
                  << std::endl;    

    } */
    
    scheduler.add_task(UserPrintOnce, 8);
    scheduler.add_task(UserPrint, 2);
    scheduler.add_task(poison_pill_task, 20);


    scheduler.execute_schedule();


    std::cout << "============================================================="
              << std::endl
              << std::endl
              << std::endl;
}



/*============================================================================*/
/*                                   User function                            */             
/*============================================================================*/
/*                                                                            */
int UserPrintOnce(void)
{
    printf("This massage should be printed only once\n");   

    /* Return value of <1> will execute this task only once */
    return (1);
}


int UserPrint(void)
{
    printf("# All glory to the Hypnotodd #\n");
    
    /* Return value of <0> will execute this task indefinitely */
    return (0);
} 
  

// int UserPrintInt(void *param)

/* Will stop the scheduler by flipping the kill switch */
int poison_pill_task(void)
{
    std::cout << "time to stop the scheduler" << std::endl;

    return (-1);
} 
