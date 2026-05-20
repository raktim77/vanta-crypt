#pragma once

#include "concurrent_queue.h"

#include <vector>
#include <thread>
#include <functional>
#include <future>
#include <atomic>

class ThreadPool {
public:
    explicit ThreadPool(size_t thread_count);

    ~ThreadPool();

    template<typename Func, typename... Args>
    auto enqueue(Func&& func, Args&&... args)
        -> std::future<typename std::invoke_result<Func, Args...>::type>;

    void shutdown();

private:
    void worker_loop();

private:
    std::vector<std::thread> workers_;

    ConcurrentQueue<std::function<void()>> tasks_;

    std::atomic<bool> running_ = true;
};

template<typename Func, typename... Args>
auto ThreadPool::enqueue(Func&& func, Args&&... args)
    -> std::future<typename std::invoke_result<Func, Args...>::type>
{
    using ReturnType =
        typename std::invoke_result<Func, Args...>::type;

    auto task = std::make_shared<std::packaged_task<ReturnType()>>(
        std::bind(
            std::forward<Func>(func),
            std::forward<Args>(args)...
        )
    );

    std::future<ReturnType> future = task->get_future();

    tasks_.push([task]() {
        (*task)();
    });

    return future;
}