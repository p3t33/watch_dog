#ifndef _STASK_
#define _STASK_
/*******************************************************************************
*                                       task
*                             =====================
* File Name: task.hpp 
* Related files: task.cpp task_test.cpp uid.hpp uid.cpp
* #Version: V 1.3
* Writer: Kobi Medrish       
* Created: 28.11.19
* Last update: 5.12.19
*******************************************************************************/


/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                      standard  directories */
/*                                                      ~~~~~~~~~~~~~~~~~~~~~ */
#include <time.h> // time_t
#include <stddef.h> //size_t
#include <functional> // using
#include <memory> // shared_ptr

/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */
#include "uid.hpp"

/*============================================================================*/

namespace med
{

template <typename T>
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
        void update_time_to_execute(); // with current time + interval
        time_t get_time_to_execute();
        UID& get_uid();

    private:
        // managing variables
        // ---------------------------------------------------------------------
        UID m_uid;
        task_function_t& m_task_function;
        time_t m_act_time;
	    size_t m_interval; /* seconds */
        std::shared_ptr<T> m_task_param;
};


/*============================================================================*/
/*                                  Class STask                               */
/*============================================================================*/
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                               special functions                            */
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                                                         Constructor / ctor */
/*                                                         ~~~~~~~~~~~~~~~~~~ */
template <typename T>
STask<T>::STask(task_function_t act_func, size_t interval):
m_uid(),
m_task_function(act_func),
m_act_time(0),
m_interval(interval)
{}

template <typename T>
bool STask<T>::operator==(STask& other) const
{
    return (m_uid == other.m_uid);
}
/*============================================================================*/
/*                     API functions / Public member functions                */
/*============================================================================*/
/*                                                                    execute */
/*                                                                    ~~~~~~~ */
template <typename T>
int STask<T>::execute()
{
    return (m_task_function(nullptr));
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                     update_time_to_execute */
/*                                                     ~~~~~~~~~~~~~~~~~~~~~~ */
template <typename T>
void STask<T>::update_time_to_execute()
{
    m_act_time = time(nullptr) + m_interval;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                        get_time_to_execute */
/*                                                        ~~~~~~~~~~~~~~~~~~~ */
template <typename T>
time_t STask<T>::get_time_to_execute()
{
    return (m_act_time);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                    get_uid */
/*                                                                    ~~~~~~~ */
template <typename T>
UID& STask<T>::get_uid()
{

    return (m_uid);
    //return (m_uid);
}


} // namespace med
#endif // _STASK_
