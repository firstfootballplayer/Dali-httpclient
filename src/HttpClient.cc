#include "libmevent/net/TcpClient.h"
#include "libmevent/base/Logging.h"
#include "libmevent/base/Thread.h"
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
    loop_->quit();
}

HttpClient::HttpClient(libmevent::net::EventLoop* loop, const libmevent::net::InetAddress& listenAddr, const std::string& id) : loop_(loop), client_(new TcpClient(loop, listenAddr, ""))
{
    client_->setConnectionCallback(std::bind(&HttpClient::onConnection, this, _1));
    client_->setMessageCallback(std::bind(&HttpClient::onMessage, this, _1, _2, _3));
    // client_->enableRetry();
}

HttpClient::HttpClient(libmevent::net::EventLoop* loop, char* url, char* strParam) : loop_(loop)
{
    parseUrl(url);
    setBody(strParam);
    InetAddress serverAddr(serverip_.c_str(), stoi(port_));
    client_.reset(new TcpClient(loop, serverAddr, ""));
    client_->setConnectionCallback(std::bind(&HttpClient::onConnection, this, _1));
    client_->setMessageCallback(std::bind(&HttpClient::onMessage, this, _1, _2, _3));
    // client_->enableRetry();
}

void HttpClient::onConnection(const TcpConnectionPtr& conn)
{
    // LOG_TRACE << conn->localAddress().toIpPort() << " -> " << conn->peerAddress().toIpPort() << " is " << (conn->connected() ? "UP" : "DOWN");
    LOG_INFO << "entry -------------------------";
    addHeader("Accept", "*/*");
    addHeader("Host", "zjm");
    addHeader("Cache-Control", "no-cache");
    setContentType("application/xml");
    setCloseConnection(false);
    appendToBuffer(&requestBuffer_);
    conn->send(&requestBuffer_);
    Timer_ = loop_->runAfter(5.0, std::bind(&HttpClient::timeout, this));
}

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

    loop_->quit();
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

void HttpClient::parseUrl(char* mUrl)
{
    string::size_type n;
    string url = mUrl;

    if(url.substr(0, 7) == "http://") url.erase(0, 7);

    // if(url.substr(0, 8) == "https://") url.erase(0, 8);

    n = url.find(':');
    if(n != string::npos) {
        serverip_ = url.substr(0, n);
        url.erase(0, n + 1);
    }
    n = url.find('/');
    if(n != string::npos) {
        port_ = url.substr(0, n);
        url.erase(0, n);
    }
    filepath_ = url;
}

int main(int argc, char* argv[])
{
    EventLoop loop;
    HttpClient clients(&loop, "http://192.168.1.17:6000/test/c", "cc");
    // clients.parseUrl("http://127.0.0.1:63/test/c");
    clients.connect();
    loop.loop();
    LOG_INFO << " eddll ";
}
