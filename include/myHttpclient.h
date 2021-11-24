#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <curl/curl.h>
#include "libmevent/base/Logging.h"

/************************************************************************/
/*           libcurl库封装    zhanjiamin 2021年8月2日 13:17:11      */
/************************************************************************/

//表单key对应的类型
enum E_KEY_TYPE
{
    e_key_text,  //文本类型
    e_key_iamge  //图片类型
};

//表单信息结构
typedef struct
{
    std::string strKey;
    std::string strVal;
    E_KEY_TYPE eKeyType;

    void Set(std::string key, std::string val, E_KEY_TYPE eType)
    {
        strKey = key;
        strVal = val;
        eKeyType = eType;
    }
} POST_LIST, *LPPOST_LIST;

//表单数据
#define _POST_LIST_DATA_ std::vector<POST_LIST>

class CurlHttp
{
public:
    CurlHttp(void);
    ~CurlHttp(void);
    static std::string Request(std::string strUrl, std::string strParam = "", std::string strRequestType = "post", std::string strHeader = "", std::string strCookie = "", std::string strCaPath = "", int nTimeOut = 3);

    //有图片建议使用表单提交比较方便
    static int RequestSSL(std::string strUrl, std::string& strReport, _POST_LIST_DATA_ listParam, std::string strHeader = "", std::string strCookie = "", std::string strCaPath = "", int nTimeOut = 0);
    static int FtpUpload(const char* remote_file_path, const char* local_file_path, const char* username, const char* password, long timeout, long tries = 3);
    static int FtpDownload(const char* remote_file_path, const char* local_file_path, const char* username, const char* password, long timeout = 3);
    //转码相关函数
    // static std::string GBKToUTF8(const char* strGBK);
    // static std::string UTF8ToGBK(const char* strUTF8);
};
