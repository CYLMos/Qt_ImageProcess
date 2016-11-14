#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv_modules.hpp"
#include "opencv2/objdetect/objdetect_c.h"
#include "opencv2/objdetect.hpp"
#include "cv.h"
#include "highgui.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pb_ChoseImage_clicked();

    void on_slider_ReSize_valueChanged(int value);

    void on_pb_ChoseDecodeImage_clicked();

    void on_pb_Save_clicked();

private:
    Ui::MainWindow *ui;
    cv::Mat mat_Image;

    cv::Mat adjustSize(cv::Mat mat);
    cv::Mat adjustSize(cv::Mat mat, double value);
    cv::Mat faceDetected(cv:: Mat mat);
    /*int decode(cv::Mat image,int peak,int zero);
    int power(int a,int n){
        int to=1;
        for(int i=0;i<n;i++)
        {
            to*=a;
        }
        return to;

    }*/
};

#endif // MAINWINDOW_H
