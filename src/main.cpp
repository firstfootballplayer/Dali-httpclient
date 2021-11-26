#include "libmevent/net/TcpServer.h"
#include "libmevent/base/Logging.h"
#include "libmevent/base/Thread.h"
#include "libmevent/net/EventLoop.h"
#include "libmevent/net/InetAddress.h"
#include "libmevent/base/LogFile.h"
#include <utility>
#include <stdio.h>
#include <unistd.h>
#include "MyXml.h"
#include "myHttpclient.h"
#include "managesql.h"
using namespace libmevent;
using namespace libmevent::net;

int numThreads = 0;
// std::unique_ptr<libmevent::LogFile> g_logFile;
// void outputFunc(const char* msg, int len)
// {
//     g_logFile->append(msg, len);
// }

// void flushFunc()
// {
//     g_logFile->flush();
// }

void callback()
{
    printf("callback(): pid = %d, tid = %d\n", getpid(), CurrentThread::tid());
}

int main(int argc, char* argv[])
{
    // LOG_INFO << "pid = " << getpid() << ", tid = " << CurrentThread::tid();
    // LOG_INFO << "sizeof TcpConnection = " << sizeof(TcpConnection);
    // g_logFile.reset(new ::LogFile(::basename("tt"), 200 * 100000));
    // ::Logger::setOutput(outputFunc);
    // ::Logger::setFlush(flushFunc);
    ::Logger::setLogLevel(Logger::LogLevel::TRACE);
    // MysqlManager sqlManager;
    MyXml xmlManager;
    // CurlHttp::Request("http://192.168.1.17:6000/test/c", "ccpost_Xml");
    // CurlHttp::Request("http://192.168.1.17:6000/test/c", "ccpost_Xml");

    CurlHttp::Request("http://192.168.249.99:6000/test/c", "ccpost_Xml");
    int c = 1;
    printf("hello Requestcccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc\n");
    printf("hello Request\n");
    printf("hello Request\n");
    sleep(2);
    CurlHttp::Request("http://192.168.249.99:6000/test/c", "ccpost_Xml");
}
