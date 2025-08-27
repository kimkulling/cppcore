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
#include <cppcore/Common/Logger.h>
#include <cppcore/Common/DateTime.h>

#include <cassert>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace cppcore {

static void appendDomain(const String &domain, String &logMsg) {
    if (!domain.isEmpty()) {
        logMsg += '(';
        logMsg += domain;
        logMsg += ')';
    }
}

static ::std::string stripFilename(const ::std::string &filename) {
    if (filename.empty()) {
        return filename;
    }

    ::std::string::size_type pos = filename.find_last_of("/");
    if (pos == ::std::string::npos) {
        return filename;
    }
    const ::std::string strippedName = filename.substr(pos + 1, filename.size() - pos - 1);

    return strippedName;
}

static void addTraceInfo(const String &file, int line, String &msg) {
    if (Logger::getInstance()->getVerboseMode() == Logger::VerboseMode::Trace) {
        msg += String(" (", 2);
        std::string stripped = stripFilename(file.c_str());
        msg += String(stripped.c_str(), stripped.size());
        msg += String(", ", 2);
        std::stringstream ss;
        ss << line;
        std::string lineno = ss.str();
        msg += String(lineno.c_str(), lineno.size());
        msg += ')';
    }
}

void AbstractLogStream::activate() {
    mIsActive = true;
}

void AbstractLogStream::deactivate() {
    mIsActive = false;
}

bool AbstractLogStream::isActive() const {
    return mIsActive;
}

Logger *Logger::sLogger = nullptr;

Logger *Logger::create() {
    if (nullptr == sLogger) {
        sLogger = new Logger;
    }

    return sLogger;
}

void Logger::set(Logger *logger) {
    if (logger == sLogger) {
        return;
    }
    kill();
    sLogger = logger;
}

Logger *Logger::getInstance() {
    if (nullptr == sLogger) {
        static_cast<void>(create());
    }

    return sLogger;
}

void Logger::kill() {
    if (sLogger != nullptr) {
        delete sLogger;
        sLogger = nullptr;
    }
}

void Logger::setVerboseMode(VerboseMode sev) {
    mVerboseMode = sev;
}

Logger::VerboseMode Logger::getVerboseMode() const {
    return mVerboseMode;
}

void Logger::trace(const String &domain, const String &msg) {
    if (getVerboseMode() == VerboseMode::Trace) {
        String logMsg;
        logMsg += String("Trace: ", 6);
        logMsg += msg;
        appendDomain(domain, logMsg);

        print(logMsg);
    }
}

void Logger::debug(const String &domain, const String &msg) {
    if (getVerboseMode() == VerboseMode::Debug || getVerboseMode() == VerboseMode::Trace) {
        String logMsg;
        logMsg += String("Dbg:  ", 6);
        logMsg += msg;
        appendDomain(domain, logMsg);

        print(logMsg);
    }
}

void Logger::info(const String &domain, const String &msg) {
    if (getVerboseMode() == VerboseMode::Normal ||
            getVerboseMode() == VerboseMode::Verbose || 
            getVerboseMode() == VerboseMode::Debug || 
            getVerboseMode() == VerboseMode::Trace) {
        String logMsg;

        logMsg += String("Info: ", 6);
        logMsg += msg;

        appendDomain(domain, logMsg);

        print(logMsg);
    }
}

void Logger::print(const String &msg, PrintMode mode) {
    if (msg.isEmpty()) {
        return;
    }

    if (msg.size() > 8 && msg[6] == '<' && msg[7] == '=') {
        mIntention -= 2;
    }

    String logMsg;
    if (0 != mIntention) {
        for (uint32_t i = 0; i < mIntention; i++) {
            logMsg += ' ';
        }
    }

    logMsg += msg;
    if (PrintMode::WithDateTime == mode) {
        logMsg += String(" (", 2);
        logMsg += this->getDateTime();
        logMsg += ')';
    }

    logMsg += String(" \n", 2);
    for (size_t i = 0; i < mLogStreams.size(); ++i) {
        AbstractLogStream *stream = mLogStreams[i];
        if (stream != nullptr) {
            stream->write(logMsg);
        }
    }

    if (msg.size() > 8) {
        if (msg[6] == '=' && msg[7] == '>') {
            mIntention += 2;
        }
    }
}

void Logger::warn(const String &domain, const String &msg) {
    String logMsg;
    logMsg += String("Warn: ", 6);
    logMsg += msg;
    appendDomain(domain, logMsg);

    print(logMsg);
}

void Logger::error(const String &domain, const String &msg) {
    String logMsg;
    logMsg += String("Err:  ", 6);
    logMsg += msg;
    appendDomain(domain, logMsg);

    print(logMsg);
}

void Logger::fatal(const String &domain, const String &msg) {
    String logMsg;
    logMsg += String("Fatal:", 6);
    logMsg += msg;
    appendDomain(domain, logMsg);

    print(logMsg);
}

void Logger::registerLogStream(AbstractLogStream *pLogStream) {
    if (nullptr == pLogStream) {
        return;
    }

    mLogStreams.add(pLogStream);
}

void Logger::unregisterLogStream(AbstractLogStream *logStream) {
    if (nullptr == logStream) {
        return;
    }

    for (size_t i = 0; i < mLogStreams.size(); ++i) {
        if (mLogStreams[i] == logStream) {
            delete mLogStreams[i];
            mLogStreams.remove(i);
        }
    }
}

Logger::Logger() {
    mLogStreams.add(new StdLogStream);
}

Logger::~Logger() {
    for (size_t i = 0; i < mLogStreams.size(); ++i) {
        delete mLogStreams[i];
    }
}

String Logger::getDateTime() {
    static const uint32_t Space = 2;
    DateTime currentDateTime;
    std::stringstream stream;
    stream.fill('0');
    stream << std::setw(Space) << currentDateTime.year << "."
           << std::setw(Space) << currentDateTime.month << "."
           << std::setw(Space * 2) << currentDateTime.day << " "
           << std::setw(Space) << currentDateTime.hour << ":"
           << std::setw(Space) << currentDateTime.min << ":"
           << std::setw(Space) << currentDateTime.sec;
    const std::string tmp(stream.str());
    String dateTime(tmp.c_str(), tmp.size());
    return dateTime;
}

void Logger::StdLogStream::write(const String &msg) {
    std::cout << msg.c_str();
}
 
void tracePrint(const String &domain, const String &file, int line, const String &msg) {
    String message;
    message += msg;
    addTraceInfo(file, line, message);
    Logger::getInstance()->trace(domain, message);
}

void debugPrint(const String &domain, const String &file, int line, const String &msg) {
    String message;
    message += msg;
    addTraceInfo(file, line, message);
    Logger::getInstance()->debug(domain, message);
}

void infoPrint(const String &domain, const String &file, int line, const String &msg) {
    String message;
    message += msg;
    addTraceInfo(file, line, message);
    Logger::getInstance()->info(domain, message);
}

void warnPrint(const String &domain, const String &file, int line, const String &message) {
    String msg;
    msg += message;
    addTraceInfo(file, line, msg);
    Logger::getInstance()->warn(domain, msg);
}

void errorPrint(const String &domain, const String &file, int line, const String &message) {
    String msg;
    msg += message;
    addTraceInfo(file, line, msg);
    Logger::getInstance()->error(domain, msg);
}

void fatalPrint(const String &domain, const String &file, int line, const String &message) {
    String msg;
    msg += message;
    addTraceInfo(file, line, msg);
    Logger::getInstance()->fatal(domain, msg);
}

} // namespace cppcore
