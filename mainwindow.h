/****************************************************************************
 * @file mainwindow.h                                                                   
 * @author Rajesh Rimal (rajeshrimal516@gmail.com)
 * @brief Header file for the Event Functions in mainwindow.cpp
 * @version 0.1
 * @date 2022-07-15
 * 
 * @copyright Copyright (c) 2022
 * 
 ****************************************************************************/


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
/***********************************************************************************
 * @brief Construct a new Main Window:: Main Window object
 * 
 * @param parent 
 **********************************************************************************/
    MainWindow(QWidget *parent = nullptr);


/***********************************************************************************
 * @brief Close any active events
 * 
 **********************************************************************************/
    void closeEvent(QCloseEvent *);


/***********************************************************************************
 * @brief Function to record the mouse double click event. 
 * 
 **********************************************************************************/
    void mouseDoubleClickEvent(QMouseEvent *);


/***********************************************************************************
 * @brief Function to toggle between full screen and normal screen
 * 
 * @param fs Boolean value (True when Normal Screen)
 **********************************************************************************/
    void onToggleFullScreen(bool fs);


/***********************************************************************************
 * @brief Destroy the Main Window:: Main Window object
 * 
 **********************************************************************************/
    ~MainWindow();


private slots:

/***********************************************************************************
 * @brief The function to load the image when user clicks upload or (keyboard shortcut Ctrl + o)
 *   from file menu.
 * 
 **********************************************************************************/
    void on_actionUpload_triggered();


/***********************************************************************************
 * @brief The Function to link the event to Upload Image when user clicks Upload Button in 
 *          "Upload and Edit" Tab. 
 * 
 **********************************************************************************/
    void on_Upload_clicked();



/***********************************************************************************
 * @brief The function to capture image using camera when Capture button is clicked 
 *          by the user in Tab 2 (Open Camera). 
 * 
 **********************************************************************************/
    void on_Camera_clicked();


/***********************************************************************************
 * @brief The function to save the image to desired directory when user clicks Save or 
 * (keyboard shortcut Ctrl + s) from file menu.
 * 
 **********************************************************************************/
    void on_actionSave_triggered();


/***********************************************************************************
 * @brief The Function to link the event to Save Image when user clicks Save Button in 
 *          "Upload and Edit" Tab. 
 * 
 **********************************************************************************/
    void on_Save_clicked();


/***********************************************************************************
 * @brief The function to Exit the application the image when user clicks Exit  
 *          (or keyboard shortcut Esc) from file menu. If the image is modified it
 *          asks the user to save before exiting.
 * 
 **********************************************************************************/
    void on_actionExit_triggered();


/***********************************************************************************
 * @brief The Function to link the event to Exit the appliation when user clicks Exit 
 *          Button in "Upload and Edit" Tab. 
 * 
 **********************************************************************************/
    void on_Exit_clicked();


/***********************************************************************************
 * @brief The Function to link the event to correct the brightness when user clicks 
 *          Brightness in Edit Menu or (Keyboard shortcut B)
 * 
 **********************************************************************************/
    void on_actionBrightess_triggered();


/***********************************************************************************
 * @brief The Function to link the event to correct the brightness when user clicks 
 *          Brightness Button in "Upload and Edit" Tab. 
 * 
 **********************************************************************************/
    void on_Brightness_clicked();


/***********************************************************************************
 * @brief The Function to link the event to correct the Contrast when user clicks 
 *          Contrast in Edit Menu or (Keyboard shortcut C)
 * 
 **********************************************************************************/
    void on_actionContrast_triggered();


/***********************************************************************************
 * @brief The Function to link the event to correct the contrast when user clicks 
 *          Contrast Button in "Upload and Edit" Tab.  
 * 
 **********************************************************************************/
    void on_Contrast_clicked();
    

/***********************************************************************************
 * @brief The Function to link the event to correct the Color when user clicks color in 
 *       Edit Menu or (Keyboard shortcut Ctrl + C)
 * 
 **********************************************************************************/
    void on_actionColor_triggered();


/***********************************************************************************
 * @brief The Function to link the event to correct the color when user clicks 
 *          Color Button in "Upload and Edit" Tab. 
 * 
 **********************************************************************************/
    void on_Color_clicked();


/***********************************************************************************
 * @brief  The Function to link the event to correct the Hue when user clicks Hue in 
 *          Edit Menu ( or Keyboard shortcut H)
 *
 **********************************************************************************/
    void on_actionHue_triggered();


/***********************************************************************************
 * @brief The Function to link the event to correct the Hue when user clicks 
 *          Hue Button in "Upload and Edit" Tab. 
 * 
 **********************************************************************************/
    void on_Hue_clicked();


/***********************************************************************************
 * @brief The Function to link the event to sharpnen or blur image when user clicks 
 * Sharpness in Edit Menu ( or Keyboard shortcut S)
 * 
 **********************************************************************************/
    void on_actionSharpness_triggered();


/***********************************************************************************
 * @brief The Function to link the event to Sharpen/Blur image when user clicks 
 *          Sharpness Button in "Upload and Edit" Tab. 
 * 
 **********************************************************************************/
    void on_Sharpness_clicked();


/***********************************************************************************
 * @brief The Function to link the event to rezise image when user clicks 
 * Resize in Edit Menu ( or Keyboard shortcut R)
 * 
 **********************************************************************************/
    void on_actionResize_triggered();


/***********************************************************************************
 * @brief The Function to link the event to Resize image when user clicks 
 *          Resize Button in "Upload and Edit" Tab.
 * 
 **********************************************************************************/
    void on_Resize_clicked();


/***********************************************************************************
 * @brief The Function to link the event to corresponding events from buttons clicked
 *          and call the appropriate function for Editing the image while user changes 
 *          the slider position
 * 
 * @param sliderPos 
 **********************************************************************************/
    void on_horizontalSlider_valueChanged(int sliderPos);


/***********************************************************************************
 * @brief The function to display the image to the user in the Image Viewer section
 * 
 * @param displayImage Image converted to QPixmap from Qimage
 **********************************************************************************/
    void on_actionImage_Display_triggered(QPixmap displayImage);

    
/***********************************************************************************
 * @brief Function to switch between the tabs 
 * 
 * @param index Tab index value (1 or 2)
 **********************************************************************************/
    void on_Tab_tabBarClicked(int tabIndex);


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
