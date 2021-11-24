// #include <iostream>
// #include <winsock2.h>
// #include <vector>
// #include <windows.h>
// #include <stdio.h>
// #include <CentralBase.h>
// #include <dbghelp.h>
// #include <stdio.h>
// #include "rapidjson/stringbuffer.h"
// #include "rapidjson/writer.h"
// #include "MyXml.h"
// #include "myHttpclient.h"
// #include "managesql.h"
// #include "Utilities.h"
// #include "slog.h"
// using namespace std;
// using namespace CentralModule;
// extern wstring kstationid;
// extern char g_urlhead[128];
// extern char g_url[128];
// extern char g_FTP_IP[128];
// extern char g_FTP_Port[128];
// extern char g_FTP_UserName[128];
// extern char g_FTP_PassWord[128];
// wstring string2wstring(string str)
// {
//     wstring result;
//     //获取缓冲区大小，并申请空间，缓冲区大小按字符计算
//     int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
//     WCHAR* buffer = new WCHAR[len + 1];
//     //多字节编码转换成宽字节编码
//     MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
//     buffer[len] = '\0';  //添加字符串结尾
//     //删除缓冲区并返回值
//     result.append(buffer);
//     delete[] buffer;
//     return result;
// }

// //将wstring转换成string
// string wstring2string(wstring wstr)
// {
//     string result;
//     //获取缓冲区大小，并申请空间，缓冲区大小事按字节计算的
//     int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
//     char* buffer = new char[len + 1];
//     //宽字节编码转换成多字节编码
//     WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
//     buffer[len] = '\0';
//     //删除缓冲区并返回值
//     result.append(buffer);
//     delete[] buffer;
//     return result;
// }

// std::string find_first_str(const char* pstr)
// {
//     int num = 0;
//     const char* p = pstr;
//     while(*p != '\0') {
//         if(*p == ' ') {
//             char dest[100];
//             memcpy_s(dest, sizeof(dest), pstr, num);
//             dest[num] = '\0';
//             std::string first_str = dest;
//             return first_str;
//         }
//         num++;
//         p++;
//     }
//     return "";
// }

// //中文 转为 utf-8
// string UTF8_URL_ENCODE(const char* Chinese)
// {
//     //中文 -> unicode  -> utf-8
//     wchar_t unicode[128] = { 0 };
//     MultiByteToWideChar(CP_ACP, 0, Chinese, strlen(Chinese), unicode, 128);
//     unsigned char sz[128] = { 0 };
//     WideCharToMultiByte(CP_UTF8, 0, unicode, wcslen(unicode), (LPSTR)sz, 128, 0, 0);
//     string EncodeStr;
//     char SrcStr[128] = { 0 };
//     for(int i = 0; i < 128; i++) {
//         if(sz[i] != NULL) {
//             sprintf(SrcStr, "%%%X", sz[i]);
//             EncodeStr += SrcStr;
//         }
//     }
//     transform(EncodeStr.begin(), EncodeStr.end(), EncodeStr.begin(), tolower);
//     return EncodeStr;
// }

// void extract_HMS(int time, int& hour, int& minute, int& second)
// {
//     second = time % 100;
//     time /= 100;
//     // cerr << second << endl;
//     minute = time % 100;
//     time /= 100;
//     // cerr << minute << endl;
//     hour = time % 100;
//     // cerr << hour << endl;
// }

// void extract_YMD(int time, int& year, int& month, int& day)
// {
//     day = time % 100;
//     time /= 100;
//     // cerr << second << endl;
//     month = time % 100;
//     time /= 100;
//     // cerr << minute << endl;
//     year = time % 10000;
//     // cerr << hour << endl;
// }

// //判断字符是否是中文
// int is_zh_ch(char p)
// {
//     if(~(p >> 8) == 0) {
//         return 1;
//     }
//     return -1;
// }
// string extract_Chinese(string str)
// {
//     if(typeid(str) == typeid(string) && str.length() > 0) {
//         int len = str.length();
//         string tmp = "";
//         vector<string> dump;
//         int i = 0;
//         while(i < len) {
//             if(is_zh_ch(str.at(i)) == 1) {
//                 dump.push_back(str.substr(i, 2));
//                 i = i + 2;
//             } else {
//                 i = i + 1;
//             }
//         }
//         for(auto s : dump) {
//             tmp += s;
//         }
//         return tmp;
//     }
// }

// int IncludeChinese(char* str)
// {
//     int nRet = 0;
//     char c;
//     while(c = *str++) {
//         //如果字符高位为1且下一字符高位也是1则有中文字符
//         if((c & 0x80) && (*str & 0x80)) {
//             nRet = 1;
//             break;
//         }
//     }
//     return nRet;
// }

// void find_DevType(const string& dest, wstring& type)
// {
//     if(!strcmp(dest.c_str(), "2")) {
//         type = L"401";
//     } else if(!strcmp(dest.c_str(), "6")) {
//         type = L"402";
//     } else if(!strcmp(dest.c_str(), "7")) {
//         type = L"404";
//     } else if(!strcmp(dest.c_str(), "22")) {
//         type = L"405";
//     } else if(!strcmp(dest.c_str(), "5")) {
//         type = L"406";
//     } else if(!strcmp(dest.c_str(), "4")) {
//         type = L"407";
//     } else if(!strcmp(dest.c_str(), "8")) {
//         type = L"408";
//     } else if(!strcmp(dest.c_str(), "11")) {
//         type = L"410";
//     } else if(!strcmp(dest.c_str(), "12") || !strcmp(dest.c_str(), "16")) {
//         type = L"412";
//     } else if(!strcmp(dest.c_str(), "26")) {
//         type = L"421";
//     } else if(!strcmp(dest.c_str(), "21")) {
//         type = L"415";
//     } else if(!strcmp(dest.c_str(), "9")) {
//         type = L"416";
//     } else if(!strcmp(dest.c_str(), "10")) {
//         type = L"417";
//     } else if(!strcmp(dest.c_str(), "25")) {
//         type = L"420";
//     } else if(!strcmp(dest.c_str(), "20")) {
//         type = L"424";
//     } else if(!strcmp(dest.c_str(), "15") || !strcmp(dest.c_str(), "17") || !strcmp(dest.c_str(), "18")) {
//         type = L"425";
//     } else if(!strcmp(dest.c_str(), "13") || !strcmp(dest.c_str(), "14") || !strcmp(dest.c_str(), "19") || !strcmp(dest.c_str(), "24")) {
//         type = L"426";
//     } else if(!strcmp(dest.c_str(), "3")) {
//         type = L"422";
//     }
// }
// void find_MeterType(const string& dest, wstring& type)
// {
//     if(!strcmp(dest.c_str(), "1")) {
//         type = L"701";
//     } else if(!strcmp(dest.c_str(), "2")) {
//         type = L"702";
//     } else if(!strcmp(dest.c_str(), "3")) {
//         type = L"703";
//     } else if(!strcmp(dest.c_str(), "4")) {
//         type = L"704";
//     } else if(!strcmp(dest.c_str(), "5")) {
//         type = L"705";
//     } else if(!strcmp(dest.c_str(), "6")) {
//         type = L"707";
//     } else if(!strcmp(dest.c_str(), "7")) {
//         type = L"706";
//     } else if(!strcmp(dest.c_str(), "8")) {
//         type = L"708";
//     } else if(!strcmp(dest.c_str(), "9")) {
//         type = L"709";
//     }
// }

// void RecognType_DeviceID(const std::string& Result_ID, std::wstring& RecognType, std::wstring& LinkID, std::wstring& FileType)
// {
//     char query[1024];
//     MysqlManager sqlManager;
//     sprintf(query, "select Device_Id from InspectionResult where Result_ID=%s", Result_ID.c_str());
//     string Device_Id = sqlManager.query_singleResult(query);
//     LinkID = string2wstring(Device_Id);
//     sprintf(query, "select DeviceType from DeviceInfo where Device_Id=%s", Device_Id.c_str());
//     string DeviceType = sqlManager.query_singleResult(query);
//     if(!strcmp(DeviceType.c_str(), "1")) {
//         RecognType = L"601";
//     } else if(!strcmp(DeviceType.c_str(), "2")) {
//         RecognType = L"605";
//     } else if(!strcmp(DeviceType.c_str(), "3") || !strcmp(DeviceType.c_str(), "9")) {
//         RecognType = L"606";
//     } else if(!strcmp(DeviceType.c_str(), "4")) {
//         RecognType = L"607";
//     } else {
//         RecognType = L"603";
//     }
//     if(!strcmp(DeviceType.c_str(), "2")) {
//         FileType = L"501";
//     } else if(!strcmp(DeviceType.c_str(), "5") || !strcmp(DeviceType.c_str(), "1")) {
//         FileType = L"502";
//     } else if(!strcmp(DeviceType.c_str(), "3") || !strcmp(DeviceType.c_str(), "9")) {
//         FileType = L"504";
//     } else if(!strcmp(DeviceType.c_str(), "4")) {
//         FileType = L"507";
//     } else {
//         FileType = L"509";
//     }
// }

// void set_AlarmType(const string& Inspection_Status, wstring& AlarmType)
// {
//     if(!strcmp(Inspection_Status.c_str(), "111") || !strcmp(Inspection_Status.c_str(), "121") || !strcmp(Inspection_Status.c_str(), "231")) {
//         AlarmType = L"1901";
//     } else if(!strcmp(Inspection_Status.c_str(), "122")) {
//         AlarmType = L"1902";
//     } else if(!strcmp(Inspection_Status.c_str(), "2")) {
//         AlarmType = L"1905";
//     } else {
//         AlarmType = L"1905";
//     }
// }

// void set_Coordinate(const std::string& Result_ID, std::wstring& Coordinate)
// {
//     MysqlManager sqlManager;
//     char query[1024];
//     std::string RLeft;
//     std::string RTop;
//     std::string RRight;
//     std::string RBottom;
//     sprintf_s(query, "select RLeft from InspectionResult where Result_ID=%s", Result_ID.c_str());
//     RLeft = sqlManager.query_singleResult(query);
//     sprintf_s(query, "select RTop from InspectionResult where Result_ID=%s", Result_ID.c_str());
//     RTop = sqlManager.query_singleResult(query);
//     sprintf_s(query, "select RRight from InspectionResult where Result_ID=%s", Result_ID.c_str());
//     RRight = sqlManager.query_singleResult(query);
//     sprintf_s(query, "select RBottom from InspectionResult where Result_ID=%s", Result_ID.c_str());
//     RBottom = sqlManager.query_singleResult(query);
//     rapidjson::StringBuffer strBuf;
//     rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
//     writer.StartArray();
//     writer.StartObject();
//     writer.Key("X");
//     writer.String(RLeft.c_str());
//     writer.Key("Y");
//     writer.String(RBottom.c_str());
//     writer.EndObject();
//     writer.StartObject();
//     writer.Key("X");
//     writer.String(RRight.c_str());
//     writer.Key("Y");
//     writer.String(RBottom.c_str());
//     writer.EndObject();
//     writer.StartObject();
//     writer.Key("X");
//     writer.String(RRight.c_str());
//     writer.Key("Y");
//     writer.String(RTop.c_str());
//     writer.EndObject();
//     writer.StartObject();
//     writer.Key("X");
//     writer.String(RLeft.c_str());
//     writer.Key("Y");
//     writer.String(RTop.c_str());
//     writer.EndObject();
//     writer.EndArray();
//     string json_ = strBuf.GetString();
//     Coordinate = string2wstring(json_);
// }

// void set_Rect(const std::string& Result_ID, std::wstring& Coordinate)
// {
//     MysqlManager sqlManager;
//     char query[1024];
//     std::string RLeft;
//     std::string RTop;
//     std::string RRight;
//     std::string RBottom;
//     sprintf_s(query, "select RLeft from InspectionResult where Result_ID=%s", Result_ID.c_str());
//     RLeft = sqlManager.query_singleResult(query);
//     sprintf_s(query, "select RTop from InspectionResult where Result_ID=%s", Result_ID.c_str());
//     RTop = sqlManager.query_singleResult(query);
//     sprintf_s(query, "select RRight from InspectionResult where Result_ID=%s", Result_ID.c_str());
//     RRight = sqlManager.query_singleResult(query);
//     sprintf_s(query, "select RBottom from InspectionResult where Result_ID=%s", Result_ID.c_str());
//     RBottom = sqlManager.query_singleResult(query);
//     rapidjson::StringBuffer strBuf;
//     rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
//     writer.StartArray();
//     writer.StartObject();
//     writer.Key("X");
//     writer.String(RLeft.c_str());
//     writer.Key("Y");
//     writer.String(RBottom.c_str());
//     writer.EndObject();
//     writer.StartObject();
//     writer.Key("X");
//     writer.String(RRight.c_str());
//     writer.Key("Y");
//     writer.String(RBottom.c_str());
//     writer.EndObject();
//     writer.StartObject();
//     writer.Key("X");
//     writer.String(RRight.c_str());
//     writer.Key("Y");
//     writer.String(RTop.c_str());
//     writer.EndObject();
//     writer.StartObject();
//     writer.Key("X");
//     writer.String(RLeft.c_str());
//     writer.Key("Y");
//     writer.String(RTop.c_str());
//     writer.EndObject();
//     writer.EndArray();
//     string json_ = strBuf.GetString();
//     Coordinate = string2wstring(json_);
// }
// void set_FilePath(const std::string& Device_Id, const std::string& Result_ID, std::wstring& WFilePath)
// {
//     MysqlManager sqlManager;
//     char query[1024];
//     int year, month, day, hour, minute, second, hms, pos;
//     sprintf(query, "select DeviceType from DeviceInfo where Device_Id=%s", Device_Id.c_str());
//     string DeviceType = sqlManager.query_singleResult(query);
//     string CarID = wstring2string(RobotID());
//     if(!strcmp(DeviceType.c_str(), "2")) {
//         sprintf(query, "select Infrared_Cap from InspectionResult where Result_ID=%s", Result_ID.c_str());
//         string Infrared_Cap = sqlManager.query_singleResult(query);
//         pos = Infrared_Cap.rfind("\\");
//         if(pos != Infrared_Cap.npos) {
//             string FilePath = Infrared_Cap.substr(pos + 1);
//             sscanf(FilePath.c_str(), "%d-%d-%d_%d_%d_%d", &year, &month, &day, &hour, &minute, &second);  //取需要的字符串
//             upload_FTP(Infrared_Cap, "INF", year, month, day, hour, minute, second);
//             sprintf(query, "%s/%04d/%02d/%02d/INF/%s_%02d%02d%02d.jpg", wstring2string(kstationid).c_str(), year, month, day, CarID.c_str(), hour, minute, second);
//             string Path = query;
//             WFilePath = string2wstring(Path);
//             SLOG_TRACE("%s：%s", "picpath", Path.c_str());
//         } else {
//             SLOG_WARN("%s", "no pic");
//         }
//     } else
//     //(!strcmp(DeviceType.c_str(), "1") || !strcmp(DeviceType.c_str(), "5"))
//     {
//         sprintf(query, "select IPC_PIC_Cap from InspectionResult where Result_ID=%s", Result_ID.c_str());
//         string IPC_PIC_Cap = sqlManager.query_singleResult(query);
//         pos = IPC_PIC_Cap.rfind("\\");
//         if(pos != IPC_PIC_Cap.npos) {
//             string FilePath = IPC_PIC_Cap.substr(pos + 1);
//             pos = FilePath.find("_");
//             pos = FilePath.find("_", pos + 1);
//             string ts = FilePath.substr(pos + 1);
//             sscanf(ts.c_str(), "%d_%d_%d_%d", &hms, &hour, &minute, &second);  //取需要的字符串
//             extract_YMD(hms, year, month, day);
//             upload_FTP(IPC_PIC_Cap, "CCD", year, month, day, hour, minute, second);
//             sprintf(query, "%s/%04d/%02d/%02d/CCD/%s_%02d%02d%02d.jpg", wstring2string(kstationid).c_str(), year, month, day, CarID.c_str(), hour, minute, second);
//             string Path = query;
//             WFilePath = string2wstring(Path);
//             SLOG_TRACE("%s：%s", "picpath", Path.c_str());
//         } else {
//             SLOG_WARN("%s", "no pic");
//         }
//     }
// }

// void set_TaskStat(std::wstring& TaskSta)
// {
//     std::string ret_Xml;
//     std::string post_Xml;
//     MyXml xmlManager;
//     std::string result;
//     sprintf(g_url, "%s%s", g_urlhead, "Other");
//     post_Xml = xmlManager.creat_Xml("GetTaskStatReq");
//     ret_Xml = CurlHttp::Request(g_url, post_Xml);
//     xmlManager.get_MsgType(ret_Xml.c_str());
//     result = xmlManager.get_oneResult("TaskStat");
//     if(!strcmp(result.c_str(), "0")) {
//         TaskSta = L"1601";
//     } else if(!strcmp(result.c_str(), "4")) {
//         TaskSta = L"1603";
//     } else {
//         TaskSta = L"1603";
//     }
// }

// void set_TaskStat(::CentralModule::ITaskState& State)
// {
//     std::string ret_Xml;
//     std::string post_Xml;
//     MyXml xmlManager;
//     std::string result;
//     sprintf(g_url, "%s%s", g_urlhead, "Other");
//     post_Xml = xmlManager.creat_Xml("GetTaskStatReq");
//     ret_Xml = CurlHttp::Request(g_url, post_Xml);
//     xmlManager.get_MsgType(ret_Xml.c_str());
//     result = xmlManager.get_oneResult("TaskStat");
//     // SLOG_TRACE("%s：%s", "set_TaskStat", result.c_str());
//     // cout << result << endl;
//     if(!strcmp(result.c_str(), "0")) {
//         State = ::CentralModule::ITaskState::Idle;
//     } else if(!strcmp(result.c_str(), "4")) {
//         State = ::CentralModule::ITaskState::Idle;
//     } else {
//         State = ::CentralModule::ITaskState::Running;
//     }
// }

// void set_IDateTime(const time_t& timestamp, ::CentralModule::IDateTime& Time)
// {
//     struct tm* localTime = localtime(&timestamp);
//     Time.Year = localTime->tm_year + 1900;
//     Time.Month = localTime->tm_mon + 1;
//     Time.Day = localTime->tm_mday;
//     Time.Hour = localTime->tm_hour;
//     Time.Minute = localTime->tm_min;
//     Time.Second = localTime->tm_sec;
// }

// void set_TimebyNow(::CentralModule::IDateTime& Time)
// {
//     time_t now = { 0 };
//     time(&now);
//     set_IDateTime(now, Time);
// }

// std::wstring cur_TaskID()
// {
//     char query[1024];
//     MysqlManager sqlManager;
//     sprintf_s(query, "select MAX(InspectionLog_ID) from InspectionLog");
//     string InspectionLog_ID = sqlManager.query_noLog_singleResult(query);
//     sprintf_s(query, "select Task_Rule_Id from InspectionLog where InspectionLog_ID=%s", InspectionLog_ID.c_str());
//     string Task_Rule_Id = sqlManager.query_noLog_singleResult(query);
//     return string2wstring(Task_Rule_Id);
// }

// std::wstring RobotID()
// {
//     static wstring WCar_Id;
//     if(!WCar_Id.size()) {
//         char query[1024];
//         MysqlManager sqlManager;
//         sprintf_s(query, "select Car_Id from CarInfo limit 1");
//         string Car_Id = sqlManager.query_singleResult(query);
//         WCar_Id = string2wstring(Car_Id);
//     }
//     return WCar_Id;
// }

// bool isNum(string str)
// {
//     stringstream sin(str);
//     double d;
//     char c;
//     if(!(sin >> d)) return false;
//     if(sin >> c) return false;
//     return true;
// }

// void set_stof(std::string& svalue, float& value)
// {
//     if(!strcmp(svalue.c_str(), "")) {
//         value = 0;
//     } else if(isNum(svalue)) {
//         value = stof(svalue);
//     } else if(!strcmp(svalue.c_str(), "分")) {
//         value = 1;
//     } else if(!strcmp(svalue.c_str(), "合")) {
//         value = 2;
//     } else if(!strcmp(svalue.c_str(), "黄色")) {
//         value = 3;
//     } else if(!strcmp(svalue.c_str(), "绿色")) {
//         value = 5;
//     } else {
//         value = 0;
//     }
// }

// int string2int(const std::string& str)
// {
//     if(!strcmp(str.c_str(), "")) {
//         return 0;
//     } else if(isNum(str)) {
//         return stoi(str);
//     } else {
//         return 0;
//     }
// }

// void set_IEventRl(int type, IEventRlSeq& EventRlSeq)
// {
//     static int sysAlarmID = 1;
//     IEventRlPtr EventRlPtr = new IEventRl;
//     EventRlPtr->ID = sysAlarmID;
//     EventRlPtr->CheckState = L"0";
//     EventRlPtr->Level = L"2103";
//     EventRlPtr->Type = L"2025";
//     set_TimebyNow(EventRlPtr->Time);
//     EventRlPtr->RobotID = RobotID();
//     EventRlPtr->Rect = L"[{\"X\":81,\"Y\":5}]";
//     if(type == 0) {
//         EventRlPtr->Content = L"激光防撞报警";
//     } else if(type == 1) {
//         EventRlPtr->Content = L"物理碰撞报警";
//     } else if(type == 2) {
//         EventRlPtr->Content = L"跌落报警";
//     } else {
//         EventRlPtr->Content = L"null";
//     }
//     EventRlSeq.emplace_back(EventRlPtr);
//     sysAlarmID++;
// }

// void upload_FTP(const std::string& pic_path, const char* type, int year, int month, int day, int hour, int minute, int second)
// {
//     char url[128] = { 0 };

//     sprintf(url, "ftp://%s:%s/Patrol/%04d/%02d/%02d/%s/%s_%02d%02d%02d.jpg", g_FTP_IP, g_FTP_Port, year, month, day, type, wstring2string(RobotID()).c_str(), hour, minute, second);
//     CurlHttp::FtpUpload(url, pic_path.c_str(), g_FTP_UserName, g_FTP_PassWord, 10);

//     // sprintf(url, "ftp://192.168.121.44:21/%s_%02d%02d%02d.jpg", "21", hour, minute, second);
//     //  CurlHttp::FtpUpload(url, pic_path.c_str(), "zjm", "123456", 10);
// }
// #pragma comment(lib, "ws2_32.lib")
// void UDP2manageserver()
// {
//     WSADATA wsa_data;
//     SOCKET serv_sock;
//     char message[128];
//     int strlen;
//     int clnt_addr_size;
//     SOCKADDR_IN serv_addr, clnt_addr;
//     if(WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
//     }
//     serv_sock = socket(AF_INET, SOCK_DGRAM, 0);
//     if(serv_sock == INVALID_SOCKET) {
//     }
//     memset(&serv_addr, 0, sizeof(serv_addr));
//     serv_addr.sin_family = AF_INET;
//     serv_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
//     serv_addr.sin_port = htons(12381);
//     if(::bind(serv_sock, (SOCKADDR*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) {
//     }
//     while(true) {
//         clnt_addr_size = sizeof(clnt_addr);
//         strlen = recvfrom(serv_sock, message, 128, 0, (SOCKADDR*)&clnt_addr, &clnt_addr_size);
//         printf("message from client:%s\n", message);
//         sendto(serv_sock, message, strlen, 0, (SOCKADDR*)&clnt_addr, sizeof(clnt_addr));
//     }
//     closesocket(serv_sock);
//     WSACleanup();
// }

// #if _MSC_VER
// #define snprintf _snprintf
// #endif

// #define STACK_INFO_LEN 1024

// void ShowTraceStack(char* szBriefInfo)
// {
//     static const int MAX_STACK_FRAMES = 12;
//     void* pStack[MAX_STACK_FRAMES];
//     static char szStackInfo[STACK_INFO_LEN * MAX_STACK_FRAMES];
//     static char szFrameInfo[STACK_INFO_LEN];

//     HANDLE process = GetCurrentProcess();
//     SymInitialize(process, NULL, TRUE);
//     WORD frames = CaptureStackBackTrace(0, MAX_STACK_FRAMES, pStack, NULL);
//     // strcpy(szStackInfo, szBriefInfo == NULL ? "stack traceback:\n" : szBriefInfo);

//     // for(WORD i = 1; i < frames; ++i) {
//     //    DWORD64 address = (DWORD64)(pStack[i]);

//     //    DWORD64 displacementSym = 0;
//     //    char buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)];
//     //    PSYMBOL_INFO pSymbol = (PSYMBOL_INFO)buffer;
//     //    pSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
//     //    pSymbol->MaxNameLen = MAX_SYM_NAME;

//     //    DWORD displacementLine = 0;
//     //    IMAGEHLP_LINE64 line;
//     //    line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

//     //    if(SymFromAddr(process, address, &displacementSym, pSymbol) && SymGetLineFromAddr64(process, address, &displacementLine, &line)) {
//     //        const char ch = '\\';
//     //        char* pos = strrchr(line.FileName, ch);
//     //        snprintf(szFrameInfo, sizeof(szFrameInfo), "\t%s() at %s:%d(0x%x)\n", pSymbol->Name, pos + 1, line.LineNumber, pSymbol->Address);
//     //    } else {
//     //        //snprintf(szFrameInfo, sizeof(szFrameInfo), "\terror: %d\n", GetLastError());
//     //    }
//     //    strcat(szStackInfo, szFrameInfo);
//     //}
//     for(WORD i = 1; i < frames; ++i) {
//         DWORD64 address = (DWORD64)(pStack[i]);

//         DWORD64 displacementSym = 0;
//         char buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)];
//         PSYMBOL_INFO pSymbol = (PSYMBOL_INFO)buffer;
//         pSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
//         pSymbol->MaxNameLen = MAX_SYM_NAME;

//         DWORD displacementLine = 0;
//         IMAGEHLP_LINE64 line;
//         line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

//         if(SymFromAddr(process, address, &displacementSym, pSymbol) && SymGetLineFromAddr64(process, address, &displacementLine, &line)) {
//             const char ch = '\\';
//             char* pos = strrchr(line.FileName, ch);
//             snprintf(szFrameInfo, sizeof(szFrameInfo), "%s()->", pSymbol->Name);
//             strcat(szStackInfo, szFrameInfo);
//         }
//     }
//     SLOG_WARN("%s", szStackInfo);
//     // printf("%s", szStackInfo);  // 输出到控制台，也可以打印到日志文件中
// }
