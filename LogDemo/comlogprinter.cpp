#include "comlogprinter.h"
#include "iostream"
#include "comlogqueue.h"

ComLogPrinter::ComLogPrinter()
{
    m_thread = new QThread;
    qRegisterMetaType<std::shared_ptr<ComLogQueue>>("std::shared_ptr<ComLogQueue>");
    connect(this, &ComLogPrinter::sigPrint, this, &ComLogPrinter::onPrint);
    this->moveToThread(m_thread);
    m_thread->start();
}

ComLogPrinter::~ComLogPrinter()
{
    std::cout<<"ComLogPrinter is destoryed"<<std::endl;
}

void ComLogPrinter::printLog(std::shared_ptr<ComLogQueue> pQueue)
{
    pQueue->setIsInPrint(true);
    emit sigPrint(pQueue);
}

void ComLogPrinter::quit()
{
    m_thread->exit(0);
    m_thread->wait();
    delete m_thread;
}

#include <QFile>
void ComLogPrinter::onPrint(std::shared_ptr<ComLogQueue> pQueue)
{
    QFile file("./DemoLogFile");
    file.open(QIODevice::Append);
    int nQueueIndex = pQueue->getQueueIndex();
    for (int i = 0, nSize = pQueue->getLogCount(); i < nSize; ++i)
    {
        QString strLog = QString("queue %1  ").arg(nQueueIndex) + pQueue->getLog(i);
        //std::cout<<strLog.toStdString()<<std::endl;
        QByteArray arr;
        arr.append(strLog).append("\r\n");
        file.write(arr);
    }
    file.close();
    pQueue->clear();
    pQueue->setIsInPrint(false);
    m_printCondition.wakeAll();
}
