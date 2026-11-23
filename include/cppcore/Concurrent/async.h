#pragma once

#include <cppcore/Container/TList.h>
#include <cassert>

namespace cppcore {
namespace concurrent {

    enum class AsyncStatus {
        Invalid = -1,
        Pending,
        Running,
        Completed,
        Failed
    };

    struct context_t {
        void *data;
    };


    /**
     * @brief Asynchronous task representation.
     *
     * This class provides a mechanism to represent and manage asynchronous tasks.
     * It allows for task creation, execution, and result retrieval in a concurrent
     * environment.
     */
    class AsyncTask {
    public:
        /**
         * @brief Constructs an AsyncTask with the given function.
         * 
         * @param func The function to be executed asynchronously.
         */
        template<typename Func>
        explicit AsyncTask(Func&& func) {
            // Implementation here
        }
    
        /**
         * @brief Starts the asynchronous task.
         */
        void start(const context_t& ctx = { nullptr });

        /// @brief 
        /// @return 
        AsyncStatus status() const;

        /**
         * @brief Waits for the task to complete and retrieves the result.
         * 
         * @return The result of the asynchronous task.
         */
        template<typename ResultType>
        ResultType get();
    
    private:
        
    };

class Executor {
public:
    Executor();
    ~Executor();
    Executor(const Executor&) = delete;
    Executor& operator=(const Executor&) = delete;

    void start();
    void stop();
    void update();
    bool isRunning() const;

    /**
     * @brief Submits a task for asynchronous execution.
     *
     * @param task The task to be executed.
     */
    void submit(AsyncTask& task);

    /**
     * @brief Shuts down the executor, waiting for all tasks to complete.
     */
    void shutdown();

private:
    AsyncStatus mAsyncStatus{AsyncStatus::Invalid};
    TList<AsyncTask*> mTasks;
    bool mStopRequested{false};
};

inline Executor::Executor() {
}

inline Executor::~Executor() {
    assert(!mStopRequested);
}

inline void Executor::start() {
    if (mAsyncStatus != AsyncStatus::Invalid) {
        return;
    }

    mAsyncStatus = AsyncStatus::Pending;
    TList<AsyncTask*>::Iterator it = mTasks.begin();
}

inline void Executor::stop() {
    if (mAsyncStatus != AsyncStatus::Pending)
        return;
    }

    mStopRequested = true;
}

inline void Executor::update() {
}

inline bool Executor::isRunning() const {
    return false;
}

inline void Executor::submit(AsyncTask&& task) {
}

inline void Executor::shutdown() {
}

} // namespace concurrent
} // namespace cppcore
