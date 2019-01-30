#include "comlogqueue.h"

ComLogQueue::ComLogQueue(int nIndex)
    : m_nIndex(nIndex)
{

}

ComLogQueue::~ComLogQueue()
{

}

void ComLogQueue::addLog(const QString &strLog)
{
    m_logCache.append(strLog);
}

void ComLogQueue::clear()
{
    m_logCache.clear();
}

bool ComLogQueue::isInPrint()
{
    return bIsInPrint;
}

void ComLogQueue::setIsInPrint(bool bInPrint)
{
    bIsInPrint = bInPrint;
}

int ComLogQueue::getLogCount()
{
    return m_logCache.size();
}

int ComLogQueue::getQueueIndex()
{
    return m_nIndex;
}

QString ComLogQueue::getLog(int nIndex)
{
    return m_logCache[nIndex];
}
