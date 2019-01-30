#ifndef LOGER_H
#define LOGER_H

#include <memory>
#include <QString>
#include <QThread>
#include <QMutex>
#include <QVector>
#include <QStringList>
#include <QWaitCondition>

class ComLogQueue;
class ComLogPrinter;
class ComLogManager
{
public:
    ComLogManager();
    ~ComLogManager();
    void init();
    void addLog(const QString &strLog, const QString &strKey, int nPrority);
    void quit();

protected:
    bool innerAddLog(const QString &strLog, const QString &strKey, int nPriority);
    void printLog();
    void printQueue(std::shared_ptr<ComLogQueue> pQueue);
    void switchQueue();
    bool checkNeedPrint();
    std::shared_ptr<ComLogQueue> createQueue();

private:
    QMutex m_mutex;
    int m_nQueueIndex = 0;
    int m_nMaxSize = 0;
    int m_nMinPriority = 0;
    std::shared_ptr<ComLogQueue> m_pAddQueue;
    QList<std::shared_ptr<ComLogQueue>> m_queueList;
    ComLogPrinter *m_printer;
    QStringList m_whiteList;
};


#endif // LOGER_H
