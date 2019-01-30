#ifndef COMLOGQUEUE_H
#define COMLOGQUEUE_H

#include <QString>
#include <QVector>

class ComLogQueue
{
public:
    ComLogQueue(int nIndex);
    ~ComLogQueue();

    void addLog(const QString &strLog);
    void clear();
    bool isInPrint();
    void setIsInPrint(bool bInPrint);
    int getLogCount();
    int getQueueIndex();
    QString getLog(int nIndex);

protected:
    int m_nIndex = 0;
    QVector<QString> m_logCache;
    volatile bool bIsInPrint = false;
};

#endif // COMLOGQUEUE_H
