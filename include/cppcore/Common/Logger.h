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

#include <cppcore/CPPCoreCommon.h>
#include <cppcore/Container/TArray.h>
#include <cppcore/Common/TStringBase.h>

namespace cppcore {

#define DECL_LOG_MODULE(name) static constexpr char Tag[] = #name;

using String = TStringBase<char>;

//-------------------------------------------------------------------------------------------------
///
///	@brief	This pure abstract interface class declares the protocol for log-stream implementation.
///	You can use log streams to pipes logs to you preferred output device like a simple text-file 
///	or a log window in a GUI application. Implement the write message and attach a valid instance 
///	to the logger itself to use your own implementation.
//-------------------------------------------------------------------------------------------------
class AbstractLogStream {
public:
    ///	@brief	The default class destructor, virtual.
    virtual ~AbstractLogStream() = default;

    ///	@brief	Will write a message into the attached log stream.
    ///	@param	message	The message to log.
    virtual void write(const String &message) = 0;

    ///	@brief	The stream will be activated.
    virtual void activate();

    ///	@brief	The stream will be deactivated.
    virtual void deactivate();

    ///	@brief	Returns true, if the stream is active.
    ///	@return	true, if the stream is active, else false will be returned.
    virtual bool isActive() const;

    // No copying
    AbstractLogStream(const AbstractLogStream &) = delete;
    AbstractLogStream &operator = (const AbstractLogStream &) = delete;

protected:
    ///	@brief	The default class constructor.
    AbstractLogStream() = default;

private:
    bool mIsActive = true;
};

//-------------------------------------------------------------------------------------------------
///
///	@brief	This class implements a simple logger. 
///
///	The logger is implemented as a singleton. You can attach several log streams to it, which can
///	be used to log the messages to several output channels like a window or a log file or something 
///	else.
///	The granularity of the logged messages can be controlled by the severity of the logger. The 
///	supported modes are normal ( no debug and info messages ), verbose ( all messages will be
///	logged ) and debug ( the debug messages will be logged as well, be careful with this option ).
//-------------------------------------------------------------------------------------------------
class Logger final {
public:
    ///	@brief	Describes the verbode mode.
    enum class VerboseMode {
        Invalid = -1,   ///< Invalid marker
        Normal, 		///< Only warnings and errors will be logged.
        Verbose,    	///< Normal messages will be logged as well.
        Debug,		    ///< All debug messages will be logged as well.
        Trace,          ///< Will enable the tracing.
        Count           ///< Number of enums
    };

    ///	@brief	Describes the mode for prints into the active log stream.
    enum class PrintMode {
        Invalid = -1,       ///< Invalid marker
        WithDateTime,		///< A dateTime string will put be in front of the entry.
        WithoutDateTime,    ///< No DateTime will be there.
        Count               ///< Number of enums
    };

public:
    ///	@brief	Creates the unique logger instance and returns a pointer showing to it.
    ///	@return	The singleton pointer of the logger.
    static Logger *create();

    ///	@brief	returns the singleton instance pointer of the logger.
    ///	@return	The singleton pointer of the logger.
    static Logger *getInstance();

    ///	@brief	Kills the only instance of the logger.
    static void kill();

    ///	@brief	Set the severity of the logger.
    ///	@param[in] sev   The new severity of the logger.
    ///	@see	Severity
    void setVerboseMode(VerboseMode sev);

    ///	@brief	Returns	the current severity of the logger.
    ///	@return	The current severity.
    VerboseMode getVerboseMode() const;

    /// @brief  Logs a trace message.
    /// @param[in] domain  The domain.
    ///	@param[in] msg     The message to log.
    void trace(const String &domain, const String &msg);

    ///	@brief	Logs a debug message.
    /// @param[in] domain  The domain.
    ///	@param[in] msg     The message to log.
    void debug(const String &domain, const String &msg);

    ///	@brief	Logs an info message.
    /// @param[in] domain  The domain.
    ///	@param[in] msg     The message to log.
    void info(const String &domain, const String &msg);

    ///	@brief	Logs a print message.
    ///	@param[in] message  The message to log.
    /// @param[in] mode     Logging mode
    void print( const String &message, PrintMode mode = PrintMode::WhithoutDateTime );

    ///	@brief	Logs a warn message.
    /// @param[in] domain  The domain.
    ///	@param[in] msg     The message to log.
    void warn( const String &domain, const String &msg );

    ///	@brief	Logs a error message.
    /// @param[in] domain  The domain.
    ///	@param[in] msg     The message to log.
    void error(const String &domain, const String &msg);

    ///	@brief	Logs a fatal error message.
    /// @param[in] domain  The domain.
    ///	@param[in] msg     The message to log.
    void fatal(const String &domain, const String &msg);

    ///	@brief	Registers a new log stream.
    ///	@param[in] pLogStream    A pointer showing to the log stream.
    void registerLogStream(AbstractLogStream *pLogStream);

    ///	@brief	Unregisters a registered log stream.
    ///	@param[in] pLogStream    A pointer showing to the log stream.
    void unregisterLogStream(AbstractLogStream *pLogStream);

private:
    Logger();
    ~Logger();
    String getDateTime();

private:
    //  @brief  The Standard log stream.
    class StdLogStream : public AbstractLogStream {
    public:
        /// @brief  The class constructor.
        StdLogStream() = default;

        /// @brief  The class destructor.
        ~StdLogStream() override = default;

        /// @brief  Will write a message into the stream.
        /// @param  msg     [in] The message to write.
        void write(const String &msg) override;
    };

    static Logger *sLogger;

    using LogStreamArray = cppcore::TArray<AbstractLogStream*>;
    LogStreamArray mLogStreams;
    VerboseMode mVerboseMode;
    uint32_t mIntention;
};

// Logger helper function prototypes
void tracePrint(const String &domain, const String &file, int line, const String &msg);
void debugPrint(const String &domain, const String &file, int line, const String &msg);
void infoPrint( const String &domain, const String &file, int line, const String &msg );
void warnPrint( const String &domain, const String &file, int line, const String &msg );
void errorPrint( const String &domain, const String &file, int line, const String &msg );
void fatalPrint( const String &domain, const String &file, int line, const String &msg );

} // namespace cppcore

//-------------------------------------------------------------------------------------------------
///	@fn		osre_trace
///	@brief	This helper macro will write the trace message into the logger.
/// @param  domain      The domain to log for.
///	@param	message		The message to log.
//-------------------------------------------------------------------------------------------------
#define log_trace(domain, msg) ::cppcore::tracePrint(domain, __FILE__, __LINE__, msg)

//-------------------------------------------------------------------------------------------------
///	@fn		osre_debug
///	@brief	This helper macro will write the debug message into the logger.
/// @param  domain      The domain to log for.
///	@param	message		The message to log.
//-------------------------------------------------------------------------------------------------
#define log_debug(domain, msg) ::cppcore::debugPrint(domain, __FILE__, __LINE__, msg)

//-------------------------------------------------------------------------------------------------
///	@fn		osre_log
///	@brief	This helper macro will write the info message into the logger.
/// @param  domain      The domain to log for.
///	@param	message		The message to log.
//-------------------------------------------------------------------------------------------------
#define log_info(domain, msg) ::cppcore::infoPrint(domain, __FILE__, __LINE__, msg)

//-------------------------------------------------------------------------------------------------
///	@fn		osre_warn
///	@brief	This helper macro will write a warning into the logger.
/// @param  domain      The domain to log for.
///	@param	message		The warning to writhe into the log.
//-------------------------------------------------------------------------------------------------
#define log_warn(domain, message) ::cppcore::warnPrint(domain, __FILE__, __LINE__, message)

//-------------------------------------------------------------------------------------------------
///	@fn		osre_error
///	@brief	This helper macro will write a error into the logger.
/// @param  domain      The domain to log for.
///	@param	message		The warning to writhe into the log.
//-------------------------------------------------------------------------------------------------
#define log_error(domain, message) ::cppcore::errorPrint(domain, __FILE__, __LINE__, message)

//-------------------------------------------------------------------------------------------------
///	@fn		osre_fatal
///	@brief	This helper macro will write a fatal error into the logger.
/// @param  domain      The domain to log for.
///	@param	message		The warning to writhe into the log.
//-------------------------------------------------------------------------------------------------
#define log_fatal(domain, message) ::cppcore::fatalPrint(domain, __FILE__, __LINE__, message)
