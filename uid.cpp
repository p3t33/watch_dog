/*******************************************************************************
*                                    uid
*                            =====================
* File Name: uid.cpp
* Related files: uid.hpp uid_test.cpp counter.hpp
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 27.11.19
* Last update: 3.zzz.19
*******************************************************************************/


/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                      standard  directories */
/*                                                      ~~~~~~~~~~~~~~~~~~~~~ */
#include <iostream>
#include <assert.h> // assert
#include <unistd.h> // getpid
/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */
#include "./include/uid.hpp"

/*============================================================================*/
namespace med
{


/*============================================================================*/
/*                                   Class uid                                */
/*============================================================================*/
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                               special functions                            */
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                                                         Constructor / ctor */
/*                                                         ~~~~~~~~~~~~~~~~~~ */
UID::UID(): m_pid(getpid()), m_time{}, m_identification_number(0)
{
    gettimeofday(&m_time, NULL);
    m_identification_number = m_counter.get_count();
}

/*                                                                 operator== */
/*                                                                 ~~~~~~~~~~ */
bool UID::operator==(UID& other) const
{
    if(m_pid == other.m_pid &&
       m_time.tv_sec == other.m_time.tv_sec &&
       m_time.tv_usec == other.m_time.tv_usec &&
       m_identification_number == other.m_identification_number)
    {
           return (true);
    }

    return (false);      
}                                                                  
/*============================================================================*/
/*                     API functions / Public member functions                */
/*============================================================================*/
/*                                                                  is_bad_id */
/*                                                                  ~~~~~~~~~ */
bool UID::is_bad_id()
{
    if(0 == m_pid &&
       0 == m_time.tv_sec &&
       0 == m_time.tv_usec &&
       0 == m_identification_number)
    {
           return (true);
    }

    return (false); 
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*                                                                  print_uid */
/*                                                                  ~~~~~~~~~ */
void UID::print_uid(void)
{
    std::cout << "pid :" << m_pid
              << " tv_sec: " << m_time.tv_sec
              << " tv_usec: " << m_time.tv_usec
              << " counter: " << m_identification_number 
              << std::endl;     
}

} // namespace med
