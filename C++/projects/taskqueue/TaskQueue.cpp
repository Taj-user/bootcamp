#include <iostream>
#include "TaskQueue.h"

TaskQueue::TaskQueue()
    : running_ (false)
{}

void TaskQueue::workerLoop() {
    while(running_) {
        std::unique_lock<std::mutex> lock(mtx_);
        if(!taskqueue_.empty()) {
            std::function<void()> front_task = taskqueue_.front();
            taskqueue_.pop();
            lock.unlock();
            front_task();
        }
        else {
            lock.unlock();
        }
    }
}

void TaskQueue::enqueue(std::function<void()> task) {
    std::unique_lock<std::mutex> lock(mtx_);
    taskqueue_.push(task);
    lock.unlock();
}

void TaskQueue::start() {
    running_ = true;
    t_ = std::thread(&TaskQueue::workerLoop, this);
}
void TaskQueue::stop() {
    running_ = false;
    t_.join();
}
