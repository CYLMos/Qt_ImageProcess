#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <Encoder.h>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv_modules.hpp"
#include "opencv2/objdetect/objdetect_c.h"
#include "opencv2/objdetect.hpp"
#include "cv.h"
#include "highgui.h"

class Thread1 : public QThread
{
    Q_OBJECT
public:
    Thread1(cv::Mat &mat, int &value, QObject *parent);
    Thread1(QObject *parent);
    ~Thread1();

signals:
    void startProcess(int peak, int zero);

protected:
    void run();

private:
    QObject *parent;
    Encoder *encoder;
    cv::Mat mat;
    int value;
};

#endif // THREAD_H
