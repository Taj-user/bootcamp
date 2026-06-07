#pragma once

#include <functional>
#include <queue>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>

class TaskQueue {
    std::queue<std::function<void()>> taskqueue_;
    std::mutex mtx_;
    std::thread t_;
    std::atomic<bool> running_;
    void workerLoop();
    std::condition_variable cv_;

    public:
        TaskQueue();
        void enqueue(std::function<void()> task);
        void start();
        void stop();
};
