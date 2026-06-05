#pragma once

#include <functional>
#include <queue>
#include <thread>
#include <mutex>
#include <atomic>

class TaskQueue {
    std::queue<std::function<void()>> taskqueue_;
    std::mutex mtx_;
    std::thread t_;
    std::atomic<bool> running_;
    void workerLoop();

    public:
        TaskQueue();
        void enqueue(std::function<void()> task);
        void start();
        void stop();
};
