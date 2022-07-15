# **QT-Creator-ImageProcessing**

An application - graphical user interface (GUI) using a QT Creator software, which will allow user to import an image or capture image from camera. Moreover, the developed application will allow user to change a brightness, contrast, sharpness, resizing, color, hue of the imported image using a slider and save the changed image. 

## User Guide for application
The executable file with all the necessary dll files and resources files are contained in the Folder named ***Image_Editor.zip***. The executable file are named ***Image_Editor.exe***. Upon clicking the .exe file, the Main Window of the application is opened. The Main Window consists of two main Tabs: Upload and Edit and Open Camera. 

### Main Window
#### Upload and Edit Tab
The upload and Edit Tab consist of buttons such as Gallery, Save, Exit, and buttons for the image processing such as Brightness, Contrast, Color, Hue, Sharpness, Resize. Also, this tab consists of the slider which can be used for processing the image, and an area to display an image to the user.

***Gallery Button:*** The user can upload the image for further processing from the computer. ***Shortcut Key: Ctrl+ O*** <br>
***Save Button:*** Saves the processed Image. ***Shortcut Key: Ctrl+S*** <br>
***Exit Button:*** The user can quit the application with this button. ***Shortcut Key: Esc*** <br>
***Brightness Button:*** Selects the uploaded or captured image to increase or decrease brightness using the slider. ***Shortcut Key: B*** <br>
***Contrast Button:*** Selects the uploaded or captured image to increase or decrease contrast using a slider. ***Shortcut Key: C***<br>
***Color Button:*** Selects the uploaded or captured image to increase or decrease color using a slider. ***Shortcut Key: Ctrl+C***<br>
***Hue Button:*** Selects the uploaded or captured image to vary Hue using the slider. ***Shortcut Key: H***<br>
***Sharpness Button:*** Selects the uploaded or captured image to increase or decrease Sharpness/Blurriness using the slider. ***Shortcut Key: S***<br>
***Resize Button:*** Selects the uploaded or captured image to increase or decrease image size using a slider. ***Shortcut Key: R***<br>
***Slider:*** The slider is used to change the brightness, contrast, etc. by sliding it. It ranges from -100 to 100. <br>

#### Open Camera Tab
Open Camera tab consists of a display area for the camera and a capture button. Upon switching the tab to Open camera, the camera will be turned on. <br> 
***Capture Button:*** On clicking the capture button, the image will be captured by the camera and will be displayed in the Upload and Edit tab image displaying area in which further processing can be done. <br>

The camera will be turned off once the tab is switched to the Upload and Edit Tab.


## **GUI Window**

![image](https://user-images.githubusercontent.com/77145863/179191439-bcf60999-4753-49b6-b80f-ec59821836bf.png) 


## **Additional Task**
The additional task is to deploy the application in the Raspberry Pi. For doing so we need to set up cross-compilation toolchains in Raspberry Pi and Linux Evironment.
### **Procedure:**

After Raspberry Pi OS is setup in the Raspberry Pi, following commands are executed in the Raspberry Pi and Ubuntu/Linux Terminal separately.

#### Raspberry Pi
    sudo rpi-update
    reboot
    sudo raspi-config

##### Install development libraries
    sudo nano /etc/apt/sources.list
    sudo apt-get update
    sudo apt-get build-dep qt4-x11
    sudo apt-get build-dep libqt5gui5
    sudo apt-get install libudev-dev libinput-dev libts-dev libxcb-xinerama0-dev libxcb-xinerama0

##### Prepare target folder
    mkdir ~/raspi
    cd ~/raspi
    git clone https://github.com/raspberrypi/tools

#### Linux/Ubuntu
##### Create working folder and set a toolchain
    mkdir ~/raspi
    cd ~/raspi
    git clone https://github.com/raspberrypi/tools

##### Create and configure a sysroot
    mkdir sysroot sysroot/usr sysroot/opt
    rsync -avz pi@raspberrypi_ip:/lib sysroot
    rsync -avz pi@raspberrypi_ip:/usr/include sysroot/usr
    rsync -avz pi@raspberrypi_ip:/usr/lib sysroot/usr
    rsync -avz pi@raspberrypi_ip:/opt/vc sysroot/opt

    wget https://raw.githubusercontent.com/riscv/riscv-poky/master/scripts/sysroot-relativelinks.py
    chmod +x sysroot-relativelinks.py
    ./sysroot-relativelinks.py sysroot

raspberrypi_ip is the network interface name or IP address of your Raspberry Pi.

##### Download Qt 
    wget http://download.qt.io/official_releases/qt/5.12/5.12.5/single/ qt-everywhere-src-5.12.5.tar.xz
    tar xvf  qt-everywhere-src-5.12.5.tar.xz
    cd  qt-everywhere-src-5.12.5
    
##### Configure Qt for cross compilation
EGL libraries have different names than those assumed in Qt configuration files, so edit the ./qtbase/mkspecs/devices/linux-rasp-pi-g++/qmake.conf file and substitute all references to -lEGL and -LGLESv2 for -lbrcmEGL and -lbrcmGLESv2, respectively. <br>

    ./configure -release -opengl es2 -device linux-rasp-pi-g++ -device-option CROSS_COMPILE=~/raspi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-     x64/bin/arm-linux-gnueabihf- -sysroot ~/raspi/sysroot -opensource -confirm-license -skip qtwayland -skip qtlocation -skip qtscript -make libs -prefix /usr/local/qt5pi -extprefix ~/raspi/qt5pi -hostprefix ~/raspi/qt5 -no-use-gold-linker -v -no-gbm
    
##### Compile, install and deploy Qt
    make
    make install
Once Qt is compiled, it can be deployed to your Raspberry Pi using the rsync command.
    rsync -avz qt5pi pi@raspberrypi_ip:/usr/local
##### Setup Qt Creator for Raspberry Pi cross compilation 
First, open Qt Creator, go to the ***Tools -> Options menu***, select the ***Devices*** section and ***Devices*** tab. Add a ***new Generic Linux Device***.
Set a name for the configuration ***(Raspberry Pi)***, the ***network name or IP***, the ***username (pi)*** and ***password (by default raspberry)***.
Next, go to the ***Kits*** section and ***Compilers*** tab, Add ***GCC C*** and ***C++*** cross compilers for Raspberry Pi.

The path for the GCC C Raspberry Pi compiler is 
    ~/raspi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/arm-linux-gnueabihf/bin/gcc.

The path for the GCC C++ Raspberry Pi compiler is the same as for the GCC C compiler.
Next, go to the ***Debuggers*** tab, and Add a debugger, set its path to 
    ~/raspi/tools/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/bin/arm-linux-gnueabihf-gdb.
Go to the ***Qt Versions*** tab and Add a new version: ***Qt 5.12 (Raspberry Pi)***, set the qmake path to
    ~/raspi/qt5/bin/qmake.
You can now design, build and deploy your Qt Raspberry Pi apps in you computer and, execute and debug them directly in your Raspberry Pi.

Enjoy!!!


