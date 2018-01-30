#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QMouseEvent>
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

private slots:
    void updateImage();
    void on_transform_clicked();
    void on_original_clicked();

private:
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *event);
    Ui::MainWindow *ui;
    cv::VideoCapture stream;
    cv::Mat img;
    cv::Mat imgHSV;
    QImage  Qimg;
    QTimer *timer;
    bool clicked;
    bool transform;
    cv::Vec3b hsvOriginal;
};

#endif // MAINWINDOW_H
