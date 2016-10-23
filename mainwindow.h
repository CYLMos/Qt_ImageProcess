#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv_modules.hpp"
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

private:
    Ui::MainWindow *ui;

    cv::Mat adjustSize(cv::Mat &mat);
};

#endif // MAINWINDOW_H
