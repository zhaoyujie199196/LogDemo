#ifndef COMLOGPRINTER_H
#define COMLOGPRINTER_H

#include <QObject>
#include <QMutex>
#include <QThread>
#include <memory>
#include <QWaitCondition>

class ComLogQueue;
class ComLogPrinter : public QObject
{
    Q_OBJECT
public:
    ComLogPrinter();
    ~ComLogPrinter();
    void printLog(std::shared_ptr<ComLogQueue> pQueue);
    void quit();

signals:
    void sigPrint(std::shared_ptr<ComLogQueue> pQueue);

protected slots:
    void onPrint(std::shared_ptr<ComLogQueue> pQueue);

public:
    QMutex m_printMutex;
    QWaitCondition m_printCondition;
    QThread *m_thread;
};

#endif // COMLOGPRINTER_H
