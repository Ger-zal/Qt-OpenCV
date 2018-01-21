#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow){
    ui->setupUi(this);
    stream.open(0);
    if(!stream.isOpened()){
        qDebug() << "Stream is not accessible";
    }
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(getImage()));
    timer->start(5);
}

MainWindow::~MainWindow(){
    if(stream.isOpened()) stream.release();
    delete ui;
}

void MainWindow::getImage(){
    stream.read(img);
    cv::cvtColor(img,img,CV_BGR2RGB);
    cv::resize(img, img, cv::Size(ui->label->size().width(), ui->label->size().height()));
    cv::cvtColor(img,imgHSV,CV_RGB2HSV);
    ui->label->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888)));
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    int x = event->x();
    int y = event->y();
    if (( x < ui->label->size().width()) & (y < ui->label->size().height())){
        ui->coordinate->setPlainText("("+ QString::number(x) + "," + QString::number(y) + ")");
        cv::Vec3b color = img.at<cv::Vec3b>(y,x);
        ui->HSV->setPlainText("(" + QString::number(color[0]) + "," + QString::number(color[1]) + "," + QString::number(color[0]) + ")");
    }
}
