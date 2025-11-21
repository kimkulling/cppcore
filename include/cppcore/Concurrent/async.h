/*-----------------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2014-2025 Kim Kulling

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
-----------------------------------------------------------------------------------------------*/
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
