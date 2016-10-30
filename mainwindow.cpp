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
    this->mat_Image.release();
}

void MainWindow::on_pb_ChoseImage_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"open file","","image files(*.jpg *.png *.bmp *.jpeg)");
    if(!fileName.isEmpty()){
        this->mat_Image = cv::imread(fileName.toStdString(),CV_LOAD_IMAGE_UNCHANGED);
        cv::cvtColor(this->mat_Image,this->mat_Image,CV_BGR2RGB);

        this->mat_Image = adjustSize(this->mat_Image);  //resize
        this->mat_Image = faceDetected(this->mat_Image);  //recognize face

        QImage qImage((const uchar *)this->mat_Image.data,this->mat_Image.cols,this->mat_Image.rows,this->mat_Image.step,QImage::Format_RGB888);
        ui->lb_Image->setPixmap(QPixmap::fromImage(qImage));
        QSize size;
        size.setHeight(qImage.height());
        size.setWidth(qImage.width());
        ui->lb_Image->setFixedSize(size);
    }
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

cv::Mat MainWindow::faceDetected(cv::Mat mat){
    QString cascadeName = "../Image_Process/haarcascade_frontalface_alt.xml";
    cv::CascadeClassifier  classifier;
    classifier.load(cascadeName.toStdString());
    std::vector<cv::Rect> rects;
    classifier.detectMultiScale(mat,rects,1.1,3,
                                CV_HAAR_DO_CANNY_PRUNING
                                |CV_HAAR_SCALE_IMAGE,
                                cv::Size(0, 0),
                                cv::Size(300,300));
    /*for(int i=0;i<rects.size();i++){
        cv::Rect r = rects[i];
        cv::Point point1(r.x+r.width,r.y+r.height);
        cv::Point point2(r.x,r.y);
        cv::rectangle(mat,point1,point2,cv::Scalar(255,0,0),1,cv::LINE_8,0);
    }*/
    //just catch one face
    cv::Rect r = rects[0];

    //adjust rect size
    double scale = 1.0;
    int x = (int)((double)r.width)*(1.0+scale),y = (int)((double)r.height)*(1.0+scale);
    r.x = r.x - (x - r.width)/2;r.y = r.y - (y - r.height)/2;
    r.width = x;r.height = y;

    mat = mat(r);

    return mat;
}
