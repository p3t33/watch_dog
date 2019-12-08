#ifndef _PRIORITY_QUEUE_
#define _PRIORITY_QUEUE_
/*******************************************************************************
*                                 priority queue
*                             =====================
* File Name: priority_queue.hpp
* Related files: priority_queue_test.cpp
* #Version: V 1.3
* Writer: Kobi Medrish       
* Created: 28.11.19
* Last update: 8.12.19
*******************************************************************************/
// std::priority_queue does not provide all of the necessary functionally
// such as random accsess to the std::vector it uses, nor does id support the
// the option to provide a costum compare function to the heap algorethem it
// uses (I need the minimum element on the top and std::priority_queue sorts 
// by maximum by default). And so this class was implemented.  

/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                      standard  directories */
/*                                                      ~~~~~~~~~~~~~~~~~~~~~ */
#include <stddef.h> //size_t
#include <functional> // using
#include <vector> // vector
#include <algorithm> // heap
#include <memory> // std::shared_ptr
#include <cstring> // std::memcmp

/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */
#include "task.hpp"
#include "uid.hpp"

/*============================================================================*/
namespace med
{

template <typename T>
class PQ
{
    private:
        using compare_t = std::function<bool(std::shared_ptr<T> data_1,
                                             std::shared_ptr<T> data_2)>;
        using is_match_t = std::function<bool(std::shared_ptr<T> data_1,
                                              std::shared_ptr<T> data_2)>;
        using print_data_t = 
                   std::function<void(std::vector<std::shared_ptr<T>>& vector)>;

    public:
        PQ(compare_t compare_func, print_data_t print_data_func);

        // Interface / API
        // ---------------------------------------------------------------------
        std::shared_ptr<T> enqueue(std::shared_ptr<T> data);
        std::shared_ptr<T> dequeue();
        std::shared_ptr<T> remove(std::shared_ptr<T> data_to_remove);
        std::shared_ptr<T> peek();
        bool is_empty();
        size_t size();
        void clear();
        void print_row_data();


    private:
        // managing variables
        // ---------------------------------------------------------------------
        std::vector<std::shared_ptr<T>> m_priority_queue;

        // Generic function provided by the user
        // ---------------------------------------------------------------------
        compare_t m_compare_func;
        print_data_t m_print_data_func;
};

/*============================================================================*/
/*                                    Class PQ                                */
/*============================================================================*/
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                               special functions                            */
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                                                         Constructor / ctor */
/*                                                         ~~~~~~~~~~~~~~~~~~ */
template <typename T>
PQ<T>::PQ(compare_t compare_func,
          print_data_t print_data_func):
                                              m_priority_queue{},
                                              m_compare_func(compare_func),
                                              m_print_data_func(print_data_func)
{}

/*============================================================================*/
/*                     API functions / Public member functions                */
/*============================================================================*/
/*                                                                    enqueue */
/*                                                                    ~~~~~~~ */
template <typename T>
std::shared_ptr<T> PQ<T>::enqueue(std::shared_ptr<T> data)
{
    // adds a new element to the vector
    m_priority_queue.push_back(data);

    // after an object is added to m_priority_queue is returned to the
    // a smart pointer to the object inside the underlying vector is returrend
    std::shared_ptr<T> temp = m_priority_queue.back();

    //pushes the last element in the vector onto the valid heap over the range      
    std::push_heap(m_priority_queue.begin(),
                   m_priority_queue.end(), m_compare_func);
    return (temp);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                    dequeue */
/*                                                                    ~~~~~~~ */
template <typename T>
std::shared_ptr<T> PQ<T>::dequeue()
{
    std::shared_ptr<T> temp = nullptr;
    // moves the top heap element to the end of the vector 
    std::pop_heap(m_priority_queue.begin(),
                  m_priority_queue.end(), m_compare_func);

    temp = m_priority_queue.back();

    // actually removes the former top heap element
    m_priority_queue.pop_back();

    return (temp);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  FUnctionF */
/*                                                                  ~~~~~~~~~ */
template <typename T>
std::shared_ptr<T> PQ<T>::remove(std::shared_ptr<T> data_to_remove)
{
    std::shared_ptr<T> temp = nullptr;
    size_t size = m_priority_queue.size();

    for (size_t i = 0; i < size; ++i)
    {
        if (*(m_priority_queue[i]) == *(data_to_remove))
        {
            temp = m_priority_queue[i];
            m_priority_queue.erase(m_priority_queue.begin() + i);
      

            std::make_heap(m_priority_queue.begin(),
                           m_priority_queue.end(), m_compare_func);
            break;
        }
    }

    return (temp);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                       peek */
/*                                                                       ~~~~ */
template <typename T>       
std::shared_ptr<T> PQ<T>::peek()
{
    return (m_priority_queue[0]);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                  FUnctionH */
/*                                                                  ~~~~~~~~~ */
template <typename T>
bool PQ<T>::is_empty()
{
    return (m_priority_queue.empty());
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                       size */
/*                                                                       ~~~~ */
template <typename T>
size_t PQ<T>::size()
{
    return (m_priority_queue.size());
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                      clear */
/*                                                                      ~~~~~ */
template <typename T>
void PQ<T>::clear()
{
    m_priority_queue.clear();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                             print_row_data */
/*                                                             ~~~~~~~~~~~~~~ */
template <typename T>
void PQ<T>::print_row_data()
{
    m_print_data_func(m_priority_queue);
}

}

#endif // _PRIORITY_QUEUE_
