/*******************************************************************************
*                                       task
*                             =====================
* File Name: task.cpp
* Related files: task.hpp task_test.cpp uid.cpp uid.hpp
* #Version: V 1.0
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
#include <stddef.h> // size_t

/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */
#include "./include/task.hpp"

/*============================================================================*/

namespace med
{

/*============================================================================*/
/*                                  Class STask                               */
/*============================================================================*/
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                               special functions                            */
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                                                         Constructor / ctor */
/*                                                         ~~~~~~~~~~~~~~~~~~ */
STask::STask(task_function_t act_func, size_t interval):
m_uid(),
m_task_function(act_func),
m_act_time(0),
m_interval(interval)
{}


bool STask::operator==(STask& other) const
{
    return (m_uid == other.m_uid);
}
/*============================================================================*/
/*                     API functions / Public member functions                */
/*============================================================================*/
/*                                                                    execute */
/*                                                                    ~~~~~~~ */
int STask::execute()
{
    return (m_task_function(nullptr));
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                     update_time_to_execute */
/*                                                     ~~~~~~~~~~~~~~~~~~~~~~ */
void STask::update_time_to_execute()
{
    m_act_time = time(nullptr) + m_interval;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                        get_time_to_execute */
/*                                                        ~~~~~~~~~~~~~~~~~~~ */
time_t STask::get_time_to_execute()
{
    return (m_act_time);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                    get_uid */
/*                                                                    ~~~~~~~ */
UID& STask::get_uid()
{
    return (m_uid);
}
    
} // namespace med