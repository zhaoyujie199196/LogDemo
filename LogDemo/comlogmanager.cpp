#include "comlogmanager.h"
#include <QMutexLocker>
#include <QMetaType>
#include <iostream>
#include <QDateTime>
#include "comlogprinter.h"
#include "comlogqueue.h"

static const QString c_strInnerLog = "%1 ## %2 ## %3";
static const int c_nLogQueueCacheCount = 100;

ComLogManager::ComLogManager()
{

}

ComLogManager::~ComLogManager()
{

}

void ComLogManager::init()
{
    std::shared_ptr<ComLogQueue> queue1 = createQueue();
    std::shared_ptr<ComLogQueue> queue2 = createQueue();
    m_queueList.append(queue1);
    m_queueList.append(queue2);
    m_pAddQueue = queue1;
    m_nMaxSize = c_nLogQueueCacheCount;
    m_printer = new ComLogPrinter;
}

void ComLogManager::addLog(const QString &strLog, const QString &strKey, int nPriority)
{
    QMutexLocker locker(&m_mutex);
    bool bAddLog = innerAddLog(strLog, strKey, nPriority);
    if (!bAddLog)
        return;
    if (checkNeedPrint())
        printLog();
}

void ComLogManager::quit()
{
    while (true)
    {
        bool bQuitFlag = false;
        for (std::shared_ptr<ComLogQueue> pQueue : m_queueList)
        {
            if (pQueue->getLogCount() != 0)
            {
                bQuitFlag = true;
                QMutexLocker locker(&(m_printer->m_printMutex));
                printQueue(pQueue);
                m_printer->m_printCondition.wait(&(m_printer->m_printMutex));
            }
        }
        if (!bQuitFlag)
            break;
    }
    QThread *pThread = m_printer->m_thread;
    m_printer->quit();
    delete m_printer;
//    delete pThread;
}

bool ComLogManager::innerAddLog(const QString &strLog, const QString &strKey, int nPriority)
{
    if (nPriority < m_nMinPriority)
        return false;
//    if (!m_whiteList.contains(strKey))
//        return false;
   // QMutexLocker locker(&m_mutex);
    QString strTime = QDateTime::currentDateTime().toString("yyyy-MM-dd:h-mm-ss-zzz");
    QString strInnerLog = c_strInnerLog.arg(strKey).arg(strTime).arg(strLog);
    m_pAddQueue->addLog(strInnerLog);
    return true;
}

bool ComLogManager::checkNeedPrint()
{
    //QMutexLocker locker(&m_mutex);
    int nSize = m_pAddQueue->getLogCount();
    return nSize >= m_nMaxSize;
}

std::shared_ptr<ComLogQueue> ComLogManager::createQueue()
{
    m_nQueueIndex++;
    return std::shared_ptr<ComLogQueue>(new ComLogQueue(m_nQueueIndex));
}

void ComLogManager::printLog()
{
    std::shared_ptr<ComLogQueue> pPrintQueue = m_pAddQueue;
    switchQueue();
    printQueue(pPrintQueue);
}

void ComLogManager::printQueue(std::shared_ptr<ComLogQueue> pQueue)
{
    m_printer->printLog(pQueue);
}

void ComLogManager::switchQueue()
{
    //QMutexLocker locker(&m_mutex);
    int nIndex = m_queueList.indexOf(m_pAddQueue);
    int nSize = m_queueList.size();
    int nNextIndex;
    int nInsertIndex;
    if (nIndex == nSize - 1)
    {
        nNextIndex = 0;
        nInsertIndex = nSize;
    }
    else
    {
        nNextIndex = nIndex + 1;
        nInsertIndex = nNextIndex;
    }

    //std::cout<<"current Index : "<<nIndex<<"  nextIndex : "<<nNextIndex<<"  insertIndex : "<<nInsertIndex<<std::endl;

    if (m_queueList[nNextIndex]->isInPrint())
    {
        m_pAddQueue = createQueue();
        m_queueList.insert(nInsertIndex, m_pAddQueue);
    }
    else
    {
        m_pAddQueue = m_queueList.at(nNextIndex);
    }
   // std::cout<<"cur add queue index : "<<m_pAddQueue->getQueueIndex()<<std::endl;
}
