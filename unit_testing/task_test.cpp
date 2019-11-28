/*******************************************************************************
*                                       task
*                             =====================
* File Name: task_test.cpp
* Related files: task.cpp task.hpp
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 28.11.19
* Last update: 28.11.19
*******************************************************************************/


/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                      standard  directories */
/*                                                      ~~~~~~~~~~~~~~~~~~~~~ */
#include <iostream> // std::cout
#include <unistd.h> // sleep()
/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */
#include "../include/task.hpp"
using namespace med;

/*============================================================================*/
/*                                                                     Macros */
/*                                                                     ~~~~~~ */
#define UNUSED(x) (void)(x);

/*============================================================================*/
/*                             ~~~~~~~~~~~~~~~~~~~                            */
/*                             Forward declaration                            */
/*                             ~~~~~~~~~~~~~~~~~~~                            */
/*                                                                 Unit tests */
/*                                                                 ~~~~~~~~~~ */
static void unit_test_run(void);
static void Unit_test_update_time(void);
static void unit_test_get_time_to_execute(void);
static void unit_test_get_uid(void);

/*                                                           Integration Test */ 
/*                                                           ~~~~~~~~~~~~~~~~ */  
   
/*============================================================================*/
/*                                                              User function */
/*                                                              ~~~~~~~~~~~~~ */
int UserPrint(void* param);

/*============================================================================*/

int main()
{
    unit_test_run();
    Unit_test_update_time();
    unit_test_get_time_to_execute();
    unit_test_get_uid();
  
    return (0);
}

/*============================================================================*/
/*                                  unit_tests                                */
/*============================================================================*/
/*                                                              unit_test_run */
/*                                                              ~~~~~~~~~~~~~ */
static void unit_test_run(void)
{  
    std::cout << "================= unit_test_run ================"<< std::endl;

    std::cout << "One task will be executed "
              <<  "# All glory to the Hypnotoad # should be printed on screen"
              << std::endl;

    STask task(UserPrint, 5);
    task.execute();

    std::cout << "================================================"<< std::endl
              << std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                      Unit_test_update_time */
/*                                                      ~~~~~~~~~~~~~~~~~~~~~ */
static void Unit_test_update_time(void)
{
    std::cout << "============ Unit_test_update_time ============="<< std::endl;    
    STask task(UserPrint, 5);

        std::cout << "current time after ctor should be zero: " 
              << task.get_time_to_execute()
              << std::endl;

        task.update_time();

        std::cout << "time after first update: "
                  << task.get_time_to_execute()
                  << std::endl;
        sleep(1);
        task.update_time();

        std::cout << "time after second update: "
                  << task.get_time_to_execute()
                  << std::endl;

    std::cout << "================================================"<< std::endl
              << std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                              unit_test_get_time_to_execute */
/*                                              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
static void unit_test_get_time_to_execute(void)
{
    std::cout << "========= unit_test_get_time_to_execute ========"<< std::endl;    
    
    STask task(UserPrint, 5);
    std::cout << "current time after ctor should be zero: " 
              << task.get_time_to_execute()
              << std::endl;

    std::cout << "================================================"<< std::endl
              << std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                          unit_test_get_uid */
/*                                                          ~~~~~~~~~~~~~~~~~ */
static void unit_test_get_uid(void)
{
    std::cout << "================ unit_test_get_uid ============="<< std::endl;    
    
    STask task(UserPrint, 5);
    task.get_uid().print_uid();

    std::cout << "================================================"<< std::endl
              << std::endl;
}

/*============================================================================*/
/*                                   User function                            */             
/*============================================================================*/
/*                                                                            */
int UserPrint(void *param)
{
    UNUSED(param); 

    printf("# All glory to the Hypnotoad #\n");
    
    return (0);
} 
