#include "TaskQueue.h"

TaskQueue::TaskQueue()
    : running_ = false;
{}

void TaskQueue::workerLoop() {
    while(running_) {
        std::lock_guard<std::mutex> guard(mtx_);
        if(!taskqueue_.empty()) {
            std::function<void()> front_task = taskqueue_.front();
            taskqueue_.pop();
        }

    }
}

void TaskQueue::enqueue(std::function<void()> task) {
    std::lock_guard<std::mutex> guard(mtx_);
    taskqueue_.push(task);
}

void TaskQueue::start() {

}
