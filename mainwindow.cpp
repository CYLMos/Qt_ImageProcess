#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

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
    cv::Mat image = cv::imread(fileName.toStdString(),CV_LOAD_IMAGE_UNCHANGED);
    cv::cvtColor(image,image,CV_BGR2RGB);
    image = adjustSize(image);
    QImage qImage((const uchar *)image.data,image.cols,image.rows,image.step,QImage::Format_RGB888);
    qImage.bits();
    ui->lb_Image->setPixmap(QPixmap::fromImage(qImage));
}


cv::Mat MainWindow::adjustSize(cv::Mat &mat){
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
