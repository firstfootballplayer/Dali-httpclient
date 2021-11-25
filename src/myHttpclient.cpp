#include <sys/stat.h>
#include "myHttpclient.h"
#include "libmevent/base/Logging.h"
#include "libmevent/net/HttpClient.h"
#include <iostream>
using namespace std;
namespace _CURL_
{

/**
 * buf: 从服务器返回的buffer
 * unit: buufer的单位
 * bufSize: buffer的大小
 * data: 保存从服务器返回的内容
 * 注意这个函数会被调用多次
 */
static size_t write_data(void* buf, size_t unit, size_t bufSize, std::string* data)
{
    int size = unit * bufSize;
    char* tmp = (char*)malloc(size + 1);
    memcpy(tmp, buf, size);
    tmp[size] = '\0';
    data->append(tmp);
    free(tmp);
    return size;
}

//智能初始化curl库和释放curl库
class CurlIntelligence
{
public:
    CurlIntelligence()
    {
        curl_global_init(CURL_GLOBAL_ALL);
    }

    ~CurlIntelligence()
    {
        curl_global_cleanup();
    }
};
}  // namespace _CURL_

_CURL_::CurlIntelligence g_curl;

CurlHttp::CurlHttp(void)
{
}

CurlHttp::~CurlHttp(void)
{
}

/*
 *	函数：
 *		 Request（请求函数）
 *  参数：
 *		strRequestType：请求类型（get，post）
 *		strUrl:请求url地址
 *		strReport：回执信息
 *		strHeader:请求头
 *		strCookie：cookie信息
 *		strCaPath：ca转成pem证书路径
 *		strParam：请求参数（get的时候此参数填空）
 *		nTimeOut:超时设置默认是0秒 是无限等待
 *  返回值：
 *		0表示成功 非0表示错误代码
 */
static libmevent::net::EventLoop loop;
static HttpClient g_client(&loop);
std::string CurlHttp::Request(std::string strUrl, std::string strParam, std::string strRequestType /* ="post" */, std::string strHeader /* ="" */, std::string strCookie /* ="" */, std::string strCaPath /* ="" */, int nTimeOut /* =0 */)
{
    g_client.parseUrl(strUrl.c_str());
    g_client.setBody(strParam.c_str());
    g_client.connect();
    loop.loop();
}
// std::string CurlHttp::Request(std::string strUrl, std::string strParam, std::string strRequestType /* ="post" */, std::string strHeader /* ="" */, std::string strCookie /* ="" */, std::string strCaPath /* ="" */, int nTimeOut /* =0 */)
// {
//     std::string strReport;
//     CURL* curl;
//     curl = curl_easy_init();
//     curl_easy_setopt(curl, CURLOPT_URL, strUrl.c_str());

//     if(strRequestType.compare("post") == 0 || strRequestType.compare("POST") == 0) {
//         curl_easy_setopt(curl, CURLOPT_POST, 1);
//         curl_easy_setopt(curl, CURLOPT_POSTFIELDS, strParam.c_str());
//     } else {
//         curl_easy_setopt(curl, CURLOPT_POST, 0);  // get请求
//     }

//     //判断是否有证书
//     if(strCaPath.empty()) {
//         curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
//         curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
//     } else {
//         //缺省情况就是PEM，所以无需设置，另外支持DER
//         // curl_easy_setopt(curl,CURLOPT_SSLCERTTYPE,"PEM");
//         curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);
//         curl_easy_setopt(curl, CURLOPT_CAINFO, strCaPath.c_str());
//     }

//     std::string strReportHeader;  //回执回来的头数据
//     // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);		//可以看到调试信息
//     //接受服务器的ssl证书而不管合不合法 （相当于命令行中的--insecure）
//     curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
//     curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
//     curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, _CURL_::write_data);
//     curl_easy_setopt(curl, CURLOPT_WRITEDATA, &strReport);
//     if(nTimeOut > 0) {
//         curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, nTimeOut);
//         curl_easy_setopt(curl, CURLOPT_TIMEOUT, nTimeOut);
//     }

//     if(!strHeader.empty()) {
//         curl_easy_setopt(curl, CURLOPT_HTTPHEADER, strHeader.c_str());
//     }

//     if(!strCookie.empty()) {
//         curl_easy_setopt(curl, CURLOPT_COOKIEFILE, strCookie.c_str());
//     }
//     CURLcode res = curl_easy_perform(curl);
//     if(res != CURLE_OK) {
//         switch(res) {
//         case CURLE_UNSUPPORTED_PROTOCOL:
//             LOG_WARN << "libcurl"
//                      << "不支持的协议,由URL的头部指定";
//             break;
//         case CURLE_COULDNT_CONNECT:
//             LOG_WARN << "libcurl"
//                      << "不支持的协议,由URL的头部指定";
//             break;
//         case CURLE_HTTP_RETURNED_ERROR:
//             LOG_WARN << "libcurl"
//                      << "http返回错误";
//             break;
//         case CURLE_READ_ERROR:
//             LOG_WARN << "libcurl"
//                      << "读本地文件错误";
//             break;
//         case CURLE_OPERATION_TIMEDOUT:
//             LOG_WARN << "libcurl"
//                      << "操作超时";
//             break;
//         default:
//             LOG_WARN << "libcurl error" << res;
//         }
//     }
//     curl_easy_cleanup(curl);
//     // cout << strReport << endl;
//     return strReport;
// }

/*
 *	函数：
 *		 RequestSSL（表单提交）
 *  参数：
 *		strUrl:请求url地址
 *		strReport：回执信息
 *		strHeader:请求头
 *		strCookie：cookie信息
 *		listParam：表单列表
 *		strCaPath：ca转成pem证书路径
 *		nTimeOut:超时设置默认是0秒 是无限等待：
 *  返回值：
 */
int CurlHttp::RequestSSL(std::string strUrl, std::string& strReport, _POST_LIST_DATA_ listParam, std::string strHeader /* ="" */, std::string strCookie /* ="" */, std::string strCaPath /* ="" */, int nTimeOut /* =0 */)
{
    CURLcode code;
    CURL* curl;
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_URL, strUrl.c_str());
    // err = curl_easy_setopt(hCurl, CURLOPT_HTTPHEADER, "dfsdf");
    struct curl_httppost* post = NULL;
    struct curl_httppost* last = NULL;

    // CURLFORMcode errf;
    for(unsigned int i = 0; i < listParam.size(); i++) {
        POST_LIST post_list = listParam.at(i);
        if(post_list.eKeyType == e_key_iamge)  //图片类型 直接提交图片路径
        {
            curl_formadd(&post, &last, CURLFORM_COPYNAME, post_list.strKey.c_str(), CURLFORM_FILE, post_list.strVal.c_str(), CURLFORM_CONTENTTYPE, "image/jpeg", CURLFORM_END);
        } else {
            curl_formadd(&post, &last, CURLFORM_COPYNAME, post_list.strKey.c_str(), CURLFORM_COPYCONTENTS, post_list.strVal.c_str(), CURLFORM_END);
        }
    }
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, _CURL_::write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &strReport);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);

    //判断是否有证书
    if(strCaPath.empty()) {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
    } else {
        //缺省情况就是PEM，所以无需设置，另外支持DER
        // curl_easy_setopt(curl,CURLOPT_SSLCERTTYPE,"PEM");
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);
        curl_easy_setopt(curl, CURLOPT_CAINFO, strCaPath.c_str());
    }

    if(nTimeOut > 0) {
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, nTimeOut);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, nTimeOut);
    }
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);  //是否抓取跳转后的页面
    /* Set the form info */
    curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);  //
    curl_easy_setopt(curl, CURLOPT_HEADER, 0);       //不读取返回头的数据

    if(!strHeader.empty()) {
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, strHeader.c_str());
    }

    if(!strCookie.empty()) {
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, strCookie.c_str());
    }
    code = curl_easy_perform(curl); /* post away! */
    //获取请求返回的值  如：200
    // code = curl_easy_getinfo(curl,CURLINFO_RESPONSE_CODE, &RESPONSE_CODE);
    /* free the post data again */
    curl_formfree(post);
    curl_easy_cleanup(curl);
    return code;
}

struct CustomProgress
{
    curl_off_t lastruntime; /* type depends on version, see above */
    CURL* curl;
};

// work for both download and upload
int progressCallback(void* p, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow)
{
    printf("TOTAL TIME:  \n");
    struct CustomProgress* progress = (struct CustomProgress*)p;
    CURL* curl = progress->curl;
    curl_off_t curtime = 0;

    curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME_T, &curtime);

    /* under certain circumstances it may be desirable for certain functionality
     to only run every N seconds, in order to do this the transaction time can
     be used */
    if((curtime - progress->lastruntime) >= 3000000) {
        progress->lastruntime = curtime;
        printf("TOTAL TIME: %f \n", curtime);
    }

    // do something to display the progress
    printf("UP: %ld bytes of %ld bytes, DOWN: %ld bytes of %ld bytes \n", ulnow, ultotal, dlnow, dltotal);
    if(ultotal) printf("UP progress: %0.2f\n", float(ulnow / ultotal));
    if(dltotal) printf("DOWN progress: %0.2f\n", float(dlnow / dltotal));

    return 0;
}

// ---- upload related ---- //
// parse headers for Content-Length
size_t getContentLengthFunc(void* ptr, size_t size, size_t nmemb, void* stream)
{
    int r;
    long len = 0;

    r = sscanf((const char*)ptr, "Content-Length: %ld\n", &len);
    if(r) /* Microsoft: we don't read the specs */
        *((long*)stream) = len;
    return size * nmemb;
}

// discard already downloaded data
size_t discardFunc(void* ptr, size_t size, size_t nmemb, void* stream)
{
    return size * nmemb;
}

// read data to upload
size_t readfunc(void* ptr, size_t size, size_t nmemb, void* stream)
{
    printf("Local file size: %d : %d bytes.\n", size, nmemb);
    FILE* f = (FILE*)stream;
    size_t n;
    if(ferror(f)) return CURL_READFUNC_ABORT;
    n = fread(ptr, size, nmemb, f) * size;
    return n;
}

/*
 *	函数：
 *		 FTP upload（FTP上传）
 *  参数：
 *		remote_file_path:FTPurl地址
 *		local_file_path：本地文件地址
 *		username:用户名
 *		password：密码
 *		timeout：超时时间
 *		tries：重试 *
 *  返回值：
 */
// do upload, will overwrite existing file
int CurlHttp::FtpUpload(const char* remote_file_path, const char* local_file_path, const char* username, const char* password, long timeout, long tries)
{
    CURL* curlhandle = curl_easy_init();
    struct stat file_info;
    curl_off_t fsize;
    // get user_key pair
    char user_key[1024] = { 0 };
    sprintf(user_key, "%s:%s", username, password);

    FILE* file;
    long uploaded_len = 0;
    CURLcode ret = CURLE_GOT_NOTHING;

    /* 获得上传文件的大小 */
    if(stat(local_file_path, &file_info)) {
        printf("Couldn't open '%s': %s\n", local_file_path, strerror(errno));
        LOG_WARN << "Couldn't open %s" << local_file_path;
        return 1;
    }
    fsize = (curl_off_t)file_info.st_size;
    printf("Local file size: %" CURL_FORMAT_CURL_OFF_T " bytes.\n", fsize);

    file = fopen(local_file_path, "rb");
    if(file == NULL) {
        LOG_WARN << "Couldn't open %s" << local_file_path;
        perror(NULL);
        return 0;
    }
    curl_easy_setopt(curlhandle, CURLOPT_UPLOAD, 1L);
    curl_easy_setopt(curlhandle, CURLOPT_URL, remote_file_path);
    curl_easy_setopt(curlhandle, CURLOPT_USERPWD, user_key);
    if(timeout) curl_easy_setopt(curlhandle, CURLOPT_FTP_RESPONSE_TIMEOUT, timeout);
    // curl_easy_setopt(curlhandle, CURLOPT_HEADERFUNCTION, getContentLengthFunc);
    // curl_easy_setopt(curlhandle, CURLOPT_HEADERDATA, &uploaded_len);
    // curl_easy_setopt(curlhandle, CURLOPT_WRITEFUNCTION, discardFunc);
    curl_easy_setopt(curlhandle, CURLOPT_READFUNCTION, readfunc);
    curl_easy_setopt(curlhandle, CURLOPT_READDATA, file);
    /*设置要上传的文件的大小（可选） */
    curl_easy_setopt(curlhandle, CURLOPT_INFILESIZE_LARGE, (curl_off_t)fsize);
    curl_easy_setopt(curlhandle, CURLOPT_FTPPORT, "-"); /* disable passive mode */
    curl_easy_setopt(curlhandle, CURLOPT_FTP_CREATE_MISSING_DIRS, 1L);

    // set upload progress
    // curl_easy_setopt(curlhandle, CURLOPT_XFERINFOFUNCTION, progressCallback);
    // struct CustomProgress prog;
    // curl_easy_setopt(curlhandle, CURLOPT_XFERINFODATA, &prog);
    // curl_easy_setopt(curlhandle, CURLOPT_NOPROGRESS, 1);

    curl_easy_setopt(curlhandle, CURLOPT_VERBOSE, 1L);  // if set 1, debug mode will print some low level msg

    // upload: 断点续传
    for(int c = 0; (ret != CURLE_OK) && (c < tries); c++) {
        /* are we resuming? */
        if(c) { /* yes */
                /* determine the length of the file already written */
                /*
                 * With NOBODY and NOHEADER, libcurl will issue a SIZE
                 * command, but the only way to retrieve the result is
                 * to parse the returned Content-Length header. Thus,
                 * getContentLengthfunc(). We need discardfunc() above
                 * because HEADER will dump the headers to stdout
                 * without it.
                 */
            curl_easy_setopt(curlhandle, CURLOPT_NOBODY, 1L);
            curl_easy_setopt(curlhandle, CURLOPT_HEADER, 1L);
            ret = curl_easy_perform(curlhandle);
            if(ret != CURLE_OK) continue;
            curl_easy_setopt(curlhandle, CURLOPT_NOBODY, 0L);
            curl_easy_setopt(curlhandle, CURLOPT_HEADER, 0L);
            fseek(file, uploaded_len, SEEK_SET);
            curl_easy_setopt(curlhandle, CURLOPT_APPEND, 1L);
        } else
            curl_easy_setopt(curlhandle, CURLOPT_APPEND, 0L);

        ret = curl_easy_perform(curlhandle);
    }
    fclose(file);

    int curl_state = 0;
    if(ret == CURLE_OK) {
        curl_state = 1;
        LOG_WARN << "FTP_OK" << remote_file_path;
    } else {
        LOG_WARN << "FTP ERROR: " << curl_easy_strerror(ret);
        curl_state = 0;
    }

    // exit curl handle
    curl_easy_cleanup(curlhandle);

    return curl_state;
}

// ---- download related ---- //
// write data to upload
size_t writeFunc(void* ptr, size_t size, size_t nmemb, void* stream)
{
    // std::cout << "--- write func ---" << std::endl;
    return fwrite(ptr, size, nmemb, (FILE*)stream);
}

// do download, will overwrite existing file
int CurlHttp::FtpDownload(const char* remote_file_path, const char* local_file_path, const char* username, const char* password, long timeout)
{
    CURL* curlhandle = curl_easy_init();

    // get user_key pair
    char user_key[1024] = { 0 };
    sprintf(user_key, "%s:%s", username, password);

    FILE* file;
    curl_off_t local_file_len = -1;
    long filesize = 0;
    CURLcode ret = CURLE_GOT_NOTHING;
    struct stat file_info;
    int use_resume = 0;  // resume flag

    // get local file info, if success ,set resume mode
    if(stat(local_file_path, &file_info) == 0) {
        local_file_len = file_info.st_size;
        use_resume = 1;
    }

    // read file in append mode: 断点续传
    file = fopen(local_file_path, "ab+");
    if(file == NULL) {
        perror(NULL);
        return 0;
    }
    curl_easy_setopt(curlhandle, CURLOPT_URL, remote_file_path);
    curl_easy_setopt(curlhandle, CURLOPT_USERPWD, user_key);  // set user:password
                                                              // set connection timeout
    curl_easy_setopt(curlhandle, CURLOPT_CONNECTTIMEOUT, timeout);
    // set header process, get content length callback
    curl_easy_setopt(curlhandle, CURLOPT_HEADERFUNCTION, getContentLengthFunc);
    curl_easy_setopt(curlhandle, CURLOPT_HEADERDATA, &filesize);

    // 断点续传 set download resume, if use resume, set current local file length
    // curl_easy_setopt(curlhandle, CURLOPT_RESUME_FROM_LARGE, use_resume ? local_file_len : 0);

    curl_easy_setopt(curlhandle, CURLOPT_WRITEFUNCTION, writeFunc);
    curl_easy_setopt(curlhandle, CURLOPT_WRITEDATA, file);

    // set download progress
    curl_easy_setopt(curlhandle, CURLOPT_XFERINFOFUNCTION, progressCallback);
    struct CustomProgress prog;
    curl_easy_setopt(curlhandle, CURLOPT_XFERINFODATA, &prog);
    // curl_easy_setopt(curlhandle, CURLOPT_NOPROGRESS, 1);

    // curl_easy_setopt(curlhandle, CURLOPT_VERBOSE, 1);  // if set 1, debug mode will print some low level msg

    ret = curl_easy_perform(curlhandle);
    fclose(file);

    int curl_state = 0;
    if(ret == CURLE_OK)
        curl_state = 1;
    else {
        fprintf(stderr, "%s\n", curl_easy_strerror(ret));
        curl_state = 0;
    }

    // exit curl handle
    curl_easy_cleanup(curlhandle);

    return curl_state;
}

// std::string CurlHttp::GBKToUTF8(const char* strGBK)
// {
//     int len = MultiByteToWideChar(CP_ACP, 0, strGBK, -1, NULL, 0);
//     wchar_t* wstr = new wchar_t[len + 1];
//     memset(wstr, 0, len + 1);
//     MultiByteToWideChar(CP_ACP, 0, strGBK, -1, wstr, len);
//     len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
//     char* str = new char[len + 1];
//     memset(str, 0, len + 1);
//     WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
//     std::string strTemp = str;
//     if(wstr) delete[] wstr;
//     if(str) delete[] str;
//     return strTemp;
// }

// std::string CurlHttp::UTF8ToGBK(const char* strUTF8)
// {
//     int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, NULL, 0);
//     wchar_t* wszGBK = new wchar_t[len + 1];
//     memset(wszGBK, 0, len * 2 + 2);
//     MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, wszGBK, len);
//     len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
//     char* szGBK = new char[len + 1];
//     memset(szGBK, 0, len + 1);
//     WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
//     std::string strTemp(szGBK);
//     if(wszGBK) delete[] wszGBK;
//     if(szGBK) delete[] szGBK;
//     return strTemp;
// }
