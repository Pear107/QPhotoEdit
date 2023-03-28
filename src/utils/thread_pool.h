#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <functional>
#include <mutex>
#include <future>
#include <memory>

#include "task_queue.h"

class ThreadPool {
private:
    class ThreadWorker {
        private:
            int m_id;
            ThreadPool *m_pool;
        public:
            ThreadWorker(ThreadPool *pool, const int id) : m_pool(pool), m_id(id) {}
            void operator()() {
            std::function<void()> func;
            bool dequeued;
            while (!m_pool->m_shutdown) {
                {
                    std::unique_lock<std::mutex> lock(m_pool->m_conditional_mutex);
                    if (m_pool->m_queue.empty()) {
                        m_pool->m_conditional_lock.wait(lock);
                    }

                    dequeued = m_pool->m_queue.dequeue(func);
                }

                if (dequeued) {
                    func();
                }
            }
        }
    };

    static std::shared_ptr<ThreadPool> _instance;
    ThreadPool(const int n_threads = 4)
        : m_threads(std::vector<std::thread>(n_threads)), m_shutdown(false) {
        init();
    }

    ThreadPool(const ThreadPool &) = delete;
    ThreadPool(ThreadPool &&) = delete;
    ThreadPool &operator=(const ThreadPool &) = delete;
    ThreadPool &operator=(ThreadPool &&) = delete;
    void init(){
        for (int i = 0; i < m_threads.size(); ++i) {
            m_threads.at(i) = std::thread(ThreadWorker(this, i));
        }
    }

public:
    bool m_shutdown;
    TaskQueue<std::function<void()>> m_queue;
    std::vector<std::thread> m_threads;
    std::mutex m_conditional_mutex;
    std::condition_variable m_conditional_lock;
    void shutdown(){
        m_shutdown = true;
        m_conditional_lock.notify_all();
        for (int i = 0; i < m_threads.size(); ++i) {
            if (m_threads.at(i).joinable()) {
                m_threads.at(i).join();
            }
        }
    }

    template <typename F, typename... Args>
    auto submit(F &&f, Args &&...args) -> std::future<decltype(f(args...))>{
        std::function<decltype(f(args...))()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
        auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);
        std::function<void()> warpper_func = [task_ptr]() {
            (*task_ptr)();
        };

        m_queue.enqueue(warpper_func);
        m_conditional_lock.notify_one();
        return task_ptr->get_future();
    };

    static std::shared_ptr<ThreadPool> getInstance(){
        return _instance;
    }
};

std::shared_ptr<ThreadPool> ThreadPool::_instance = std::shared_ptr<ThreadPool>(new (std::nothrow) ThreadPool(std::thread::hardware_concurrency()));

#endif // THREAD_POOL_H
