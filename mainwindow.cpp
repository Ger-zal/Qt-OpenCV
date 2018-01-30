#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
int Hoffset = 10;
int Soffset = 15;
MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow){
    ui->setupUi(this);
    stream.open(0);
    if(!stream.isOpened()){
        qDebug() << "Stream is not accessible";
    }
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(updateImage()));
    timer->start(5);
    clicked = false;
    transform = false;
}

MainWindow::~MainWindow(){
    if(stream.isOpened()) stream.release();
    delete ui;
}

void MainWindow::getImage(){
    stream.read(img);
    cv::cvtColor(img,img,CV_BGR2RGB);
    // Resize Image
    cv::resize(img, img, cv::Size(ui->label->size().width(), ui->label->size().height()));
    cv::cvtColor(img,imgHSV,CV_RGB2HSV);

}

void MainWindow::updateImage(){
    getImage();

    if (clicked & transform){
        for(int i=0;i<img.size().width;i++){
            for (int j=0; j<img.size().height;j++){
                cv::Vec3b hoi = imgHSV.at<cv::Vec3b>(j,i);
                bool condition = (hoi[0] < hsvOriginal[0]+Hoffset) & (hoi[0] > hsvOriginal[0]-Hoffset);
                condition = condition & ( hoi[1] < hsvOriginal[1]+ Soffset) & (hoi[1] > hsvOriginal[1]-Soffset);
                if (!condition){
                    img.at<cv::Vec3b>(j,i) = 0;
                }
            }
        }
    }
    //COnvert Matrix -> Qlabel
    ui->label->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888)));
}

void MainWindow::mouseMoveEvent(QMouseEvent *e){
    //if (( event->x() < ui->label->size().width()) & (event->y() < ui->label->size().height()) ){
        ui->coordinate->setPlainText("("+ QString::number( e->x()) + "," + QString::number(e->y()) + ")");
    //}
        qDebug()<< "("+ QString::number( e->x()) + "," + QString::number(e->y()) + ")"<<endl;
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    clicked = true;
    int x = event->x();
    int y = event->y();
    if (( x < ui->label->size().width()) & (y < ui->label->size().height()) ){
        hsvOriginal = imgHSV.at<cv::Vec3b>(y,x);
        ui->HSV->setPlainText("(" + QString::number(hsvOriginal[0]) + "," + QString::number(hsvOriginal[1]) + "," + QString::number(hsvOriginal[0]) + ")");
    }
}

void MainWindow::on_transform_clicked(){
    transform = true;
}



void MainWindow::on_original_clicked(){
    transform = false;
}
