#ifndef NDBPOOL_H
#define NDBPOOL_H
/**
 * 作者: daodaoliang
 * 时间: 2016年8月5日
 * 版本: 1.0.7.0
 * 邮箱: daodaoliang@yeah.net
 */
#include "ndbpool_global.h"
#include "ndbpool_p.h"
#include <QTimer>
#include <QDateTime>

struct connectActive{
    qint64 lastActiveTime;
    QString poolName;
    bool longConnect;
};

/**
 * @brief The NDBPool class
 * 数据库连接池库的接口文档
 */

class NDBPOOLSHARED_EXPORT NDBPool: public QObject
{
    Q_OBJECT
public:
    /**
     * @brief release 释放所有链接
     * @return void
     */
    static void release();

    /**
     * @brief getNewConnection getNewConnection 获取一个可用的连接链接
     * @param paramHostName 主机名
     * @param paramDatabaseName 数据库名字
     * @param paramUserName 数据库名字
     * @param paramPassword 数据库密码
     * @param paramPort 数据库端口
     * @param longConnect 是否为长连接
     * @param longConnnectName 长连接名字
     * @return
     */
    static QSqlDatabase getNewConnection(QString paramHostName,
                                         QString paramDatabaseName,
                                         QString paramUserName,
                                         QString paramPassword,
                                         int paramPort,
                                         bool longConnect=false,
                                         QString longConnnectName="");

    /**
     * @brief closeConnection 释放本地连接
     * @param connection
     */
    static void closeConnection(const QSqlDatabase &connection);

public:
    /**
     * @brief NDBPool 构造函数
     * @param paramIsDebug 是否是调试模式
     */
    NDBPool(bool paramIsDebug = true,QObject * parent = 0);

    ~NDBPool();

private slots:

    /**
     * @brief slots_forceBreak 强制断开连接
     */
    void slots_forceBreak();

private:
    /**
     * @brief instance 单例实例
     * @param paramIsDebug 是否是调试模式
     * @return
     */
    static NDBPool& instance(bool paramIsDebug = true);

private:

    /**
     * @brief checkForceBreakInterval 强制断开连接的检查频率
     */
    short checkForceBreakInterval;

    /**
     * @brief connectionLastActiveTimeMap 连接的最近状态映射
     */
    static QMap<QString, connectActive> connectionLastActiveTimeMap;

    /**
     * @brief poolMap 数据库连接池名字和连接池的映射
     */
    static QMap<QString, NDBPool_p *> poolMap;

    /**
     * @brief mLock
     */
    static QMutex mLock;

    /**
     * @brief forceBreakTime 强制断开连接的判定时间差
     */
    int forceBreakTime;

    /**
     * @brief isDebug 是否为调试模式
     */
    static bool isDebug;

    /**
     * @brief activeTimer 维持活跃连接
     */
    QTimer activeTimer;

    /**
     * @brief checkDeadTimer 检测死链接
     */
    QTimer checkDeadTimer;

    /**
     * @brief forceBreakTimer 检查超时链接
     */
    QTimer forceBreakTimer;
};

#endif // NDBPOOL_H
