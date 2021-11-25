#include "libmevent/net/TcpClient.h"
#include "libmevent/base/Logging.h"
#include "libmevent/net/EventLoop.h"
#include "libmevent/net/InetAddress.h"
#include "libmevent/net/HttpClient.h"
#include <utility>
#include <stdio.h>
#include <unistd.h>

using namespace libmevent;
using namespace libmevent::net;

class HttpClient;

void HttpClient::timeout()
{
    LOG_WARN << "http request timeout";
    client_->forceClose();
    // loop_->quit();
}

HttpClient::HttpClient(libmevent::net::EventLoop* loop, const libmevent::net::InetAddress& listenAddr, const std::string& id) : loop_(loop), mutex_(), cond_(mutex_), client_(new TcpClient(loop, listenAddr, "")), thread_(std::bind(&HttpClient::processhttp, this))
{
    client_->setConnectionCallback(std::bind(&HttpClient::onConnection, this, _1));
    client_->setMessageCallback(std::bind(&HttpClient::onMessage, this, _1, _2, _3));
    // client_->enableRetry();
}

HttpClient::HttpClient() : thread_(std::bind(&HttpClient::processhttp, this)), loop_(NULL), mutex_(), cond_(mutex_)
{
    thread_.start();
    {
        MutexLockGuard lock(mutex_);
        while(loop_ == NULL) {
            cond_.wait();
        }
    }
    client_.reset(new TcpClient(loop_, ""));
    client_->setConnectionCallback(std::bind(&HttpClient::onConnection, this, _1));
    client_->setMessageCallback(std::bind(&HttpClient::onMessage, this, _1, _2, _3));
    // client_->enableRetry();
}

void HttpClient::processhttp()
{
    EventLoop loop;
    {
        MutexLockGuard lock(mutex_);
        loop_ = &loop;
    }
    cond_.notify();
    loop.loop();
    LOG_INFO << "t";
}

void HttpClient::setServerAddr(const libmevent::net::InetAddress& serverAddr)
{
    client_->setServerAddr(serverAddr);
}

void HttpClient::onConnection(const TcpConnectionPtr& conn)
{
    // LOG_TRACE << conn->localAddress().toIpPort() << " -> " << conn->peerAddress().toIpPort() << " is " << (conn->connected() ? "UP" : "DOWN");
    addHeader("Accept", "*/*");
    addHeader("Host", "zjm");
    addHeader("Cache-Control", "no-cache");
    setContentType("application/xml");
    setCloseConnection(false);
    appendToBuffer(&requestBuffer_);
    conn->send(&requestBuffer_);
    Timer_ = loop_->runAfter(5.0, std::bind(&HttpClient::timeout, this));
}
extern libmevent::MutexLock g_mutex;
extern libmevent::Condition g_cond;
void HttpClient::onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time)
{
    loop_->cancel(Timer_);
    string msg(buf->retrieveAllAsString());
    auto pos = msg.find("\r\n\r\n");
    if(pos != msg.npos) {
        postbody_ = msg.substr(pos + 4, msg.length());
    }
    LOG_INFO << " recv " << postbody_;
    conn->forceClose();
    {
        MutexLockGuard lock(g_mutex);
    }
    g_cond.notify();
}

void HttpClient::appendToBuffer(Buffer* output) const
{
    char buf[32];
    snprintf(buf, sizeof buf, "POST %s HTTP/1.0", filepath_.c_str());
    output->append(buf);
    output->append("\r\n");

    if(closeConnection_) {
        snprintf(buf, sizeof buf, "Content-Length: %zd\r\n", body_.size());
        output->append(buf);
        output->append("Connection: close\r\n");
    } else {
        snprintf(buf, sizeof buf, "Content-Length: %zd\r\n", body_.size());
        output->append(buf);
        output->append("Connection: Keep-Alive\r\n");
    }

    for(const auto& header : headers_) {
        output->append(header.first);
        output->append(": ");
        output->append(header.second);
        output->append("\r\n");
    }
    output->append("\r\n");
    output->append(body_);
}

void HttpClient::parseUrl(const char* mUrl)
{
    assert(mUrl != NULL);
    string::size_type n;
    string url = mUrl;

    if(url.substr(0, 7) == "http://")
        url.erase(0, 7);
    else
        LOG_FATAL << "http:// error";

    // if(url.substr(0, 8) == "https://") url.erase(0, 8);

    n = url.find(':');
    if(n != string::npos) {
        serverip_ = url.substr(0, n);
        url.erase(0, n + 1);
    } else
        LOG_FATAL << "http ip port not found";
    n = url.find('/');
    if(n != string::npos) {
        port_ = url.substr(0, n);
        url.erase(0, n);
    } else
        LOG_FATAL << "http filepath not found";
    libmevent::net::InetAddress serverAddr(serverip_.c_str(), stoi(port_));
    setServerAddr(serverAddr);
    filepath_ = url;
}

// int main(int argc, char* argv[])
// {
//     EventLoop loop;
//     printf("hh");
//     // HttpClient clients(&loop, "http://192.168.1.17:6000/test/c", "cc");
//     HttpClient clients(&loop, "http://192.168.252.183:6000/test/c", "cc");
//     // clients.parseUrl("http://127.0.0.1:63/test/c");
//     clients.connect();
//     loop.loop();
//     LOG_INFO << " eddll ";
// }
