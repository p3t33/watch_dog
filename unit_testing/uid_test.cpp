/*******************************************************************************
*                                       uid
*                             =====================
* File Name: uid.hpp
* Related files: uid.cpp counter.hpp
* #Version: V 1.2
* Writer: Kobi Medrish       
* Created: 27.11.19
* Last update: 3.12.19
*******************************************************************************/

/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                      standard  directories */
/*                                                      ~~~~~~~~~~~~~~~~~~~~~ */
#include <iostream>

/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */
#include "../include/uid.hpp"

/*============================================================================*/
/*                                                                       enum */
/*                                                                       ~~~~ */
enum status {STATUS_SUCCESS, STATUS_FAIL};
using namespace med;

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

    std::cout << (result ? "Fail" : "Success") << std::endl;

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

    std::cout << (result ? "Fail" : "Success") << std::endl;

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
