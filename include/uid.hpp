#ifndef _UID_
#define _UID_
/*******************************************************************************
*                                       uid
*                             =====================
* File Name: uid.hpp
* Related files: uid.cpp counter.hpp
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 27.11.19
* Last update: 27.11.19
*******************************************************************************/


/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                      standard  directories */
/*                                                      ~~~~~~~~~~~~~~~~~~~~~ */
#include <sys/time.h> /* struct timeval, gettimeofday */
#include <sys/types.h> /* pid_t */

/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */
#include "counter.hpp"

/*============================================================================*/


namespace med
{

class UID
{
    private:
        enum status {DIFFERENT_ID, SAME_ID, GOOD_ID, BAD_ID};
        Counter<UID> m_counter;

    public:
        UID();
        
        bool is_same_id(UID& other);
        bool is_bad_id();
        void print_uid();

    private:
        pid_t m_pid; 
        timeval m_time; 
        size_t m_identification_number;
};

} // namespace med
#endif // _UID_
