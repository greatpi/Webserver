#ifndef _CONNECTION_POOL_
#define _CONNECTION_POOL_

#include "../lock/locker.h"
#include "../log/log.h"
#include <error.h>
#include <iostream>
#include <list>
#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>
#include <string>

class connection_pool {
public:
    MYSQL* GetConnection(); // 获取数据库连接
    bool ReleaseConnection(MYSQL* conn); // 释放连接
    int GetFreeConn(); // 获取连接
    void DestroyPool(); // 销毁所有连接

    // 单例模式
    static connection_pool* GetInstance();

    void init(std::string url, std::string User, std::string PassWord, std::string DataBaseName, int Port, int MaxConn, int close_log);

private:
    connection_pool();
    ~connection_pool();

    int m_MaxConn; // 最大连接数
    int m_CurConn; // 当前已使用的连接数
    int m_FreeConn; // 当前空闲的连接数
    locker lock;
    std::list<MYSQL*> connList; // 连接池
    sem reserve;

public:
    std::string m_url; // 主机地址
    std::string m_Port; // 数据库端口号
    std::string m_User; // 登录数据库用户名
    std::string m_PassWord; // 登录数据库密码
    std::string m_DatabaseName; // 使用数据库名
    int m_close_log; // 日志开关
};

class connectionRAII {
public:
    connectionRAII(MYSQL* SQL, connection_pool* connPool);
    ~connectionRAII();

private:
    MYSQL* conRAII;
    connection_pool* poolRAII;
};

#endif