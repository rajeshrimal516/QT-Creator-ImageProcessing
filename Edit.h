/*********************************************************************************
 * @file Edit.h
 * @author Rajesh Rimal (rajeshrimal516@gmail.com)
 * @brief Header file for the image propcessing functions in Edit.cpp
 * @version 0.1
 * @date 2022-07-14
 *
 * @copyright Copyright (c) 2022
 * 
 ********************************************************************************/

#ifndef EDIT_H
#define EDIT_H

#include <QMainWindow>
#include <QtMath>
#include <iostream>
#include <QColor>
#include <QtDebug>
#include <QElapsedTimer>

#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * @brief structure for R, G, B values.
 */
typedef struct RgbColor
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RgbColor;

/**
 * @brief structure for H, S, V values.
 */
typedef struct HsvColor
{
    unsigned char h;
    unsigned char s;
    unsigned char v;
} HsvColor;


/**
 * @brief Function for conversion of HSV to RGB
 * 
 * @param hsv structure with H, S and V value
 * @return RgbColor structure with R, G and B value
*/
RgbColor HsvToRgb(HsvColor hsv);

/**
 * @brief Function for conversion of RGB to HSV
 * 
 * @param rgb RgbColor structure with R, G and B value
 * @return HSV structure with H, S, and V value
*/
HsvColor RgbToHsv (RgbColor rgb);

/**
 * @brief Function for changing the brightness in the image
 *
 * @param [in,out] inImage Image in QImage format
 * @param [in] sliderPos Position of the slider from (-100 to 100)
 */
void Brightness(QImage* inImage, int sliderPos);

/**
 * @brief Function for changing the contrast in the image
 * 
 * @param [in,out] inImage Image in QImage format 
 * @param [in] sliderPos Position of the slider from (-100 to 100)
 */

void Contrast(QImage* inImage, int sliderPos);\

/**
 * @brief Function for changing the color in the image
 * 
 * @param [in,out] inImage Image in QImage format 
 * @param [in] sliderPos Position of the slider from (-100 to 100)
*/
void Color(QImage* inImage, int sliderPos);


/**
 * @brief Function for changing the hue in the image
 * 
 * @param [in,out] inImage Image in QImage format 
 * @param [in] sliderPos Position of the slider from (-100 to 100)
*/ 

void Hue(QImage* inImage, int sliderPos);


/**
 * @brief Function for sharpning or bluring the image
 * 
 * @param [in] inImage Image in QImage format 
 * @param [in] sliderPos Position of the slider from (-100 to 100)
 * @return sharpened or blurred image in QImage format
*/
QImage Sharpness(QImage inImage, int sliderPos);


/**
 * @brief Function for resizing the slide of the image
 * 
 * @param [in] inImage Image in QImage format 
 * @param [in] sliderPos Position of the slider from (-100 to 100)
 * @return resized image in QImage format
*/
QImage Resize(QImage inImage, int sliderPos);

/**
 * @brief Function for performing the convolution in the image
 * 
 * @param [in] inImage Image in QImage format
 * @param [out] outImage Image in QImage format 
 * @param KernelMatrix kernel matrix for convolution (3x3)
*/
void Convolution(QImage *inImage, QImage *outImage, double KernelMatrix[][3]);

#endif // EDIT_H
