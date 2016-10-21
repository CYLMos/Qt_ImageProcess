#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv_modules.hpp"
#include "cv.h"
#include"highgui.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    cv::Mat image = cv::imread("C:\\Users\\LinCY\\Desktop\\14489663_979466592163831_719162473_o.jpg",CV_LOAD_IMAGE_ANYCOLOR);
    //cv::Mat image;
    cv::cvtColor(image,image,CV_BGR2RGB);
    //cv::cvtColor(s,image,CV_)
    QImage im((const uchar *)image.data,image.cols,image.rows,image.step,QImage::Format_RGB888);
    im.bits();
    ui->label->setPixmap(QPixmap::fromImage(im));
    QSize size;
    size.setHeight(im.height());
    size.setWidth(im.width());
    ui->label->setFixedSize(size);
}

MainWindow::~MainWindow()
{
    delete ui;
}
