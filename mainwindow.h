#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<QMouseEvent>
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
    void getImage();

private:
    void mousePressEvent(QMouseEvent *event);
    Ui::MainWindow *ui;
    cv::VideoCapture stream;
    cv::Mat img;
    cv::Mat imgHSV;
    QImage  Qimg;
    QTimer *timer;
};

#endif // MAINWINDOW_H
