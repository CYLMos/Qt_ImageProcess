#include "Thread2.h"
#include <QString>
#include <QMutex>
#include <QtCore>


Thread2::Thread2(cv::Mat &mat, int &peak, int &zero, int &result, QObject *parent) : QThread(parent)
{
    this->decoder = new Decoder;
    this->mat = mat;
    this->peak = peak;
    this->zero = zero;
    this->result = result;
    this->parent = parent;
}

Thread2::Thread2(QObject *parent) : QThread(parent)
{
    this->parent = parent;
}

Thread2::~Thread2(){
    delete this->decoder;
    delete this->parent;
    this->mat.release();
}

cv::Mat Thread2::getMat(){
    return this->mat;
}

void Thread2::run(){
    emit startProcess(-1);
    QMutex mutex;
    mutex.lock();

    this->result = decoder->decode_and_recover(this->mat,this->peak,this->zero);

    mutex.unlock();

    emit startProcess(this->result);
}
