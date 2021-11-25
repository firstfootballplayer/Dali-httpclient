// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/libmevent/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//
// This is a public header file, it must only include public header files.

#ifndef libmevent_NET_HTTPCLIENT_H
#define libmevent_NET_HTTPCLIENT_H

#include "libmevent/net/TcpClient.h"
#include "libmevent/base/Logging.h"
#include "libmevent/net/EventLoop.h"
#include "libmevent/base/Thread.h"
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <stdio.h>
#include <unistd.h>

class HttpClient : libmevent::noncopyable
{
public:
    HttpClient(libmevent::net::EventLoop* loop, const libmevent::net::InetAddress& listenAddr, const std::string& id);

    HttpClient();

    void setServerAddr(const libmevent::net::InetAddress& serverAddr);

    void connect()
    {
        client_->connect();
    }
    // void stop();
    void parseUrl(const char* mUrl);
    void setBody(const std::string& body)
    {
        body_ = body;
    }

    void processhttp();

private:
    void onConnection(const libmevent::net::TcpConnectionPtr& conn);

    void onMessage(const libmevent::net::TcpConnectionPtr& conn, libmevent::net::Buffer* buf, libmevent::Timestamp time);

    void timeout();

    void setCloseConnection(bool on)
    {
        closeConnection_ = on;
    }

    void setContentType(const std::string& contentType)
    {
        addHeader("Content-Type", contentType);
    }

    // FIXME: replace std::string with std::stringPiece
    void addHeader(const std::string& key, const std::string& value)
    {
        headers_[key] = value;
    }

    void appendToBuffer(libmevent::net::Buffer* output) const;

    std::map<std::string, std::string> headers_;
    // FIXME: add http version
    bool closeConnection_;
    std::string body_;
    libmevent::net::EventLoop* loop_;
    std::unique_ptr<libmevent::net::TcpClient> client_;
    libmevent::net::TimerId Timer_;
    libmevent::net::Buffer requestBuffer_;
    std::string serverip_;
    std::string port_;
    std::string filepath_;
    std::string postbody_;
    libmevent::Thread thread_;
    libmevent::MutexLock mutex_;
    libmevent::Condition cond_ GUARDED_BY(mutex_);
};

#endif  // libmevent_NET_CALLBACKS_H
