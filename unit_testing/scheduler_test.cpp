/*******************************************************************************
*                                    scheduler
*                             =====================
* File Name: scheduler_test.cpp
* Related files: scheduler.hpp scheduler.cpp
* #Version: V 1.1
* Writer: Kobi Medrish       
* Created: 28.11.19
* Last update: 5.12.19
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

#define UNUSED(x) (void)(x);
using namespace med;
/*============================================================================*/
/*                                                                      enums */
/*                                                                      ~~~~~ */


/*============================================================================*/
/*                                                                    structs */
/*                                                                    ~~~~~~~ */
 
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
static void unit_test_add(void);
static void Unit_test_y(void);
static void unit_test_z(void);
static void unit_test_k(void);
static void unit_test_m(void);
static void unit_test_a(void);
static void unit_test_b(void);
static void unit_test_c(void);
static void unit_test_d(void);
static void unit_test_e(void);

/*                                                           Integration Test */ 
/*                                                           ~~~~~~~~~~~~~~~~ */  
   
/*============================================================================*/
/*                                                              User function */
/*                                                              ~~~~~~~~~~~~~ */
int UserPrintInt(void *param);
int UserPrint(void *param);
int UserPrintOnce(void *param);
/*============================================================================*/

int main()
{
    unit_test_add();
    Unit_test_y();
    unit_test_z();
    unit_test_k();
    unit_test_m();
    unit_test_a();
    unit_test_b();
    unit_test_c();
    unit_test_d();
    unit_test_e();
  
    return (0);
}

/*============================================================================*/
/*                                 unit_test_s                                */
/*============================================================================*/
/*                                                              unit_test_add */
/*                                                              ~~~~~~~~~~~~~ */

static void unit_test_add(void)
{  
    std::cout << "======================== unit_test_add ======================"
              << std::endl;
    
    Scheduler scheduler;
    UID& task_uid = scheduler.add_task(UserPrint, 5);
    task_uid.print_uid();
    task_uid = scheduler.add_task(UserPrintOnce, 10);


    if (2 == scheduler.get_number_of_tasks())
    {
        std::cout << "num of tasks is 2 " << green << "SUCCESS" << reset
                  << std::endl;
    }
    else
    {
        std::cout << "num of tasks is 2 " << red << "SUCCESS" << reset
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
                  << red << "SUCCESS" << reset
                  << std::endl;
    }
    std::cout << "============================================================="
              << std::endl
              << std::endl
              << std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  Unit_test_y */
/*                                                                  ~~~~~~~~~ */
static void Unit_test_y(void)
{
    std::cout << "========================= Unit_test_y ======================="
              << std::endl;    
    

    std::cout << "============================================================="
              << std::endl
              << std::endl
              << std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  unit_test_z */
/*                                                                  ~~~~~~~~~ */
static void unit_test_z(void)
{
    std::cout << "=================== unit_test_z ================"<< std::endl;    
   

    std::cout << "============================================================="
              << std::endl
              << std::endl
              << std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  unit_test_k */
/*                                                                  ~~~~~~~~~ */
static void unit_test_k(void)
{
    std::cout << "=================== unit_test_k ================"<< std::endl;    
   

    std::cout << "============================================================="
              << std::endl
              << std::endl
              << std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  unit_test_m */
/*                                                                  ~~~~~~~~~ */
static void unit_test_m(void)
{
    std::cout << "=================== unit_test_m ================"<< std::endl;    
   

    std::cout << "============================================================="
              << std::endl
              << std::endl
              << std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  unit_test_a */
/*                                                                  ~~~~~~~~~ */
static void unit_test_a(void)
{
    std::cout << "=================== unit_test_a ================"<< std::endl;    
    

    std::cout << "============================================================="
              << std::endl
              << std::endl
              << std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  unit_test_b */
/*                                                                  ~~~~~~~~~ */
static void unit_test_b(void)
{
    std::cout << "=================== unit_test_b ================"<< std::endl;    
    

    std::cout << "============================================================="
              << std::endl
              << std::endl
              << std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  unit_test_c */
/*                                                                  ~~~~~~~~~ */
static void unit_test_c(void)
{
    std::cout << "=================== unit_test_c ================"<< std::endl;   

    std::cout << "============================================================="
              << std::endl
              << std::endl
              << std::endl;
              
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  unit_test_d */
/*                                                                  ~~~~~~~~~ */
static void unit_test_d(void)
{
    std::cout << "=================== unit_test_d ================"<< std::endl;    
   

    std::cout << "============================================================="
              << std::endl
              << std::endl
              << std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  unit_test_e */
/*                                                                  ~~~~~~~~~ */
static void unit_test_e(void)
{
    std::cout << "=================== unit_test_e ================"<< std::endl;    
    

    std::cout << "============================================================="
              << std::endl
              << std::endl
              << std::endl;
}


/*============================================================================*/
/*                                   User function                            */             
/*============================================================================*/
/*                                                                            */
int UserPrintOnce(void *param)
{
    UNUSED(param)
    printf("This massage should be printed only once\n");   

    /* Return value of <1> will execute this task only once */
    return (1);
}


int UserPrint(void *param)
{
    UNUSED(param); 

    printf("# All glory to the Hypnotodd #\n");
    
    /* Return value of <0> will execute this task indefinitely */
    return (0);
} 
  

// int UserPrintInt(void *param)

/* Will stop the scheduler by flipping the kill switch */
/* int CyanidePill(void *param)
{
    med::Scheduler::stop();

    return (0);
}  */
