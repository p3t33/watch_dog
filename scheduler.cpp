/*******************************************************************************
*                                    scheduler
*                             =====================
* File Name: scheduler.cpp
* Related files: scheduler.hpp scheduler_test.cpp
* #Version: V 1.1
* Writer: Kobi Medrish       
* Created: 28.11.19
* Last update: 5.12.19
*******************************************************************************/

/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                      standard  directories */
/*                                                      ~~~~~~~~~~~~~~~~~~~~~ */
#include <iostream>
#include <assert.h> /* assert */
/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */
#include "./include/scheduler.hpp"


namespace med
{

/*============================================================================*/
/*                                Class scheduler                             */
/*============================================================================*/
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                               special functions                            */
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                                                         Constructor / ctor */
/*                                                         ~~~~~~~~~~~~~~~~~~ */
Scheduler::Scheduler():
m_kill_flag(0), m_pqueue(Scheduler::compare_task, Scheduler::print_task_uid)
{}

/*============================================================================*/
/*                     API functions / Public member functions                */
/*============================================================================*/
/*                                                                   add_task */
/*                                                                   ~~~~~~~~ */
UID& Scheduler::add_task(task_function_t act_func,
                                           size_t interval)
{
    std::shared_ptr<STask<size_t>> temp = m_pqueue.enqueue(std::shared_ptr<STask<size_t>> 
                                               (new STask<size_t>(act_func, interval)));
    return (temp.get()->get_uid());
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                remove_task */
/*                                                                ~~~~~~~~~~~ */
std::shared_ptr<STask<size_t>> 
Scheduler::remove_task(std::shared_ptr<STask<size_t>> task_to_remove)
{
    std::shared_ptr<STask<size_t>> temp = m_pqueue.remove(task_to_remove);
    return (temp);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                           execute_schedule */
/*                                                           ~~~~~~~~~~~~~~~~ */
int Scheduler::execute_schedule()
{
    
    int i = 0, temp_size = 0, enqueue_status = 0;
    std::shared_ptr<STask<size_t>> temp_task_handle = nullptr;

    size_t queue_size = this->get_number_of_tasks();

    // Tasks are time stamped and list is rearranged based on the time to
    // execute priority.
    for (size_t i = 0; i < queue_size; ++i)
    {
        temp_task_handle = m_pqueue.dequeue();
        temp_task_handle.get()->update_time_to_execute();
        m_pqueue.enqueue(temp_task_handle);
    }

    
    while(!m_kill_flag)
    {
        // Scheduler will stop when all of the tasks were executed and queue is 
        // empty.
        if (true == this->is_empty())
        {
            return (0);
        }

        sleep(m_pqueue.peek()->get_time_to_execute());


        /* Task to be executed is removed from the queue */
        temp_task_handle = m_pqueue.dequeue();

        /* Task is executed and dealt with based on its return status */ 
        if (0 == temp_task_handle.get()->execute())
        {
            temp_task_handle.get()->update_time_to_execute();
            m_pqueue.enqueue(temp_task_handle);
        }
        else
        {
            /* In case task is to be run once or it is failed to run is is
            destroyed */ 
            temp_task_handle = nullptr;    
        }
    }

    return (1);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                       stop */
/*                                                                       ~~~~ */
void Scheduler::stop()
{
    m_kill_flag = 1;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                        get_number_of_tasks */
/*                                                        ~~~~~~~~~~~~~~~~~~~ */
size_t Scheduler::get_number_of_tasks()
{
    return (m_pqueue.size());
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                   is_empty */
/*                                                                   ~~~~~~~~ */
bool Scheduler::is_empty()
{
    return (m_pqueue.is_empty());
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                               compare_task */
/*                                                               ~~~~~~~~~~~~ */ 
bool 
Scheduler::compare_task(std::shared_ptr<STask<size_t>> one,
                        std::shared_ptr<STask<size_t>> two)
{
    return ((one.get()->get_time_to_execute() >
             two.get()->get_time_to_execute()) ?
             true : false);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                             print_task_uid */
/*                                                             ~~~~~~~~~~~~~~ */ 
void Scheduler::
print_task_uid(std::vector<std::shared_ptr<STask<size_t>>>& vector)
{
    for (auto i : vector)
    {
        i.get()->get_uid().print_uid();
    }  
}

} // namespace hrd9
