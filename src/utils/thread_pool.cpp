#include "thread_pool.h"

ThreadPool::ThreadPool():ThreadPool(std::thread::hardware_concurrency()) {}

ThreadPool::ThreadPool(std::size_t num_threads) : stop_(false) {
    for (std::size_t i = 0; i < num_threads; ++i) {
        threads_.emplace_back([this]{
            for (;;) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(this->queue_mutex_);
                    this->condition_.wait(lock, [this] { return this->stop_ || !this->tasks_.empty(); });
                    if (this->stop_ && this->tasks_.empty()) {
                        return;
                    }
                    task = std::move(this->tasks_.front());
                    this->tasks_.pop();
                }

                task();
            }
        });
    }
}

template<class F, class... Args>
void ThreadPool::enqueue(F&& f, Args&&... args) {
    {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        tasks_.emplace([=] { std::invoke(std::forward<F>(f), std::forward<Args>(args)...); });
    }
    condition_.notify_one();
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        stop_ = true;
    }
    condition_.notify_all();
    for (std::thread& thread : threads_) {
        thread.join();
    }
}
