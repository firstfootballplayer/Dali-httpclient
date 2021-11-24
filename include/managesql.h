#pragma once
#include <vector>
#include <mysql/mysql.h>
#include <string>
#include <iostream>
#include "libmevent/base/Logging.h"
//#define MYSQL_GONE_AWAY 2006

class MysqlManager
{
public:
    typedef std::vector<std::string> multiRes;
    MysqlManager(const char* mysql_db_ = "robot", int mysql_port_ = 3310, const char* mysql_ip_ = "127.0.0.1", const char* mysql_pwd_ = "123456", const char* mysql_user_ = "root");
    /* 无返回结果查询类型 */
    int query_noResult(const char* sql);
    /* 单个结果查询类型 */
    const char* query_singleResult(const char* sql);
    /* 多个结果查询类型 */
    multiRes query_multiResult(const char* sql);

    const char* query_noLog_singleResult(const char* sql);

private:
    /* 找到查询目标名称 */
    std::string find_query_target();
    /* 清除查询结果 */
    void freeRes();
    /* 重连数据库 */
    void reconn_Mysql();
    /* 测试mysql服务器是否存活 */
    int ping();
    /* 关闭mysql 服务器 */
    int shutDown();
    /* 主要功能:重新启动mysql 服务器 */
    int reboot();
    /* 主要功能:开始事务 */
    int startTransaction();
    /* 主要功能:提交事务 */
    int commit();
    /* 主要功能:回滚事务 */
    int rollback();
    /* 建立新数据库 */
    int createDB(const char* name);
    /* 删除制定的数据库*/
    int dropDB(const char* name);
    /* 关闭数据库 */
    void close();

private:
    MYSQL mysqlConn_;
    std::string mysql_ip_;
    std::string mysql_pwd_;
    std::string mysql_user_;
    std::string mysql_db_;
    std::string query_str_;
    int mysql_port_;
    MYSQL_RES* res_ = nullptr;
    MYSQL_ROW row_;
    std::string query;
};
