#include "Thread1.h"
#include <QString>
#include <QMutex>
#include <QtCore>

Thread1::Thread1(cv::Mat &mat, int &value, QObject *parent) :
    QThread(parent)
{
    this->encoder = new Encoder;
    this->mat = mat;
    this->value = value;
    this->parent = parent;
}

Thread1::Thread1(QObject *parent) :
    QThread(parent)
{
    this->parent = parent;
}

Thread1::~Thread1(){
    delete this->encoder;
    delete this->parent;
    this->mat.release();
}

void Thread1::run(){
    int peak,zero,count;
    emit startProcess(-1,-1);
    QMutex mutex;
    mutex.lock();

    encoder->encode(this->mat,peak,zero,count,this->value);

    cv::cvtColor(this->mat,this->mat,CV_RGB2BGR);
    cv::imwrite("Test.bmp",this->mat);

    mutex.unlock();

    emit startProcess(peak, zero);

}
