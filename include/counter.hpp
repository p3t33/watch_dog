#ifndef _COUNTER_
#define _COUNTER_ 
/*******************************************************************************
*                                    counter
*                             =====================
* File Name: counter.hpp
* Related files: uid.cpp uid.cpp
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 27.11.19
* Last update: 28.11.19
*******************************************************************************/

/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                      standard  directories */
/*                                                      ~~~~~~~~~~~~~~~~~~~~~ */
#include <stddef.h> // size_t

/*============================================================================*/


// This is an auxilary class used to provide a count identifier for UID class.
// There is no dtor (which would decrease m_count by 1) because all is needed is
// a unique count identifier for each created object of type UID.
namespace med
{

template<typename T>
class Counter
{
public:
    Counter();
    Counter(const Counter& other);

    size_t get_count();

private:
    static size_t m_count;
};

template<typename T>
size_t Counter<T>::m_count = 0;


/*============================================================================*/
/*                                 Class Counter                              */
/*============================================================================*/
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                               special functions                            */
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                                                         Constructor / ctor */
/*                                                         ~~~~~~~~~~~~~~~~~~ */
template<typename T>
Counter<T>::Counter()
{
    ++m_count;
}
                                                                    
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                          Destructor / dtor */
/*                                                          ~~~~~~~~~~~~~~~~~ */
template<typename T>
Counter<T>::Counter(const Counter& other)
{
    ++m_count;
}

/*============================================================================*/
/*                     API functions / Public member functions                */
/*============================================================================*/
/*                                                                  get_count */
/*                                                                  ~~~~~~~~~ */
template<typename T>
size_t Counter<T>::get_count()
{
    return m_count;
}

} // namespace med
#endif // _COUNTER_ 
