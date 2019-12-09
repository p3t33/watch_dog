/*******************************************************************************
*                                    scheduler
*                             =====================
* File Name: scheduler.cpp
* Related files: scheduler.hpp scheduler_test.cpp
* #Version: V 1.1
* Writer: Kobi Medrish       
* Created: 28.11.19
* Last update: 9.12.19
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
std::shared_ptr<STask<size_t>> Scheduler::add_task(task_function_t act_func,
                                                   size_t interval)
{
    std::shared_ptr<STask<size_t>> temp = 
    m_pqueue.enqueue(std::make_shared<STask<size_t>>(act_func, interval));
    return (temp);
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
    std::shared_ptr<STask<size_t>> temp_task_handle = nullptr;

    size_t queue_size = this->get_number_of_tasks();

    // Tasks are time stamped and list is rearranged based on the time to
    // execute priority.
    for (size_t i = 0; i < queue_size; ++i)
    {
        temp_task_handle = m_pqueue.dequeue();
        temp_task_handle->update_time_to_execute();
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

        sleep(m_pqueue.peek()->get_time_to_execute() - time(nullptr));

        /* Task to be executed is removed from the queue and executed*/
        temp_task_handle = m_pqueue.dequeue();

        switch (temp_task_handle.get()->execute())
        {
            case execute_task_once_and_remove_from_queue: 
            {
                temp_task_handle = nullptr;
                break;
            }
   
            case stop_execution_of_scheduler:
            {
                this->stop();
                break;
            }
        
            // return value is 0, task time stamp is updated and it is inserted 
            // back to the pq.
            default: 
            {
                temp_task_handle.get()->update_time_to_execute();
                m_pqueue.enqueue(temp_task_handle); 
                break;
            }
        }
    }

    return (0);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                       stop */
/*                                                                       ~~~~ */
void Scheduler::stop()
{
    m_kill_flag = -1;
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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                            get_top_task */
/*                                                            ~~~~~~~~~~~~~~~ */ 
void Scheduler::get_top_task()
{
    m_pqueue.peek();
}

} // namespace hrd9
