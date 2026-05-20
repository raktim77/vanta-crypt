#include "../core/thread_pool.h"

#include <iostream>
#include <chrono>

int main() {

    ThreadPool pool(4);

    std::vector<std::future<int>> futures;

    for (int i = 0; i < 10; ++i) {

        futures.push_back(
            pool.enqueue([i]() {

                std::this_thread::sleep_for(
                    std::chrono::milliseconds(500)
                );

                std::cout
                    << "Task "
                    << i
                    << " executed on thread "
                    << std::this_thread::get_id()
                    << std::endl;

                return i * 2;
            })
        );
    }

    for (auto& future : futures) {
        std::cout
            << "Result: "
            << future.get()
            << std::endl;
    }

    return 0;
}