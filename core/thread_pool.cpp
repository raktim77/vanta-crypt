#include "thread_pool.h"

ThreadPool::ThreadPool(size_t thread_count) {
    for (size_t i = 0; i < thread_count; ++i) {
        workers_.emplace_back(&ThreadPool::worker_loop, this);
    }
}

ThreadPool::~ThreadPool() {
    shutdown();
}

void ThreadPool::shutdown() {
    if (!running_) {
        return;
    }

    running_ = false;

    tasks_.shutdown();

    for (auto& worker : workers_) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

void ThreadPool::worker_loop() {
    while (running_) {
        std::function<void()> task;

        if (!tasks_.pop(task)) {
            break;
        }

        task();
    }
}