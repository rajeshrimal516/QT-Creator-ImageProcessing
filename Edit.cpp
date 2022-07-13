#include "Edit.h"

QElapsedTimer timer;

using namespace std;

void Brightness(QImage* inImage, int sliderPos)
{
    uchar *inPixel = inImage->bits();
    int height = inImage->height();
    int width = inImage->width();
    int rowIdx, colIdx,pixel_index;
    double R,G,B;
    double factor = sliderPos*2.0;
    timer.start();
    for(rowIdx = 0; rowIdx < width; rowIdx++)
    {
        for(colIdx = 0; colIdx < height; colIdx++)
        {
            pixel_index = 4 * rowIdx + 4 * width * colIdx;

            B = inPixel[pixel_index + 0 ] + factor;
            G = inPixel[pixel_index + 1 ] + factor;
            R = inPixel[pixel_index + 2 ] + factor;

            B = (B>255)?255:((B<0)?0:B);
            G = (G>255)?255:((G<0)?0:G);
            R = (R>255)?255:((R<0)?0:R);

            inPixel[pixel_index + 0 ] = B;
            inPixel[pixel_index + 1 ] = G;
            inPixel[pixel_index + 2 ] = R;
        }
    }
    qDebug()<<"Brightness Loop Exectuion Time: "<< timer.elapsed()<<endl;
}

void Contrast (QImage* inImage, int sliderPos)
{
    uchar *inPixel = inImage->bits();
    int height = inImage->height();
    int width = inImage->width();
    int rowIdx, colIdx,pixel_index;
    double R,G,B;
    double factor = (double)(259*(255+(sliderPos)))/(255*(259-(sliderPos)));
    timer.start();
    for(rowIdx = 0; rowIdx < height; rowIdx++)
    {
        for(colIdx = 0; colIdx < width;colIdx++)
        {
            pixel_index =  4* colIdx + 4*width * rowIdx;


           B = inPixel[pixel_index + 0 ];
           G = inPixel[pixel_index + 1 ];
           R = inPixel[pixel_index + 2 ];

           B = factor * (B-128) + 128;
           G = factor * (G-128) + 128;
           R = factor * (R-128) + 128;

           B = (B>255)?255:((B<0)?0:B);
           G = (G>255)?255:((G<0)?0:G);
           R = (R>255)?255:((R<0)?0:R);

          inPixel[pixel_index + 0 ] = B;
          inPixel[pixel_index + 1 ] = G;
          inPixel[pixel_index + 2 ] = R;
          }
    }
    qDebug()<<"Contrast Loop Exectuion Time: "<< timer.elapsed()<<endl;
}

void Color(QImage* inImage, int sliderPos)
{
    uchar *inPixel = inImage->bits();
    int height = inImage->height();
    int width = inImage->width();
    int rowIdx, colIdx,pixel_index;
    float factor = (float)(1 + (float)sliderPos/(100));
    RgbColor rgb;
    HsvColor hsv;
    timer.start();
    for(rowIdx = 0; rowIdx < width; rowIdx++)
    {
        for(colIdx = 0; colIdx < height;colIdx++)
        {
            pixel_index = 4*rowIdx + 4*width*colIdx;
            rgb.b = inPixel[pixel_index + 0 ];
            rgb.g = inPixel[pixel_index + 1 ];
            rgb.r = inPixel[pixel_index + 2 ];
            hsv = RgbToHsv(rgb);
            float satValue = hsv.s*factor;
            if (satValue>255) satValue=255;
            hsv.s = satValue;
            rgb= HsvToRgb( hsv);
            inPixel[pixel_index + 0 ] = rgb.b;
            inPixel[pixel_index + 1 ] = rgb.g;
            inPixel[pixel_index + 2 ] = rgb.r;
        }
    }
     qDebug()<<"Color Loop Exectuion Time: "<< timer.elapsed()<<endl;
}

void Hue(QImage* inImage, int sliderPos)
{
    uchar *inPixel = inImage->bits();
    int height = inImage->height();
    int width = inImage->width();
    int rowIdx, colIdx,pixel_index;
    float factor = (float)(1 + (float)sliderPos/(100));
    RgbColor rgb;
    HsvColor hsv;
    timer.start();
    for(rowIdx = 0; rowIdx < width; rowIdx++)
    {
        for(colIdx = 0; colIdx < height;colIdx++)
        {
            pixel_index = 4*rowIdx + 4*width*colIdx;
            rgb.b = inPixel[pixel_index + 0 ];
            rgb.g = inPixel[pixel_index + 1 ];
            rgb.r = inPixel[pixel_index + 2 ];
            hsv = RgbToHsv(rgb);
            float HueValue = hsv.h*factor;
            if (HueValue>255) HueValue=255;
            hsv.h = HueValue;
            rgb= HsvToRgb( hsv);
            inPixel[pixel_index + 0 ] = rgb.b;
            inPixel[pixel_index + 1 ] = rgb.g;
            inPixel[pixel_index + 2 ] = rgb.r;
        }
    }
     qDebug()<<"Hue Loop Exectuion Time: "<< timer.elapsed()<<endl;
}

QImage Sharpness(QImage inImage, int sliderPos)
{
    int height = inImage.height();
    int width = inImage.width();
    QImage outImage = QImage(width,height,inImage.format());
    timer.start();
    if (sliderPos >0)
    {
        if(sliderPos<15)
        {
            double sharpenKernel[3][3] = {{0,-1,0} , {-1,5.0,-1} , {0,-1,0} };
            Convolution(&inImage,&outImage,sharpenKernel);}
        if(sliderPos>=15 && sliderPos<30)
        {
            double sharpenKernel[3][3] = {{0,-2,0} , {-2,9.0,-2} , {0,-2,0} };
            Convolution(&inImage,&outImage,sharpenKernel);}
        if(sliderPos>=30 && sliderPos<45)
        {
            double sharpenKernel[3][3] = {{-1,-1,-1} , {-1,9.0,-1} , {-1,-1,-1} };
            Convolution(&inImage,&outImage,sharpenKernel);}
        if(sliderPos>=45 && sliderPos<60)
        {
            double sharpenKernel[3][3] = {{0,-3,0} , {-3,13.0,-3} , {0,-3,0} };
            Convolution(&inImage,&outImage,sharpenKernel);}
        if(sliderPos>=60 && sliderPos<=75)
           {
            double sharpenKernel[3][3] = {{-2,-2,-2} , {-2,17.0,-2} , {-2,-2,-2} };
            Convolution(&inImage,&outImage,sharpenKernel);}
        if(sliderPos>75 && sliderPos<=90)
             {
            double sharpenKernel[3][3] = {{-3,-3,-3} , {-3,25.0,-3} , {-3,-3,-3} };
            Convolution(&inImage,&outImage,sharpenKernel);}
        if(sliderPos>90)
        {
            double sharpenKernel[3][3] = {{-4,-4,-4} , {-4,33.0,-4} , {-4,-4,-4} };
            Convolution(&inImage,&outImage,sharpenKernel);}

    }
    else if (sliderPos < 0)
    {
        double kernelSum =0,sum=0 ;
        double factor = (double)(1 - (double)sliderPos/(10));
        double stdv = factor;
        double expNumerator = 0;
        double expDenominator = 2.0 * stdv * stdv;
        double Numerator = 0;
        double Denominator = M_PI * expDenominator;
        double blurKernel[3][3];
        double blurKernel1D[9] = { 0 };

        for (int x = -1; x <= 1; x++)
               {
                   for (int y = -1; y <=1; y++)
                   {
                       expNumerator = (double)(x*x + y*y);
                       Numerator = (double)1/exp((expNumerator / expDenominator));
                       blurKernel[x + 1][y + 1] = (double)(Numerator / Denominator);
                       kernelSum += blurKernel[x +1][y + 1];
                   }
               }
               for (int i = 0; i < 3; i++)
               {
                   printf("[");
                   for (int j = 0; j < 3; j++)
                   {
                       blurKernel[i][j] /= kernelSum;
                       printf("%.8lf\t", blurKernel[i][j]);
                       sum += blurKernel[i][j];
                   }
                   printf("]\n");
               }
               printf("Sum: %lf, %lf", kernelSum, sum);

            /*for (int x = 0; x < 9; x++)
            {
                expNumerator = (double)pow((x - 4), 2);
                blurKernel1D[x] = exp(-(expNumerator / expDenominator));
                sum += blurKernel1D[x];
            }
            for (int j = 0; j < 9; j++)
            {
                blurKernel1D[j] /= sum;
                kernelSum += blurKernel1D[j];
            }

            printf("Sum: %lf ,KernelSum: %lf\n", sum,kernelSum);

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    blurKernel[i][j] = blurKernel1D[(i * 3) + j];
                    printf("%0.12lf\t", blurKernel[i][j]);
                }
                printf("\n");
            }*/

        cout<< "Slider Pos: "<<sliderPos<<"  Standard Dev: "<<factor<<endl;
        Convolution(&inImage,&outImage,blurKernel);
    }
    else
    {
        outImage = inImage;
    }
        printf("\n");
     cout<<"Sharpness/Blur Loop Exectuion Time: "<< timer.elapsed()<<endl;
    return outImage;
}

QImage Resize(QImage inImage, int sliderPos)
{
    uchar *inPixel = inImage.bits();
    int height = inImage.height();
    int width = inImage.width();
    if(sliderPos==-100) sliderPos = -99;
    double factor=(double)(1 + (double)sliderPos/(100));
    int newheight=height*factor;
    int newwidth=width*factor;
    QImage outImage= QImage(newwidth,newheight,inImage.format());
    uchar *outPixel = outImage.bits();
    double rowRatio = (double) height/newheight;
    double columnRatio = (double) width/newwidth;
    int px,py;
    int position;
    int pixel_index;
    timer.start();
    for(int rowIdx= 0; rowIdx < newwidth; rowIdx++)
    {
        for(int colIdx= 0; colIdx< newheight; colIdx++)
        {
            px = (int) floor((double) rowRatio*rowIdx );
            py = (int) floor((double) columnRatio*colIdx);
            pixel_index = 4*rowIdx + 4*newwidth*colIdx;
            position = 4*px + 4*width*py;
            outPixel[pixel_index+0] =  inPixel[position + 0];
            outPixel[pixel_index+1] =  inPixel[position + 1];
            outPixel[pixel_index+2] =  inPixel[position + 2];
        }
    }
     qDebug()<<"Resize Loop Exectuion Time: "<< timer.elapsed()<<endl;
    return outImage;
}

/*double binaryMedian(int m[][3])
{
    double min = 0, max = 255;
    for (int i=0; i<3; i++)
    {
        if (m[i][0] < min)
            min = m[i][0];
        if (m[i][3-1] > max)
            max = m[i][3-1];
    }
    double desired = (3 * 3 + 1) / 2;
    while (min < max)
    {
        int mid = min + (max - min) / 2;
        int place = 0;
        for (int i = 0; i < 3; ++i)
            place += upper_bound(m[i], m[i]+3, mid) - m[i];
        if (place < desired)
            min = mid + 1;
        else
            max = mid;
    }
    return min;
}

void medianFilter(QImage *inImage, QImage* outImage)
{
    uchar *inPixel = inImage->bits();
    int height = inImage->height();
    int width = inImage->width();
    int pixel_index,position;
    int rowIdx, colIdx;
    uchar *final = outImage->bits();
    int matrixR[3][3];
    int matrixG[3][3];
    int matrixB[3][3];
    for(rowIdx = 0; rowIdx < width-1; rowIdx++)
    {
        for(colIdx = 0; colIdx < height-1;colIdx++)
        {
            for(int p=-1;p<2;p++)
            {
                for(int q=-1;q<2;q++)
                {
                    pixel_index = 4*(rowIdx+p) + 4*width*(colIdx+q);
                    matrixR[p+1][q+1]=  inPixel[pixel_index + 2 ];
                    matrixG[p+1][q+1]=  inPixel[pixel_index + 1 ];
                    matrixB[p+1][q+1]=  inPixel[pixel_index + 0 ];
                }
            }
                double medianR = binaryMedian(matrixR);
                double medianG = binaryMedian(matrixG);
                double medianB = binaryMedian(matrixB);
                position = 4*rowIdx + 4*width*colIdx;
                final[position + 0 ]= medianB;
                final[position + 1 ]= medianG;
                final[position + 2 ]= medianR;
        }
    }
}*/

void Convolution(QImage *inImage, QImage* outImage, double KernelMatrix[][3])
{
    uchar *inPixel = inImage->bits();
    int height = inImage->height();
    int width = inImage->width();
    int pixel_index,position;
    uchar *outPixel = outImage->bits();
    int KernelSum =0;
    int rowIdx, colIdx;
    int matrix[3][3][3];
    double sumr=0;
    double sumg=0;
    double sumb=0;
    for (int i = 0; i<3;i++){
        for(int j =0;j<3;j++)
            {
                KernelSum = KernelSum + KernelMatrix[i][j];
            }
        }

    for(rowIdx = 1; rowIdx < width; rowIdx++)
    {
        for(colIdx = 1; colIdx < height;colIdx++)
        {

            for(int p=-1;p<2;p++)
            {
                for(int q=-1;q<2;q++)
                {
                    pixel_index = 4*(rowIdx+p) + 4*width*(colIdx+q);
                    matrix[p+1][q+1][2]=  inPixel[pixel_index + 2 ];
                    matrix[p+1][q+1][1]=  inPixel[pixel_index + 1 ];
                    matrix[p+1][q+1][0]=  inPixel[pixel_index + 0 ];
                }
            }
                sumr=0,sumg=0, sumb=0;
                for(int p=0; p<3; p++)
                {
                    for(int q=0; q<3; q++)
                    {
                        sumr +=matrix[p][q][2] * KernelMatrix[p][q];
                        sumg +=matrix[p][q][1] * KernelMatrix[p][q];
                        sumb +=matrix[p][q][0] * KernelMatrix[p][q];
                    }
                }
                sumb = (sumb>255)?255:((sumb<0)?0:sumb);
                sumg = (sumg>255)?255:((sumg<0)?0:sumg);
                sumr = (sumr>255)?255:((sumr<0)?0:sumr);
                position = 4*rowIdx + 4*width*colIdx;
                outPixel[position + 0 ]= sumb;
                outPixel[position + 1 ]= sumg;
                outPixel[position + 2 ]= sumr;
       }
    }
}

void bilateralFilter(QImage *inImage, QImage* outImage, double KernelMatrix[][3])
{
    uchar *inPixel = inImage->bits();
    int height = inImage->height();
    int width = inImage->width();
    int pixel_index,position;
    int rowIdx, colIdx;
    uchar *final = outImage->bits();

    int matrix[3][3][3];
    double sumr=0;
    double sumg=0;
    double sumb=0;

    for(rowIdx = 0; rowIdx < width-1; rowIdx++)
    {
        for(colIdx = 0; colIdx < height-1;colIdx++)
        {
            for(int p=-1;p<2;p++)
            {
                for(int q=-1;q<2;q++)
                {
                    pixel_index = 4*(rowIdx+p) + 4*width*(colIdx+q);
                    matrix[p+1][q+1][2]=  inPixel[pixel_index + 2 ];
                    matrix[p+1][q+1][1]=  inPixel[pixel_index + 1 ];
                    matrix[p+1][q+1][0]=  inPixel[pixel_index + 0 ];
                }
            }
                sumr=0,sumg=0, sumb=0;
                for(int p=0; p<3; p++)
                {
                    for(int q=0; q<3; q++)
                    {
                        sumr +=matrix[p][q][2] * KernelMatrix[p][q];
                        sumg +=matrix[p][q][1] * KernelMatrix[p][q];
                        sumb +=matrix[p][q][0] * KernelMatrix[p][q];
                    }
                }


                sumr=sumr/9;
                sumg=sumg/9;
                sumb=sumb/9;

                sumb = (sumb>255)?255:((sumb<0)?0:sumb);
                sumg = (sumg>255)?255:((sumg<0)?0:sumg);
                sumr = (sumr>255)?255:((sumr<0)?0:sumr);

                position = 4*rowIdx + 4*width*colIdx;
                final[position + 0 ]= sumb;
                final[position + 1 ]= sumg;
                final[position + 2 ]= sumr;
       }
    }
}

RgbColor HsvToRgb(HsvColor hsv)
{
    RgbColor rgb;
    unsigned char region, p, q, t;
    unsigned int h, s, v, remainder;
    hsv.h = hsv.h - 86;
    if (hsv.s == 0)
    {
        rgb.r = hsv.v;
        rgb.g = hsv.v;
        rgb.b = hsv.v;
        return rgb;
    }

    h = hsv.h;
    s = hsv.s;
    v = hsv.v;
    region = h / 43;
    remainder = (h - (region * 43)) * 6;
    p = (v * (255 - s)) >> 8;
    q = (v * (255 - ((s * remainder) >> 8))) >> 8;
    t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;
    switch (region)
    {
        case 0:
            rgb.r = v;
            rgb.g = t;
            rgb.b = p;
            break;
        case 1:
            rgb.r = q;
            rgb.g = v;
            rgb.b = p;
            break;
        case 2:
            rgb.r = p;
            rgb.g = v;
            rgb.b = t;
            break;
        case 3:
            rgb.r = p;
            rgb.g = q;
            rgb.b = v;
            break;
        case 4:
            rgb.r = t;
            rgb.g = p;
            rgb.b = v;
            break;
        default:
            rgb.r = v;
            rgb.g = p;
            rgb.b = q;
            break;
    }
    return rgb;
}

HsvColor RgbToHsv(RgbColor rgb)
{
    HsvColor hsv;
    double rgbMin, rgbMax;

    rgbMin = min(rgb.r,min(rgb.g,rgb.b));
    rgbMax = max(rgb.r,max(rgb.g,rgb.b));

    hsv.v = rgbMax;
    if (hsv.v == 0)
    {
        hsv.h = 0;
        hsv.s = 0;
        return hsv;
    }

    hsv.s = 255 * ((double)(rgbMax - rgbMin)) / hsv.v;
    if (hsv.s == 0)
    {
        hsv.h = 0;
        return hsv;
    }

    if (rgbMax == rgb.r)
        hsv.h = 0 + 43 *(double) (rgb.g - rgb.b) / (rgbMax - rgbMin);
    else if (rgbMax == rgb.g)
        hsv.h = 85 + 43 * (double)(rgb.b - rgb.r) / (rgbMax - rgbMin);
    else
        hsv.h = 171 + 43 * (double)(rgb.r - rgb.g) / (rgbMax - rgbMin);
    hsv.h = hsv.h + 86;
    return hsv;
}

/*{
    uchar *inPixel = received.inPixels();
    int height = received.height();
    int width = received.width();
    int rowIdx, colIdx=0;
    int i,j;
    double factor = sliderPos*2.0;
    timer.start();
    for(rowIdx = 0; rowIdx < width/4;rowIdx= rowIdx+1)
    {
       for(colIdx = 0; colIdx < height/4; colIdx= colIdx+1)
        {
            i=4*rowIdx; j = 4*colIdx;
            brightnessIncrease(&inPixel[4 * i + 4 * width *j],factor);
            brightnessIncrease(&inPixel[4 * i + 4 * width * (j+1)],factor);
            brightnessIncrease(&inPixel[4 * i + 4 * width * (j+2)],factor);
            brightnessIncrease(&inPixel[4 * i + 4 * width * (j+3)],factor);

            brightnessIncrease(&inPixel[4 * (i+1) + 4 * width *j],factor);
            brightnessIncrease(&inPixel[4 * (i+1) + 4 * width * (j+1)],factor);
            brightnessIncrease(&inPixel[4 * (i+1) + 4 * width * (j+2)],factor);
            brightnessIncrease(&inPixel[4 * (i+1) + 4 * width * (j+3)],factor);

            brightnessIncrease(&inPixel[4 * (i+2) + 4 * width *j],factor);
            brightnessIncrease(&inPixel[4 * (i+2) + 4 * width * (j+1)],factor);
            brightnessIncrease(&inPixel[4 * (i+2) + 4 * width * (j+2)],factor);
            brightnessIncrease(&inPixel[4 * (i+2) + 4 * width * (j+3)],factor);

            brightnessIncrease(&inPixel[4 * (i+3) + 4 * width *j],factor);
            brightnessIncrease(&inPixel[4 * (i+3) + 4 * width * (j+1)],factor);
            brightnessIncrease(&inPixel[4 * (i+3) + 4 * width * (j+2)],factor);
            brightnessIncrease(&inPixel[4 * (i+3) + 4 * width * (j+3)],factor);

        }
    }
   qDebug() << "Slider Pos: "<<sliderPos<<"  Brightness Loop Execution Time" << timer.elapsed() << "milliseconds";
    return received;


    float R,G,B;
    B =  *(receivedinPixel+0) + factor;
    G =  *(receivedinPixel+1)+ factor;
    R =  *(receivedinPixel+2)+ factor;
    B = (B>255)?255:((B<0)?0:B);
    G = (G>255)?255:((G<0)?0:G);
    R = (R>255)?255:((R<0)?0:R);
     *(receivedinPixel+0)= B;
     *(receivedinPixel+1)= G;
     *(receivedinPixel+2)= R;*/

