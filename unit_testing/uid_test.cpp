/*******************************************************************************
*                                       uid
*                             =====================
* File Name: uid.hpp
* Related files: uid.cpp counter.hpp
* #Version: V 1.2
* Writer: Kobi Medrish       
* Created: 27.11.19
* Last update: 9.12.19
*******************************************************************************/


/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                      standard  directories */
/*                                                      ~~~~~~~~~~~~~~~~~~~~~ */
#include <iostream> // std::cout

/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */
#include "../include/uid.hpp"
using namespace med;

/*============================================================================*/
/*                                                                       enum */
/*                                                                       ~~~~ */
enum status {STATUS_SUCCESS, STATUS_FAIL};

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
static void unit_test_is_same_id(void);
static void unit_test_print_uid(void);
static void unit_test_is_bad_id(void);

/*============================================================================*/

int main()
{
    unit_test_is_same_id();
    unit_test_is_bad_id();
    unit_test_print_uid();
  
    return (0);
}


/*============================================================================*/
/*                                  unit_tests                                */
/*============================================================================*/
/*                                                       unit_test_is_same_id */
/*                                                       ~~~~~~~~~~~~~~~~~~~~ */

static void unit_test_is_same_id(void)
{  
    std::cout << "==================== unit_test_is_same_id ==================="
              << std::endl;

    UID uid1;
    UID uid2;
    size_t result = STATUS_SUCCESS;
    
    std::cout << "unit_test_is_same_id() : ";     

    if (true == (uid1 == (uid2)))
    {
        result = STATUS_FAIL;
    }  

    if (false == (uid1 == uid1))
    {
        result = STATUS_FAIL;
    }

    if (false == (uid2 == uid2))
    {
        result = STATUS_FAIL;
    }

    if (STATUS_SUCCESS == result)
    {
        std::cout << green << "SUCCESS" << reset << std::endl;
    }
    else
    {
        std::cout << red << "FAILURE" << reset << std::endl;
    }
    
    std::cout << "============================================================="
              << std::endl
              << std::endl
              << std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                        unit_test_is_bad_id */
/*                                                        ~~~~~~~~~~~~~~~~~~~ */
static void unit_test_is_bad_id(void)
{
    std::cout << "===================== unit_test_is_bad_id ==================="
              << std::endl;    
    
    UID uid1;
    UID uid2;
    size_t result = STATUS_SUCCESS;

    std::cout << "unit_test_is_bad_id() : "; 

    if (true == uid1.is_bad_id())
    {
        result = STATUS_FAIL;
    }
   
    if (true == uid2.is_bad_id())
    {
        result = STATUS_FAIL;
    }

    if (STATUS_SUCCESS == result)
    {
        std::cout << green << "SUCCESS" << reset << std::endl;
    }
    else
    {
        std::cout << red << "FAILURE" << reset << std::endl;
    } 

    std::cout << "============================================================="
              << std::endl
              << std::endl
              << std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                        unit_test_print_uid */
/*                                                        ~~~~~~~~~~~~~~~~~~~ */
static void unit_test_print_uid(void)
{
    std::cout << "====================== unit_test_print_uid =================="
              << std::endl;    
    
    UID uid1;
    UID uid2;
    
    uid1.print_uid();
    uid2.print_uid();

    std::cout << "============================================================="
              << std::endl
              << std::endl
              << std::endl;
}
