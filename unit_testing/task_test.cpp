/*******************************************************************************
*                                       task
*                             =====================
* File Name: task_test.cpp
* Related files: task.cpp task.hpp
* #Version: V 1.1
* Writer: Kobi Medrish       
* Created: 28.11.19
* Last update: 3.12.19
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
static void unit_test_execute(void);
static void Unit_test_update_time_to_execute(void);
static void unit_test_get_time_to_execute(void);
static void unit_test_get_uid(void);
static void unit_test_operator_equal(void);

/*============================================================================*/
/*                                                              User function */
/*                                                              ~~~~~~~~~~~~~ */
int user_print(void* param);

/*============================================================================*/

int main()
{
    unit_test_execute();
    Unit_test_update_time_to_execute();
    unit_test_get_time_to_execute();
    unit_test_get_uid();
    unit_test_operator_equal();
  
    return (0);
}

/*============================================================================*/
/*                                  unit_tests                                */
/*============================================================================*/
/*                                                          unit_test_execute */
/*                                                          ~~~~~~~~~~~~~~~~~ */
static void unit_test_execute(void)
{  
    std::cout << "===================== unit_test_execute ====================="
              << std::endl;

    std::cout << "One task will be executed "
              <<  "# All glory to the Hypnotoad # should be printed on screen"
              << std::endl;

    STask task(user_print, 5);
    task.execute();

    std::cout << "================================================"<< std::endl
              << std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                           Unit_test_update_time_to_execute */
/*                                           ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
static void Unit_test_update_time_to_execute(void)
{
    std::cout << "=========== Unit_test_update_time_to_execute ================"
              << std::endl;    

    STask task(user_print, 5);

    std::cout << "current time after ctor should be zero: " 
            << task.get_time_to_execute()
            << std::endl;

    task.update_time_to_execute();

    std::cout << "time after first update: "
                << task.get_time_to_execute()
                << std::endl;
    sleep(1);
    task.update_time_to_execute();

    std::cout << "time after second update: "
                << task.get_time_to_execute()
                << std::endl;

    std::cout << "============================================================="
              << std::endl
              << std::endl
              << std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                              unit_test_get_time_to_execute */
/*                                              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
static void unit_test_get_time_to_execute(void)
{
    std::cout << "=============== unit_test_get_time_to_execute ==============="
              << std::endl;    
    
    STask task(user_print, 5);
    std::cout << "current time after ctor should be zero: " 
              << task.get_time_to_execute()
              << std::endl;

    std::cout << "============================================================="
              << std::endl
              << std::endl
              << std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                          unit_test_get_uid */
/*                                                          ~~~~~~~~~~~~~~~~~ */
static void unit_test_get_uid(void)
{
    std::cout << "======================== unit_test_get_uid =================="
              << std::endl;    
    
    STask task(user_print, 5);
    task.get_uid().print_uid();

    std::cout << "============================================================="
              << std::endl
              << std::endl
              << std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                          unit_test_get_uid */
/*                                                          ~~~~~~~~~~~~~~~~~ */
static void unit_test_operator_equal(void)
{
    std::cout << "================= unit_test_operator_equal =================="
              << std::endl;    
    
    STask task_1(user_print, 5);
    STask task_2(user_print, 10);


    std::cout << "~~~~~~~~~ task_1 == task_2 test ~~~~~~~~~~~~~~~" << std::endl;
    if (task_1 == task_2)
    {
        std::cout << "operator== FAIL" << std::endl;
    }
    else
    {
        std::cout << "operator== SUCCESS" << std::endl;
    }

    std::cout << "~~~~~~~~~ task_1 == task_1 test ~~~~~~~~~~~~~~~" << std::endl;
    if (task_1 == task_1)
    {
        std::cout << "operator== SUCCESS" << std::endl;    
    }
    else 
    {
        std::cout << "operator== FAIL" << std::endl;
    }
    
    std::cout << "============================================================="
              << std::endl
              << std::endl
              << std::endl;
}

/*============================================================================*/
/*                                   User function                            */             
/*============================================================================*/
/*                                                                            */
/*                                                                  user_print */
/*                                                                  ~~~~~~~~~ */
int user_print(void *param)
{
    UNUSED(param); 

    printf("# All glory to the Hypnotoad #\n");
    
    return (0);
} 
