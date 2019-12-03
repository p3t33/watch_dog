#ifndef _STASK_
#define _STASK_
/*******************************************************************************
*                                       task
*                             =====================
* File Name: task.hpp 
* Related files: task.cpp task_test.cpp uid.hpp uid.cpp
* #Version: V 1.2
* Writer: Kobi Medrish       
* Created: 28.11.19
* Last update: 3.12.19
*******************************************************************************/


/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                      standard  directories */
/*                                                      ~~~~~~~~~~~~~~~~~~~~~ */
#include <time.h> // time_t
#include <stddef.h> //size_t
#include <functional> // using

/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */
#include "uid.hpp"

/*============================================================================*/

namespace med
{

class STask
{
    private:
        using task_function_t = std::function<int(void* param)>;
    
    public:
        STask(task_function_t act_func, size_t interval);
        bool operator==(STask& other) const;

        // Interface / API
        // ---------------------------------------------------------------------
        int execute();
        void update_time(); // with current time + interval
        time_t get_time_to_execute();
        UID& get_uid();

    private:
        // managing variables
        // ---------------------------------------------------------------------
        UID m_uid;
        task_function_t& m_task_function;
        time_t m_act_time;
	    size_t m_interval; /* seconds */
};
    
} // namespace med
#endif // _STASK_
