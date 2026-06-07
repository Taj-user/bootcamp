#include "TaskQueue.h"

TaskQueue::TaskQueue()
    : running_ (false)
{}

void TaskQueue::workerLoop() {
    while(running_) {
        std::unique_lock<std::mutex> lock(mtx_);
        cv_.wait(lock, [this]() { return !taskqueue_.empty() || !running_;} );

        if(running_ == false) { break; }

        while(!taskqueue_.empty()) {
            std::function<void()> front_task = taskqueue_.front();
            taskqueue_.pop();
            lock.unlock();
            front_task();
            lock.lock();
        }
    }
}

void TaskQueue::enqueue(std::function<void()> task) {
    std::unique_lock<std::mutex> lock(mtx_);
    taskqueue_.push(task);
    cv_.notify_one();
}

void TaskQueue::start() {
    running_ = true;
    t_ = std::thread(&TaskQueue::workerLoop, this);
}
void TaskQueue::stop() {
    running_ = false;
    cv_.notify_one();
    t_.join();
}
