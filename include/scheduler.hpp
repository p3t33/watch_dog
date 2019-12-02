#ifndef _SCHEDULER_
#define _SCHEDULER_
/*******************************************************************************
*                                    scheduler
*                             =====================
* File Name: scheduler.hpp
* Related files: scheduler.cpp scheduler_test.cpp
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 28.11.19
* Last update: 28.11.19
*******************************************************************************/


/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                      standard  directories */
/*                                                      ~~~~~~~~~~~~~~~~~~~~~ */
#include <stddef.h> //size_t
#include <functional> // using
#include <queue> // std::priority_queue
#include <functional> // using
#include <memory> // shared_ptr
//std::multimap
/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */
#include "task.hpp"
#include "uid.hpp"

/*============================================================================*/
namespace med
{

class Scheduler
{
    private:
    using task_function_t = std::function<int(void* param)>;

    public:
    Scheduler();

    UID add_task(task_function_t act_func, size_t interval);
    int remove_task(UID& task_id);
    int execute_schedule();
    void stop();
    size_t get_number_of_tasks();
    bool is_empty();

    private:
    int m_kill_flag;
    std::priority_queue<std::shared_ptr<STask>> m_pqueue;
};

} // namespace med

#endif // scheduler