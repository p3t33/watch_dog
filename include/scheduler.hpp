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
#include <unistd.h> // sleep
/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */
#include "task.hpp"
#include "uid.hpp"
#include "priority_queue.hpp"

/*============================================================================*/
namespace med
{

class Scheduler
{
    private:
        using task_function_t = std::function<int(void* param)>;

    public:
        Scheduler();

        // Interface / API
        // ---------------------------------------------------------------------
        void add_task(task_function_t act_func, size_t interval);
        std::shared_ptr<STask> remove_task(std::shared_ptr<STask> task_to_remove);
        int execute_schedule();
        void stop();
        size_t get_number_of_tasks();
        bool is_empty();

    private:
        // managing variables
        // ---------------------------------------------------------------------
        int m_kill_flag;
        PQ<STask> m_pqueue;

        static bool compare_task(std::shared_ptr<STask> one, std::shared_ptr<STask> two);
        static void print_task_uid(std::vector<std::shared_ptr<STask>>& vector);
};

} // namespace med

#endif // scheduler