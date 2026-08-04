/*-----------------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2014-2026 Kim Kulling

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

#include <cppcore/CPPCoreCommon.h>

#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>

namespace cppcore {

//-------------------------------------------------------------------------------------------------
///	@class		TAsyncLoader
///	@ingroup	CPPCore
///
///	@brief  This template class implements a simple loader which runs load requests asynchronously.
///
/// A load request is described by a user-provided load function which returns the loaded resource
/// of type @c T. Each request is dispatched onto its own worker via @c std::async and a
/// @c std::future is handed back to the caller to retrieve the result once it is ready. The loader
/// keeps track of the number of outstanding requests, so you can wait until all of them have
/// finished. The class destructor will block until all pending loads are done, so no request can
/// outlive the loader instance it was started from.
///
///	@code
/// TAsyncLoader<Buffer> loader;
/// std::future<Buffer> request = loader.load([]() { return readFileBlocking("data.bin"); });
/// // ... do other work ...
/// Buffer buffer = request.get();
///	@endcode
//-------------------------------------------------------------------------------------------------
template<class T>
class TAsyncLoader {
public:
    /// The load function type, describes the blocking load operation to run asynchronously.
    using LoadFunc = std::function<T()>;

    ///	@brief	The default class constructor.
    TAsyncLoader() = default;

    ///	@brief	The class destructor, will wait for all pending loads to finish.
    ~TAsyncLoader();

    // This class cannot be copied or moved.
    CPPCORE_NONE_COPYING(TAsyncLoader)

    ///	@brief	Will start a new load request which runs asynchronously.
    ///	@param[in] loadFunc     The load function to execute, must be valid.
    ///	@return	A future which will hold the loaded resource once the request has finished.
    std::future<T> load(LoadFunc loadFunc);

    ///	@brief	Returns the number of load requests which have not finished yet.
    ///	@return	The number of pending load requests.
    size_t numPending() const;

    ///	@brief	Returns true, if there is at least one load request which has not finished yet.
    ///	@return	true if any request is still pending, else false.
    bool hasPending() const;

    ///	@brief	Blocks the calling thread until all pending load requests have finished.
    void waitForAll();

private:
    void finish();

private:
    mutable std::mutex mMutex;               ///< Guards the pending counter.
    std::condition_variable mCondition;      ///< Used to signal a finished request.
    size_t mNumPending{0};                   ///< The number of outstanding load requests.
};

template<class T>
inline TAsyncLoader<T>::~TAsyncLoader() {
    waitForAll();
}

template<class T>
inline std::future<T> TAsyncLoader<T>::load(LoadFunc loadFunc) {
    assert(loadFunc != nullptr);

    {
        std::lock_guard<std::mutex> lock(mMutex);
        ++mNumPending;
    }

    try {
        std::future<T> f = std::async(std::launch::async, [this, loadFunc]() -> T {
            // Make sure the pending counter is decremented, even if the load throws.
            struct Finalizer {
                Finalizer(const Finalizer&) = delete;    
                Finalizer(const Finalizer&&) = delete;
                Finalizer &operator = (const Finalizer&) = delete;
                
                Finalizer() = default;
                TAsyncLoader *mLoader{nullptr};
                ~Finalizer() { mLoader->finish(); }
            } finalizer{this};

            return loadFunc();
        });
        return f;
    } catch (std::runtime_error &) {
        std::lock_guard<std::mutex> lock(mMutex);
        --mNumPending;
    }
    
    return std::future<T>();
}

template<class T>
inline size_t TAsyncLoader<T>::numPending() const {
    std::lock_guard<std::mutex> lock(mMutex);
    return mNumPending;
}

template<class T>
inline bool TAsyncLoader<T>::hasPending() const {
    return numPending() != 0;
}

template<class T>
inline void TAsyncLoader<T>::waitForAll() {
    std::unique_lock<std::mutex> lock(mMutex);
    mCondition.wait(lock, [this]() { return mNumPending == 0; });
}

template<class T>
inline void TAsyncLoader<T>::finish() {
    // Notify while holding the lock so waitForAll() cannot return and destroy this
    // instance while the notification is still in flight.
    std::lock_guard<std::mutex> lock(mMutex);
    --mNumPending;
    mCondition.notify_all();
}

} // namespace cppcore
