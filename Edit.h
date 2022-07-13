#ifndef EDIT_H
#define EDIT_H
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include<QtMath>
#include<iostream>
#include <QColor>
#include<QtDebug>
#include <QElapsedTimer>

typedef struct RgbColor
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RgbColor;

typedef struct HsvColor
{
    unsigned char h;
    unsigned char s;
    unsigned char v;
} HsvColor;

RgbColor HsvToRgb(HsvColor hsv);
HsvColor RgbToHsv (RgbColor rgb);
void Brightness(QImage* inImage, int sliderPos);
void Contrast(QImage* inImage, int sliderPos);
void Color(QImage* inImage, int sliderPos);
void Hue(QImage* inImage, int sliderPos);
QImage Sharpness(QImage inImage, int sliderPos);
QImage Resize(QImage inImage, int sliderPos);
void brightnessIncrease(uchar* receivedbit,float factor);
void Convolution(QImage *inImage, QImage* outImage, double KernelMatrix[][3]);
double binaryMedian(int m[][3]);
void medianFilter(QImage *inImage, QImage* outImage);
void bilateralFilter(QImage *inImage, QImage* outImage, double KernelMatrix[][3]);


#endif // EDIT_H
