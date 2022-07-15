/***********************************************************************************
 * @file mainwindow.cpp
 * @author Rajesh RImal (rajeshrimal516@gmail.com)
 * @brief Source for linking the GUI, and events and actions
 * @version 0.1
 * @date 2022-07-14
 * 
 * @copyright Copyright (c) 2022
 * 
 **********************************************************************************/

#include "mainwindow.h"



/***********************************************************************************
 * @brief Construct a new Main Window:: Main Window object
 * 
 * @param parent 
 **********************************************************************************/
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mCam = new QCamera(this);
    mCamvf = new QCameraViewfinder(this);
    mCamCap = new QCameraImageCapture(mCam,this);
    mLayout = new QVBoxLayout;
    mCamvf->show();
    mCam->setViewfinder(mCamvf);
    mLayout->addWidget(mCamvf);
    ui->CameraView->setLayout(mLayout);
}



/***********************************************************************************
 * @brief Destroy the Main Window:: Main Window object
 * 
 **********************************************************************************/
MainWindow::~MainWindow()
{
    delete ui;
}



/***********************************************************************************
 * @brief Close any active events
 * 
 **********************************************************************************/
void MainWindow::closeEvent(QCloseEvent *)
{
    if(ismodified)
    {
        on_actionExit_triggered();
    }
}



/***********************************************************************************
 * @brief Function to record the mouse double click event. 
 * 
 **********************************************************************************/
void MainWindow::mouseDoubleClickEvent(QMouseEvent *)
{
    onToggleFullScreen(!isFullScreen());
}



/***********************************************************************************
 * @brief Function to toggle between full screen and normal screen
 * 
 * @param fs Boolean value (True when Normal Screen)
 **********************************************************************************/
void MainWindow::onToggleFullScreen(bool fs)
{
    if (fs)
    {
        showFullScreen();
        ui->quitAction->setVisible(true);
    }
    else
    {
        ui->quitAction->setVisible(false);
        showNormal();
    }
}




/***********************************************************************************
 * @brief Function to switch between the tabs 
 * 
 * @param index Tab index value (1 or 2)
 **********************************************************************************/
void MainWindow::on_Tab_tabBarClicked(int index)
{

    if(index==1)  {

        if(!filename_open.isEmpty()&& ismodified)
            {
                QMessageBox::StandardButton reply = QMessageBox::question(this,"Image Editor","Do you want to save the image?",
                                                                       QMessageBox:: Save|QMessageBox:: Discard);
                if(reply== QMessageBox::Save)
                {

                   on_Save_clicked();

                }

                }
        mCam->start();
    }
    else
    {
        mCam->stop();
    }
}




/***********************************************************************************
 * @brief The function to load the image when user clicks upload or (keyboard shortcut Ctrl + o)
 *   from file menu.
 * 
 **********************************************************************************/
void MainWindow::on_actionUpload_triggered()
{   if(ismodified)
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this,"Image Editor","Do you want to save the image?",
                                                               QMessageBox:: Save|QMessageBox:: Discard);

        if(reply== QMessageBox::Save)
        {

         on_actionSave_triggered();

        }

        }
    filename_open = QFileDialog::getOpenFileName(this,"Open an image",QDir::homePath(),
                                                  "Images (*.jpg *.jpeg *.JPG *.png *.PNG *.bmp *.BMP );;""JPG (*.jpg *.jpeg *.JPG);;"
                                                  "PNG (*.png *.PNG);;""BMP (*.bmp *.BMP)");
    if(!filename_open.isEmpty())
    {
        original_img.load(filename_open);
        QGraphicsScene *scene=new QGraphicsScene;
        QGraphicsPixmapItem *item= new QGraphicsPixmapItem(original_img);
        scene->addItem(item);
        ui->editView->setScene(scene);
        ui->editView->show();
        ui->editView->fitInView(scene->itemsBoundingRect() ,Qt::KeepAspectRatio);
        ui->editlabel->setText("Original Image");
        filename_copy=filename_open;
        ui->horizontalSlider->setValue(0);
        ui->label->setText(QLocale().toString(0));
        ui->statusBar->showMessage("Original Image Uploaded");
        edit_case=7;
    }
    else if(!filename_copy.isEmpty())
    {
        filename_open=filename_copy;
    }
}




/***********************************************************************************
 * @brief The function to capture image using camera when Capture button is clicked 
 *          by the user in Tab 2 (Open Camera). 
 * 
 **********************************************************************************/
void MainWindow::on_Camera_clicked()
{
    QDateTime now = QDateTime::currentDateTime();
    QString timestamp = now.toString(QLatin1String("yyyyMMdd-hhmmss"));
    filename_open = QString::fromLatin1("C:/Users/Img-%1.jpg").arg(timestamp);
    mCam->setCaptureMode(QCamera::CaptureStillImage);
    mCamCap->setCaptureDestination(QCameraImageCapture::CaptureToFile);
    mCam->searchAndLock();
    mCamCap->capture(filename_open);
    mCam->unlock();
    QMessageBox::StandardButton reply = QMessageBox::question(this,"Image is Captured","Do you want to capture again?",
                                                              QMessageBox:: Yes | QMessageBox:: No);
    if(reply== QMessageBox::Yes)
    {
        mCam->start();
    }

    if(reply== QMessageBox::No)
    {
        original_img.load(filename_open);
        QGraphicsScene *scene=new QGraphicsScene;
        QGraphicsPixmapItem *item= new QGraphicsPixmapItem(original_img);
        scene->addItem(item);
        ui->editView->setScene(scene);
        ui->editView->show();
        ui->editView->fitInView(scene->itemsBoundingRect() ,Qt::KeepAspectRatio);
        ui->editlabel->setText("Captured Image");
        ui->horizontalSlider->setValue(0);
        ui->label->setText(QLocale().toString(0));
        ui->statusBar->showMessage("Image Captured");
        edit_case=7;
    }
}



/***********************************************************************************
 * @brief The function to save the image to desired directory when user clicks Save or 
 * (keyboard shortcut Ctrl + s) from file menu.
 * 
 **********************************************************************************/
void MainWindow::on_actionSave_triggered()
{
    QFile file(filename_open);
    if(!file.exists(filename_open))
    {
        QMessageBox::warning(this,"Error","No File to Save");
        qDebug() << "File not open" << file.error();
    }
    else
    {
        if(ismodified)
        {
            const QDateTime now = QDateTime::currentDateTime();
            const QString timestamp = now.toString(QLatin1String("yyyyMMdd-hhmmss"));
            const QString filename = QString::fromLatin1("C:/Users/Img-%1.jpg").arg(timestamp);
            filename_save = QFileDialog::getSaveFileName(this,"Save an Image",filename,"Images (*.jpg *.jpeg *.JPG *.png *.PNG *.bmp *.BMP );;"
                                                    "JPG (*.jpg *.jpeg *.JPG);;"
                                                    "PNG (*.png *.PNG);;"
                                                    "BMP (*.bmp *.BMP)");

        if(!filename_save.isEmpty())
        {
            processed_img.save(filename_save);
            QMessageBox::information(this, "Image Saved Successfully",filename_save);
            ismodified=false;
        }
        }
    }
}



/***********************************************************************************
 * @brief The function to Exit the application the image when user clicks Exit  
 *          (or keyboard shortcut Esc) from file menu. If the image is modified it
 *          asks the user to save before exiting.
 * 
 **********************************************************************************/
void MainWindow::on_actionExit_triggered()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this,"Image Editor","Do you want to save the image before closing?",
                                                              QMessageBox:: Save|QMessageBox:: Discard);
    if(reply== QMessageBox::Discard)
    {
        QApplication::quit();
    }
    if(reply== QMessageBox::Save)
    {
        QFile file(filename_open);
        if(!file.exists(filename_open))
        {
            QMessageBox::warning(this,"Error","No File to Save");
            qDebug() << "File not open" << file.error();
        }
        else
        {
            if(ismodified)
            {
                const QDateTime now = QDateTime::currentDateTime();
                const QString timestamp = now.toString(QLatin1String("yyyyMMdd-hhmmss"));
                const QString filename = QString::fromLatin1("C:/Users/Img-%1.jpg").arg(timestamp);
                filename_save = QFileDialog::getSaveFileName(this,"Save an Image",filename,
                                                         "Images (*.jpg *.jpeg *.JPG *.png *.PNG *.bmp *.BMP );;"
                                                         "JPG (*.jpg *.jpeg *.JPG);;""PNG (*.png *.PNG);;""BMP (*.bmp *.BMP)");
                if(!filename_save.isEmpty())
                {
                    processed_img.save(filename_save);
                    QMessageBox::information(this, "Image Saved Successfully",filename_save);
                    ismodified=false;
                }

            }
        }
    }
}



/***********************************************************************************
 * @brief The Function to link the event to correct the brightness when user clicks 
 *          Brightness in Edit Menu or (Keyboard shortcut B)
 * 
 **********************************************************************************/
void MainWindow::on_actionBrightess_triggered()
{
    if(ismodified)
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this,"Image Editor","Do you want to save the image before Leaving?",
                                                                    QMessageBox:: Save|QMessageBox:: Discard);
        if(reply== QMessageBox::Save)
        {
            QFile file(filename_open);
            if(!file.exists(filename_open))
            {
                QMessageBox::warning(this,"Error","No File to Save");
                qDebug() << "File not open" << file.error();
            }
            else
                on_actionSave_triggered();
        }
    }

    QMessageBox::StandardButton msgBox = QMessageBox::question(this,"Open Editor","Do you want to Edit Brightness?",
                                                               QMessageBox::Yes|QMessageBox::No);
    if (msgBox == QMessageBox::Yes)
    {
        QFile file(filename_open);
        if(!file.exists(filename_open))
        {
            QMessageBox::warning(this,"Error","No File to Open");
            qDebug() << "File not open" << file.error();
        }
        else
        {
            ui->editlabel->setText("Editing View: Brightness Editing");
            ui->statusBar->showMessage("Editing View: Brightness Editing");
            processed_img = original_img.copy();
            on_actionImage_Display_triggered(processed_img);
            ui->horizontalSlider->setValue(0);
            edit_case=1;
            ismodified=true;
        }
    }
}



/***********************************************************************************
 * @brief The Function to link the event to correct the Contrast when user clicks 
 *          Contrast in Edit Menu or (Keyboard shortcut C)
 * 
 **********************************************************************************/
void MainWindow::on_actionContrast_triggered()
{
    if(ismodified)
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this,"Image Editor","Do you want to save the image before Leaving?",
                                                                    QMessageBox:: Save|QMessageBox:: Discard);
        if(reply== QMessageBox::Save)
        {
            QFile file(filename_open);
            if(!file.exists(filename_open))
            {
                QMessageBox::warning(this,"Error","No File to Save");
                qDebug() << "File not open" << file.error();
            }
            else
                on_actionSave_triggered();
        }
    }

    QMessageBox::StandardButton msgBox = QMessageBox::question(this,"Open Editor","Do you want to Edit Contrast?",
                                                               QMessageBox::Yes|QMessageBox::No);
    if (msgBox == QMessageBox::Yes)
    {
        QFile file(filename_open);
        if(!file.exists(filename_open))
        {
            QMessageBox::warning(this,"Error","No File to Open");
            qDebug() << "File not open" << file.error();
        }
        else
        {
            ui->editlabel->setText("Editing View: Contrast Editing");
            ui->statusBar->showMessage("Editing View: Contrast Editing");
            processed_img = original_img.copy();
            on_actionImage_Display_triggered(processed_img);
            ui->horizontalSlider->setValue(0);
            edit_case=2;
            ismodified=true;
        }
    }
}



/***********************************************************************************
 * @brief The Function to link the event to correct the Color when user clicks color in 
 *       Edit Menu or (Keyboard shortcut Ctrl + C)
 * 
 **********************************************************************************/
void MainWindow::on_actionColor_triggered()
{
    if(ismodified)
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this,"Image Editor","Do you want to save the image before Leaving?",
                                                                    QMessageBox:: Save|QMessageBox:: Discard);
        if(reply== QMessageBox::Save)
        {
            QFile file(filename_open);
            if(!file.exists(filename_open))
            {
                QMessageBox::warning(this,"Error","No File to Save");
                qDebug() << "File not open" << file.error();
            }
            else
                on_actionSave_triggered();
        }
    }

    QMessageBox::StandardButton msgBox = QMessageBox::question(this,"Open Editor","Do you want to Edit Color?",
                                                               QMessageBox::Yes|QMessageBox::No);
    if (msgBox == QMessageBox::Yes)
    {
        QFile file(filename_open);
        if(!file.exists(filename_open))
        {
            QMessageBox::warning(this,"Error","No File to Open");
            qDebug() << "File not open" << file.error();
        }
        else
        {
            ui->editlabel->setText("Editing View: Color Editing");
            ui->statusBar->showMessage("Editing View: Color Editing");
            processed_img = original_img.copy();
            on_actionImage_Display_triggered(processed_img);
            ui->horizontalSlider->setValue(0);
            edit_case=3;
            ismodified=true;
        }
    }
}



/***********************************************************************************
 * @brief  The Function to link the event to correct the Hue when user clicks Hue in 
 *          Edit Menu ( or Keyboard shortcut H)
 *
 **********************************************************************************/
void MainWindow::on_actionHue_triggered()
{
    if(ismodified)
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this,"Image Editor","Do you want to save the image before Leaving?",
                                                                    QMessageBox:: Save|QMessageBox:: Discard);
        if(reply== QMessageBox::Save)
        {
            QFile file(filename_open);
            if(!file.exists(filename_open))
            {
                QMessageBox::warning(this,"Error","No File to Save");
                qDebug() << "File not open" << file.error();
            }
            else
                on_actionSave_triggered();
        }
    }

    QMessageBox::StandardButton msgBox = QMessageBox::question(this,"Open Editor","Do you want to Edit Hue?",
                                                               QMessageBox::Yes|QMessageBox::No);
    if (msgBox == QMessageBox::Yes)
    {
        QFile file(filename_open);
        if(!file.exists(filename_open))
        {
            QMessageBox::warning(this,"Error","No File to Open");
            qDebug() << "File not open" << file.error();
        }
        else
        {
            ui->editlabel->setText("Editing View: Hue Editing");
            ui->statusBar->showMessage("Editing View: Hue Editing");
            processed_img = original_img.copy();
            on_actionImage_Display_triggered(processed_img);
            ui->horizontalSlider->setValue(0);
            edit_case=4;
            ismodified=true;
        }
    }
}



/***********************************************************************************
 * @brief The Function to link the event to sharpnen or blur image when user clicks 
 * Sharpness in Edit Menu ( or Keyboard shortcut S)
 * 
 **********************************************************************************/
void MainWindow::on_actionSharpness_triggered()
{
    if(ismodified)
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this,"Image Editor","Do you want to save the image before Leaving?",
                                                                    QMessageBox:: Save|QMessageBox:: Discard);
        if(reply== QMessageBox::Save)
        {
            QFile file(filename_open);
            if(!file.exists(filename_open))
            {
                QMessageBox::warning(this,"Error","No File to Save");
                qDebug() << "File not open" << file.error();
            }
            else
                on_actionSave_triggered();
        }
    }

    QMessageBox::StandardButton msgBox = QMessageBox::question(this,"Open Editor","Do you want to Edit Sharpness?",
                                                               QMessageBox::Yes|QMessageBox::No);
    if (msgBox == QMessageBox::Yes)
    {
        QFile file(filename_open);
        if(!file.exists(filename_open))
        {
            QMessageBox::warning(this,"Error","No File to Open");
            qDebug() << "File not open" << file.error();
        }
        else
        {
            ui->editlabel->setText("Editing View: Sharpness/Blur Editing");
            ui->statusBar->showMessage("Editing View: Brightness/Blur Editing");
            processed_img = original_img.copy();
            on_actionImage_Display_triggered(processed_img);
            ui->horizontalSlider->setValue(0);
            edit_case=5;
            ismodified=true;
        }
    }
}



/***********************************************************************************
 * @brief The Function to link the event to rezise image when user clicks 
 * Resize in Edit Menu ( or Keyboard shortcut R)
 * 
 **********************************************************************************/
void MainWindow::on_actionResize_triggered()
{
    if(ismodified)
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this,"Image Editor","Do you want to save the image before Leaving?",
                                                                    QMessageBox:: Save|QMessageBox:: Discard);
        if(reply== QMessageBox::Save)
        {
            QFile file(filename_open);
            if(!file.exists(filename_open))
            {
                QMessageBox::warning(this,"Error","No File to Save");
                qDebug() << "File not open" << file.error();
            }
            else
                on_actionSave_triggered();
        }
    }

    QMessageBox::StandardButton msgBox = QMessageBox::question(this,"Open Editor","Do you want to Resize Image?",
                                                               QMessageBox::Yes|QMessageBox::No);
    if (msgBox == QMessageBox::Yes)
    {
        QFile file(filename_open);
        if(!file.exists(filename_open))
        {
            QMessageBox::warning(this,"Error","No File to Open");
            qDebug() << "File not open" << file.error();
        }
        else
        {
            ui->editlabel->setText("Editing View: Resizing Image");
            ui->statusBar->showMessage("Editing View: Resizing Editing");
            processed_img = original_img.copy();
            on_actionImage_Display_triggered(processed_img);
            ui->horizontalSlider->setValue(0);
            edit_case=6;
            ismodified=true;
        }
    }
}



/***********************************************************************************
 * @brief The Function to link the event to corresponding events from buttons clicked
 *          and call the appropriate function for Editing the image while user changes 
 *          the slider position
 * 
 * @param sliderPos 
 **********************************************************************************/
void MainWindow::on_horizontalSlider_valueChanged(int sliderPos)
{
    QImage send = original_img.copy().toImage();
    qint64 time = 0;
    switch(edit_case)
    {
    case 1:
        ui->label->setText(QLocale().toString(sliderPos));
        timer.start();
        Brightness(&send,sliderPos);
        time = timer.elapsed();
        ui->statusBar->showMessage("Brightness loop Execution Time: "+QLocale().toString(time)+" milliseconds");
        break;

    case 2:
        ui->label->setText(QLocale().toString(sliderPos));
        timer.start();
        Contrast(&send,sliderPos);
        time = timer.elapsed();
        ui->statusBar->showMessage("Contrast loop Execution Time: "+QLocale().toString(time)+" milliseconds");
        break;

    case 3:
        ui->label->setText(QLocale().toString(sliderPos));
        timer.start();
        Color(&send,sliderPos);
        time = timer.elapsed();
        ui->statusBar->showMessage("Color loop Execution Time: "+QLocale().toString(time)+" milliseconds");
        break;

     case 4:
        ui->label->setText(QLocale().toString(sliderPos));
        timer.start();
        Hue(&send,sliderPos);
        time = timer.elapsed();
        ui->statusBar->showMessage("Hue loop Execution Time: "+QLocale().toString(time)+" milliseconds");
        break;

    case 5:
        ui->label->setText(QLocale().toString(sliderPos));
        timer.start();
        send = Sharpness(send,sliderPos);
        time = timer.elapsed();
        ui->statusBar->showMessage("Sharpness loop Execution Time: "+QLocale().toString(time)+" milliseconds");
        break;

    case 6:
        timer.start();
        send = Resize(send,sliderPos);
        time = timer.elapsed();
        ui->label->setText(QLocale().toString(sliderPos)+"\n" +
        QLocale().toString(send.width())+ "x"+ QLocale().toString(send.height()));
        ui->statusBar->showMessage("Resize loop Execution Time: "+QLocale().toString(time)+" milliseconds");
        break;
    case 7:
        ui->label->setText(QLocale().toString(0));
        break;
    }
    processed_img = processed_img.fromImage(send);
    on_actionImage_Display_triggered(processed_img);

    if(!filename_open.isEmpty())
        ismodified=true;
}



/***********************************************************************************
 * @brief The function to display the image to the user in the Image Viewer section
 * 
 * @param displayImage Image converted to QPixmap from Qimage
 **********************************************************************************/
void MainWindow::on_actionImage_Display_triggered(QPixmap displayImage)
{
    QGraphicsScene *scene=new QGraphicsScene;
    QGraphicsPixmapItem *item= new QGraphicsPixmapItem(displayImage);
    scene->addItem(item);
    ui->editView->setScene(scene);
    ui->editView->show();
    ui->editView->fitInView(scene->itemsBoundingRect() ,Qt::KeepAspectRatio);
}



/***********************************************************************************
 * @brief The Function to link the event to Upload Image when user clicks Upload Button in 
 *          "Upload and Edit" Tab. 
 * 
 **********************************************************************************/
void MainWindow::on_Upload_clicked()
{
    on_actionUpload_triggered();
}



/***********************************************************************************
 * @brief The Function to link the event to Save Image when user clicks Save Button in 
 *          "Upload and Edit" Tab. 
 * 
 **********************************************************************************/
void MainWindow::on_Save_clicked()
{
    on_actionSave_triggered();
}



/***********************************************************************************
 * @brief The Function to link the event to Exit the appliation when user clicks Exit 
 *          Button in "Upload and Edit" Tab. 
 * 
 **********************************************************************************/
void MainWindow::on_Exit_clicked()
{
    on_actionExit_triggered();
}



/***********************************************************************************
 * @brief The Function to link the event to correct the brightness when user clicks 
 *          Brightness Button in "Upload and Edit" Tab. 
 * 
 **********************************************************************************/
void MainWindow::on_Brightness_clicked()
{
    on_actionBrightess_triggered();
}



/***********************************************************************************
 * @brief The Function to link the event to correct the contrast when user clicks 
 *          Contrast Button in "Upload and Edit" Tab.  
 * 
 **********************************************************************************/
void MainWindow::on_Contrast_clicked()
{
    on_actionContrast_triggered();
}



/***********************************************************************************
 * @brief The Function to link the event to correct the color when user clicks 
 *          Color Button in "Upload and Edit" Tab. 
 * 
 **********************************************************************************/
void MainWindow::on_Color_clicked()
{
    on_actionColor_triggered();
}



/***********************************************************************************
 * @brief The Function to link the event to correct the Hue when user clicks 
 *          Hue Button in "Upload and Edit" Tab. 
 * 
 **********************************************************************************/
void MainWindow::on_Hue_clicked()
{
    on_actionHue_triggered();
}



/***********************************************************************************
 * @brief The Function to link the event to Sharpen/Blur image when user clicks 
 *          Sharpness Button in "Upload and Edit" Tab. 
 * 
 **********************************************************************************/
void MainWindow::on_Sharpness_clicked()
{
    on_actionSharpness_triggered();
}



/***********************************************************************************
 * @brief The Function to link the event to Resize image when user clicks 
 *          Resize Button in "Upload and Edit" Tab.
 * 
 **********************************************************************************/
void MainWindow::on_Resize_clicked()
{
    on_actionResize_triggered();
}

