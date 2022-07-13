#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "Edit.h"
#include <math.h>
#include <QMessageBox>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QAction>
#include <QDateTime>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QMessageBox>
#include <QElapsedTimer>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE
class QCamera;

class QCameraViewfinder;

class QCameraImageCapture;

class QVBoxLayout;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void closeEvent(QCloseEvent *);

    void mouseDoubleClickEvent(QMouseEvent *);

    void onToggleFullScreen(bool fs);

    ~MainWindow();

private slots:

    void on_actionSave_triggered();

    void on_actionExit_triggered();

    void on_actionBrightess_triggered();

    void on_Upload_clicked();

    void on_Brightness_clicked();

    void on_actionContrast_triggered();

    void on_actionColor_triggered();

    void on_Contrast_clicked();

    void on_Color_clicked();

    void on_horizontalSlider_valueChanged(int sliderPos);

    void on_actionHue_triggered();

    void on_Hue_clicked();

    void on_Sharpness_clicked();

    void on_Resize_clicked();

    void on_actionSharpness_triggered();

    void on_actionResize_triggered();

    void on_actionImage_Display_triggered(QPixmap displayImage);

    void on_Save_clicked();

    void on_Exit_clicked();

    void on_Camera_clicked();

    void on_Tab_tabBarClicked(int tabIndex);

    void on_actionUpload_triggered();


public:
     Ui::MainWindow *ui;

private:
    QString filename_open;
    QString filename_save;
    QString filename_copy;

    QPixmap original_img;
    QPixmap processed_img;
    QPixmap capture_img;

    int edit_case;
    bool ismodified=false;
    QElapsedTimer timer;
    QCamera* mCam;
    QCameraViewfinder* mCamvf;
    QCameraImageCapture* mCamCap;
    QVBoxLayout *mLayout;
};
#endif // MAINWINDOW_H
