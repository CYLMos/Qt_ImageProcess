#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "Thread1.h"
#include <Thread2.h>

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

public slots:
    void startProcess(int peak, int zero);
    void startProcess(int result);

private slots:
    void on_pb_ChoseImage_clicked();

    void on_slider_ReSize_valueChanged(int value);

    void on_pb_ChoseDecodeImage_clicked();

    void on_pb_Save_clicked();

private:
    Ui::MainWindow *ui;
    cv::Mat mat_Image;
    //QMessageBox *messagebox;
    Thread1 *thread;
    Thread2 *thread2;

    cv::Mat adjustSize(cv::Mat mat);
    cv::Mat adjustSize(cv::Mat mat, double value);
    cv::Mat faceDetected(cv:: Mat mat);
};

#endif // MAINWINDOW_H
