#pragma once

namespace cppcore {
namespace concurrent {

    enum class AsyncStatus {
        Pending,
        Running,
        Completed,
        Failed
    };

    struct context_t {
        void *data;
    };

    class Executor {
    public:
        Executor();
        ~Executor();
        Executor(const Executor&) = delete;
        Executor& operator=(const Executor&) = delete;

        void run();
        
        bool isRunning() const;

        /**
         * @brief Submits a task for asynchronous execution.
         * 
         * @param task The task to be executed.
         */
        template<typename Task>
        void submit(Task&& task);

        /**
         * @brief Shuts down the executor, waiting for all tasks to complete.
         */
        void shutdown();

    private:
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
    
} // namespace concurrent
} // namespace cppcore
