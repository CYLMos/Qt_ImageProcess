#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ChoseImage_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"open file","","image files(*.jpg *.png *.bmp *.jpeg)");
    this->mat_Image = cv::imread(fileName.toStdString(),CV_LOAD_IMAGE_UNCHANGED);
    cv::cvtColor(this->mat_Image,this->mat_Image,CV_BGR2RGB);
    this->mat_Image = adjustSize(this->mat_Image);  //resize
    QImage qImage((const uchar *)this->mat_Image.data,this->mat_Image.cols,this->mat_Image.rows,this->mat_Image.step,QImage::Format_RGB888);
    ui->lb_Image->setPixmap(QPixmap::fromImage(qImage));
    QSize size;
    size.setHeight(qImage.height());
    size.setWidth(qImage.width());
    ui->lb_Image->setFixedSize(size);
}

void MainWindow::on_slider_ReSize_valueChanged(int value)
{
    cv::Mat image = adjustSize(this->mat_Image,(double)value);
    QImage qImage = QImage((const uchar *)image.data,image.cols,image.rows,image.step,QImage::Format_RGB888);
    ui->lb_Image->setPixmap(QPixmap::fromImage(qImage));
    QSize size;
    size.setHeight(qImage.height());
    size.setWidth(qImage.width());
    ui->lb_Image->setFixedSize(size);
}


cv::Mat MainWindow::adjustSize(cv::Mat mat){
    IplImage *srcImage = new IplImage(mat);
    IplImage *dstImage = 0;
    while(srcImage->height > ui->lb_Image->size().height() || srcImage->width > ui->lb_Image->size().width()){
        double ratio = 0.618;
        CvSize size;

        size.width = srcImage->width * ratio;
        size.height = srcImage->height * ratio;
        dstImage = cvCreateImage(size,srcImage->depth,srcImage->nChannels);
        cvResize(srcImage,dstImage,CV_INTER_LINEAR);
        srcImage = dstImage;
    }
    mat = cv::cvarrToMat(srcImage);
    return mat;
}

cv::Mat MainWindow::adjustSize(cv::Mat mat, double value){
    IplImage *srcImage = new IplImage(mat);
    IplImage *dstImage = 0;
    double ratio = 1 + value/10.0;
    CvSize size;

    size.width = srcImage->width * ratio;
    size.height = srcImage->height * ratio;
    dstImage = cvCreateImage(size,srcImage->depth,srcImage->nChannels);
    cvResize(srcImage,dstImage,CV_INTER_LINEAR);
    srcImage = dstImage;
    mat = cv::cvarrToMat(srcImage);
    return mat;
}
