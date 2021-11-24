#include "managesql.h"
#include <iostream>
#include "Utilities.h"
using namespace std;
using namespace libmevent;
int MYSQL_GONE_AWAY = 2006;
int MYSQL_Unknown_column = 1054;
MysqlManager::MysqlManager(const char* mysql_db, int mysql_port, const char* mysql_ip, const char* mysql_pwd, const char* mysql_user) : mysql_ip_(mysql_ip), mysql_pwd_(mysql_pwd), mysql_user_(mysql_user), mysql_db_(mysql_db), mysql_port_(mysql_port)
{
    mysql_init(&mysqlConn_);
    if(!mysql_real_connect(&mysqlConn_, mysql_ip_.c_str(), mysql_user_.c_str(), mysql_pwd_.c_str(), mysql_db_.c_str(), mysql_port_, NULL, 0)) {
        ::sleep(2);
        if(!mysql_real_connect(&mysqlConn_, mysql_ip_.c_str(), mysql_user_.c_str(), mysql_pwd_.c_str(), mysql_db_.c_str(), mysql_port_, NULL, 0)) {
            LOG_WARN << "mysql conn error: " << mysql_error(&mysqlConn_);
        } else {
            char value = 1;
            mysql_options(&mysqlConn_, MYSQL_OPT_RECONNECT, static_cast<char*>(&value));
            LOG_WARN << "MYSQL_OPT_RECONNECT: " << mysql_error(&mysqlConn_);
        }
    }
    mysql_query(&mysqlConn_, "set NAMES 'gbk'");  //显示中文，没有gbk中文乱码，once
}

/* 无返回结果查询 */
int MysqlManager::query_noResult(const char* sql)
{
    query = sql;
again:
    int ret = mysql_real_query(&mysqlConn_, query.c_str(), strlen(query.c_str()));
    if(0 != ret) {
        int errcode = mysql_errno(&mysqlConn_);
        if(MYSQL_GONE_AWAY == errcode) {
            // LOG_WARN("查询报警:", mysql_error(&mysqlConn_));
            reconn_Mysql();
            goto again;
        } else {
            LOG_WARN << "查询报警:" << mysql_error(&mysqlConn_);
            // ShowTraceStack();
        }
    }
    return (int)mysql_affected_rows(&mysqlConn_);
}

/* 单个结果查询 */
const char* MysqlManager::query_singleResult(const char* sql)
{
    query = sql;
    std::string select_target = find_query_target();
again:
    int ret = mysql_real_query(&mysqlConn_, query.c_str(), strlen(query.c_str()));
    if(0 != ret) {
        int errcode = mysql_errno(&mysqlConn_);
        if(MYSQL_Unknown_column == errcode) {
            LOG_WARN << select_target.c_str() << mysql_error(&mysqlConn_);
            // ShowTraceStack();
            return "";
        }
        if(MYSQL_GONE_AWAY == errcode) {
            // LOG_WARN("查询报警:", "mysql gone away");
            reconn_Mysql();
            goto again;
        } else {
            LOG_WARN << select_target.c_str() << mysql_error(&mysqlConn_);
            // ShowTraceStack();
        }
    }
    res_ = mysql_store_result(&mysqlConn_);  //存储查询结果
    if(nullptr == res_) {
        return "";
    }
    if((row_ = mysql_fetch_row(res_)) == nullptr) {
        freeRes();
        return "";
    }
    freeRes();
    LOG_INFO << select_target.c_str() << row_[0];
    return row_[0];
}

/* 单个结果查询 */
const char* MysqlManager::query_noLog_singleResult(const char* sql)
{
    query = sql;
    std::string select_target = find_query_target();
again:
    int ret = mysql_real_query(&mysqlConn_, query.c_str(), strlen(query.c_str()));
    if(0 != ret) {
        int errcode = mysql_errno(&mysqlConn_);
        if(MYSQL_Unknown_column == errcode) {
            LOG_WARN << select_target.c_str() << mysql_error(&mysqlConn_);
            // ShowTraceStack();
            return "";
        }
        if(MYSQL_GONE_AWAY == errcode) {
            // LOG_WARN("查询报警:", "mysql gone away");
            reconn_Mysql();
            goto again;
        } else {
            LOG_WARN << select_target.c_str() << mysql_error(&mysqlConn_);
            // ShowTraceStack();
        }
    }
    res_ = mysql_store_result(&mysqlConn_);  //存储查询结果
    if(nullptr == res_) {
        return "";
    }
    if((row_ = mysql_fetch_row(res_)) == nullptr) {
        freeRes();
        return "";
    }
    cout << row_[0] << endl;
    freeRes();
    return row_[0];
}

/* 多个结果查询 */
MysqlManager::multiRes MysqlManager::query_multiResult(const char* sql)
{
    multiRes rets;
    query = sql;
again:
    int ret = mysql_real_query(&mysqlConn_, query.c_str(), strlen(query.c_str()));
    if(0 != ret) {
        int errcode = mysql_errno(&mysqlConn_);
        if(MYSQL_Unknown_column == errcode) {
            LOG_WARN << "mysql error" << mysql_error(&mysqlConn_);
            // return "";
        }
        if(MYSQL_GONE_AWAY == errcode) {
            // LOG_WARN("查询报警:", "mysql gone away");
            reconn_Mysql();
            goto again;
        } else {
            LOG_WARN << "mysql error" << mysql_error(&mysqlConn_);
        }
    }
    res_ = mysql_store_result(&mysqlConn_);  //存储查询结果
    int rows = mysql_num_rows(res_);         //行
    int fields = mysql_num_fields(res_);     //列
    while((row_ = mysql_fetch_row(res_))) {  //从查询结果提取一行
        for(int i = 0; i < fields; i++) {    //打印每列元素
            // std::cout << row_[i] << std::endl;
            rets.emplace_back(std::string(row_[i]));
        }
    }
    freeRes();
    std::string select_target = find_query_target();
    LOG_INFO << select_target.c_str();
    return rets;
}
/* 找到查询的目标名字 */
std::string MysqlManager::find_query_target()
{
    int po1 = query.find(' ', 0);
    int po2 = query.find(' ', po1 + 1);
    return query.substr(po1 + 1, (po2 - po1 - 1));
}

/* 查询结束释放 */
void MysqlManager::freeRes()
{
    if(res_ != nullptr) {
        mysql_free_result(res_);
        res_ = nullptr;
    }
}

/* 关闭数据库 */
void MysqlManager::close()
{
    if(&mysqlConn_ != nullptr) {
        mysql_close(&mysqlConn_);
        //&mysqlConn_ = nullptr;
    }
}

/* 测试mysql服务器是否存活 */
int MysqlManager::ping()
{
    if(mysql_ping(&mysqlConn_) == 0)
        return 0;
    else
        return -1;
}

/* 关闭mysql 服务器 */
int MysqlManager::shutDown()
{
    if(mysql_shutdown(&mysqlConn_, SHUTDOWN_DEFAULT) == 0)
        return 0;
    else
        return -1;
}

/* 主要功能:重新启动mysql 服务器 */
int MysqlManager::reboot()
{
    if(!mysql_reload(&mysqlConn_))
        return 0;
    else
        return -1;
}

/*
 * 说明:事务支持InnoDB or BDB表类型
 */
/* 主要功能:开始事务 */
int MysqlManager::startTransaction()
{
    if(!mysql_real_query(&mysqlConn_, "START TRANSACTION", (unsigned long)strlen("START TRANSACTION")))
        return 0;
    else  //执行查询失败
        return -1;
}

/* 主要功能:提交事务 */
int MysqlManager::commit()
{
    if(!mysql_real_query(&mysqlConn_, "COMMIT", (unsigned long)strlen("COMMIT")))
        return 0;
    else  //执行查询失败
        return -1;
}

/* 主要功能:回滚事务 */
int MysqlManager::rollback()
{
    if(!mysql_real_query(&mysqlConn_, "ROLLBACK", (unsigned long)strlen("ROLLBACK")))
        return 0;
    else
        //执行查询失败
        return -1;
}

/* 建立新数据库 */
int MysqlManager::createDB(const char* name)
{
    char temp[1024];
    sprintf(temp, "CREATE DATABASE %s", name);
    if(!mysql_real_query(&mysqlConn_, temp, strlen(temp)))
        return 0;
    else  //执行查询失败
        return -1;
}

/* 删除制定的数据库*/
int MysqlManager::dropDB(const char* name)
{
    char temp[1024];
    sprintf(temp, "DROP DATABASE %s", name);
    if(!mysql_real_query(&mysqlConn_, temp, strlen(temp)))
        return 0;
    else  //执行查询失败
        return -1;
}

/* 重连数据库 */
void MysqlManager::reconn_Mysql()
{
    mysql_real_connect(&mysqlConn_, mysql_ip_.c_str(), mysql_user_.c_str(), mysql_pwd_.c_str(), mysql_db_.c_str(), mysql_port_, NULL, 0);
    mysql_query(&mysqlConn_, "set NAMES 'gbk'");  //显示中文，没有gbk中文乱码,掉线后需要重新设置
}

// std::string find_first_str(const char *pstr)
//{
//	int len = 0;
//	int n0 = 0;
//	int n1 = 0;
//	int arr = 0;
//	const char *p0 = pstr;
//	const char *p1 = nullptr;
//	while (*p0 != '\0') {
//		if (*p0 == ' ') {
//			arr++;
//			if (1 == arr) {
//				p1 = p0;
//			}
//			if (2 == arr) {
//				char dest[100];
//				len = n0 - n1;
//				memcpy_s(dest, sizeof(dest), p1, len);
//				dest[len] = '\0';
//				std::string first_str = dest;
//				return first_str;
//			}
//			n0++;
//			p0++;
//		}
//		if (0 == arr) {
//			n1++;
//		}
//		n0++;
//		p0++;
//	}
//	return "";
//}
