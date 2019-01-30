#include "mainwindow.h"
#include <QApplication>

#include <thread>
#include <memory>
#include <iostream>
#include <QDateTime>
#include "comlogmanager.h"

void addLog(std::shared_ptr<ComLogManager> pManager, int nThreadNo)
{
    for (int i = 0; i < 100000; ++i)
    {
        pManager->addLog(QString("addLog %1").arg(i), QString::number(nThreadNo), 1);
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::shared_ptr<ComLogManager> pManager(new ComLogManager);
    pManager->init();

    std::cout<<"main begin "<<QDateTime::currentDateTime().toString("yyyy-MM-dd h-mm-ss").toStdString()<<std::endl;

    std::thread pThread1(addLog, pManager, 1);
    std::thread pThread2(addLog, pManager, 2);
    std::thread pThread3(addLog, pManager, 3);
    std::thread pThread4(addLog, pManager, 4);
    std::thread pThread5(addLog, pManager, 5);
    std::thread pThread6(addLog, pManager, 6);
    std::thread pThread7(addLog, pManager, 7);
    std::thread pThread8(addLog, pManager, 8);
    std::thread pThread9(addLog, pManager, 9);
    std::thread pThread10(addLog, pManager, 10);

    pThread1.join();
    pThread2.join();
    pThread3.join();
    pThread4.join();
    pThread5.join();
    pThread6.join();
    pThread7.join();
    pThread8.join();
    pThread9.join();
    pThread10.join();

    pManager->quit();
    std::cout<<"main finish "<<QDateTime::currentDateTime().toString("yyyy-MM-dd h-mm-ss").toStdString()<<std::endl;
    return 0;
    return a.exec();
}
