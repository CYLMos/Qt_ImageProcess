#ifndef THREAD2_H
#define THREAD2_H

#include <QThread>
#include <Decoder.h>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv_modules.hpp"
#include "opencv2/objdetect/objdetect_c.h"
#include "opencv2/objdetect.hpp"
#include "cv.h"
#include "highgui.h"

class Thread2 : public QThread
{
    Q_OBJECT
public:
    Thread2(cv::Mat &mat, int &peak, int &zero, int &result, QObject *parent);
    Thread2(QObject *parent);
    ~Thread2();

    cv::Mat getMat();

signals:
    void startProcess(int result);

protected:
    void run();

private:
    Decoder* decoder;
    cv::Mat mat;
    int result;
    int peak;
    int zero;
    QObject *parent;
};

#endif // THREAD2_H
