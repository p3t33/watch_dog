/*******************************************************************************
*                                 priority queue
*                             =====================
* File Name: priority_queue_test.cpp
* Related files: priority_queue.hpp
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 28.11.19
* Last update: 3.12.19
*******************************************************************************/
// Testing for handling of primitive type and objects.
// is_empty() , size() and clear() are just wrappers for std::vector functions
// and so were not tested.

/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                      standard  directories */
/*                                                      ~~~~~~~~~~~~~~~~~~~~~ */
#include <iostream>
#include <stdio.h> /* printf */
#include <cstring> // std::memcmp

/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */
#include "../include/priority_queue.hpp"
#include "../include/task.hpp"
#include "../include/counter.hpp"
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
static void unit_test_enqueue(void);
static void unit_test_dequeue(void);
static void unit_test_remove(void);
static void unit_test_peek(void);

/*============================================================================*/
/*                                                              User function */
/*                                                              ~~~~~~~~~~~~~ */
// Functions for PQ<STask>
// ~~~~~~~~~~~~~~~~~~~~~~~
bool compare_task(std::shared_ptr<STask> one, std::shared_ptr<STask> two);
void print_task_uid(std::vector<std::shared_ptr<STask>>& vector);

// Functions for PQ<size_t>
// ~~~~~~~~~~~~~~~~~~~~~~~~
bool compare_size_t(std::shared_ptr<size_t> one, std::shared_ptr<size_t> two);
void print_size_t(std::vector<std::shared_ptr<size_t>>& vector);

int user_print(void *param); // used for STask
/*============================================================================*/

int main()
{
    unit_test_enqueue();
    unit_test_dequeue();
    unit_test_remove();
    unit_test_peek();

    return (0);
}

/*============================================================================*/
/*                                  unit_tests                                */
/*============================================================================*/
/*                                                          unit_test_enqueue */
/*                                                          ~~~~~~~~~~~~~~~~~ */
static void unit_test_enqueue(void)
{  
    std::cout << "==================== unit_test_enqueue ======================"
              << std::endl;
    
    size_t arr[] = {1,8,5,6,3,4,0,9,7,2};

    std::cout <<"~~~~~~~~~~ test enqueue for size_t type ~~~~~~~~" << std::endl;
    PQ<size_t> pq(compare_size_t, print_size_t);
    for (size_t i = 0; i < 10; ++i)
    {
        pq.enqueue(std::make_shared<size_t>(arr[i]));
    }

    pq.print_row_data();

    std::cout << std::endl;

    std::cout <<"~~~~~~~~~~~~~ test enqueue for objects ~~~~~~~~~" << std::endl;
    PQ<STask> pq_task(compare_task, print_task_uid);
    pq_task.enqueue(std::shared_ptr<STask> (new STask(user_print, 5)));
    pq_task.enqueue(std::shared_ptr<STask> (new STask(user_print, 10)));
    pq_task.enqueue(std::shared_ptr<STask> (new STask(user_print, 15)));
    pq_task.enqueue(std::shared_ptr<STask> (new STask(user_print, 20)));
    pq_task.enqueue(std::shared_ptr<STask> (new STask(user_print, 25)));

    pq_task.print_row_data();

    std::cout << std::endl;  


    std::cout << "============================================================="
              << std::endl
              << std::endl
              << std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                          unit_test_dequeue */
/*                                                          ~~~~~~~~~~~~~~~~~ */
static void unit_test_dequeue(void)
{
    std::cout << "========================= unit_test_dequeue ================="
              << std::endl;    

    size_t arr[] = {1,8,5,6,3,4,9,7,2};

    std::cout <<"~~~~~~~~~~ test dequeue for size_t type ~~~~~~~~" << std::endl;
    PQ<size_t> pq(compare_size_t, print_size_t);
    for (size_t i = 0; i < 9; ++i)
    {
        pq.enqueue(std::make_shared<size_t>(arr[i]));
    }

    std::cout <<"~~~~~~~ list of size_t types before dequeue ~~~~" << std::endl;
    pq.print_row_data();

    std::cout << std::endl << std::endl;
    std::cout <<"~~~~~~~ start of dequeue ~~~~" << std::endl;

    size_t temp = pq.size();

    for (size_t i = 0; i < temp; ++i)
    {
        pq.dequeue();
        pq.print_row_data();
        std::cout << std::endl;
    }

    std::cout << std::endl;
 
    std::cout << "============================================================="
              << std::endl
              << std::endl
              << std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                           unit_test_remove */
/*                                                           ~~~~~~~~~~~~~~~~ */
static void unit_test_remove(void)
{
    std::cout << "======================= unit_test_remove ===================="
              << std::endl;    
   
    size_t arr[] = {1,8,5,6,3,4,9,7,2};

    std::cout <<"~~~~~~~~~~ test remove for size_t type ~~~~~~~~" << std::endl;
    PQ<size_t> pq(compare_size_t, print_size_t);
    for (size_t i = 0; i < 9; ++i)
    {
        pq.enqueue(std::make_shared<size_t>(arr[i]));
    }

    std::cout <<"~~~~~~~ list of size_t types in the pq ~~~~" << std::endl;
    pq.print_row_data();

    std::cout << std::endl <<"The same list after removing 8" << std::endl;
    std::shared_ptr<size_t> temp = pq.remove(std::make_shared<size_t>(arr[1]));
    pq.print_row_data();

    std::cout << std::endl;

    std::cout << "item that was removed: " << *(temp.get()) << std::endl
              << std::endl;

    std::cout <<"~~~~~~~~~~ test remove for STask ~~~~~~~~" << std::endl;
    PQ<STask> pq_task(compare_task, print_task_uid);
    pq_task.enqueue(std::shared_ptr<STask> (new STask(user_print, 5)));
    pq_task.enqueue(std::shared_ptr<STask> (new STask(user_print, 10)));
    pq_task.enqueue(std::shared_ptr<STask> (new STask(user_print, 15)));
    pq_task.enqueue(std::shared_ptr<STask> (new STask(user_print, 20)));
    pq_task.enqueue(std::shared_ptr<STask> (new STask(user_print, 25)));

    std::cout <<"~~~~~~~ list of STask objects in the pq ~~~~" << std::endl;
    pq_task.print_row_data();

    std::shared_ptr<STask> temp_2 = pq_task.peek();
    std::shared_ptr<STask> temp_3 = pq_task.remove(temp_2); 

    std::cout <<"~~~~~~~~~~~~~~ list of STask objects in the pq after "
              << "object with counter 8 was removed  ~~~~~~~~~~~~" << std::endl;
    pq_task.print_row_data();
    temp_2 = nullptr;

    std::cout << std::endl;
    std::cout << "item that was removed: " << std::endl;
    temp_3.get()->get_uid().print_uid();

   

    std::cout << "============================================================="
              << std::endl
              << std::endl
              << std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                             unit_test_peek */
/*                                                             ~~~~~~~~~~~~~~ */
static void unit_test_peek(void)
{
    std::cout << "================ unit_test_peek ================"<< std::endl;    
   
    size_t arr[] = {1,8,5,6,3,4,9,7,2};

    std::cout <<"~~~~~~~~~~ test remove for size_t type ~~~~~~~~" << std::endl;
    PQ<size_t> pq(compare_size_t, print_size_t);
    for (size_t i = 0; i < 9; ++i)
    {
        pq.enqueue(std::make_shared<size_t>(arr[i]));
    }

    std::cout <<"~~~~~~~ list of size_t types in the pq ~~~~" << std::endl;
    pq.print_row_data();
    std::cout << std::endl;

    std::cout << "~~~~~~~~~~~~~~ peek at the top element of the heap: "
              << *(pq.peek().get()) << std::endl ;

    std::cout << "============================================================="
              << std::endl
              << std::endl
              << std::endl;
}


/*============================================================================*/
/*                                   User function                            */             
/*============================================================================*/
/*                                                                            */
/*                                                             compare_size_t */
/*                                                             ~~~~~~~~~~~~~~ */ 
bool compare_size_t(std::shared_ptr<size_t> one, std::shared_ptr<size_t> two)
{
    return ((*(one.get()) > *(two.get())));    
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                               print_size_t */
/*                                                               ~~~~~~~~~~~~ */ 
void print_size_t(std::vector<std::shared_ptr<size_t>>& vector)
{
    for (auto i : vector)
    {
        std::cout << *(i.get());
    }  
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                               compare_task */
/*                                                               ~~~~~~~~~~~~ */ 
bool compare_task(std::shared_ptr<STask> one, std::shared_ptr<STask> two)
{
    return ((one.get()->get_time_to_execute() >
             two.get()->get_time_to_execute()) ?
             true : false);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                             print_task_uid */
/*                                                             ~~~~~~~~~~~~~~ */ 
void print_task_uid(std::vector<std::shared_ptr<STask>>& vector)
{
    for (auto i : vector)
    {
        i.get()->get_uid().print_uid();
    }  
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                 user_print */
/*                                                                 ~~~~~~~~~~ */ 
int user_print(void *param)
{
    UNUSED(param); 

    printf("# All glory to the Hypnotoad #\n");
    
    return (0);
} 
