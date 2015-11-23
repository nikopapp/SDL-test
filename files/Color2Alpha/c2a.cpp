/////////////////////////////////////////////////////////////////////////////
//
//       Process  makes a color transparent
//
//
//
/////////////////////////////////////////////////////////////////////////////

// header inclusion
#include <stdio.h>
#include <stdlib.h>
#include "openCV.h"

#define W 512
#define H 512

#define MAX_V 255

using namespace cv;

int intSwap(int value);
int invertColor(int value);

int main( int argc, char** argv )
{

 // LOADING THE IMAGE
 char* imageName = argv[1];
 char* outputName = argv[2];
 int a=0;
 Mat image;
 image = imread( imageName );
 int temp[image.rows][image.cols];

 if( argc != 3 || !image.data )
 {
   printf( " No image data \n " );
   return -1;
 }
 // THRESHOLD BY LOOPING THROUGH ALL PIXELS
 for(int i=0; i<image.rows; i++) {
   for(int j=0; j<image.cols; j++) {
       uchar pixelBlue = image.at<Vec3b>(i,j)[0];
       uchar pixelGreen = image.at<Vec3b>(i,j)[1];
       uchar pixelRed = image.at<Vec3b>(i,j)[2];
       uchar pixelAlpha = image.at<Vec3b>(i,j)[3];
     if(pixelGreen>140&&pixelBlue>10&&pixelRed>130)
   image.at<Vec3b>(i,j)[3] =255;

   }
 }

namedWindow( "Display window", WINDOW_AUTOSIZE );
 imshow("Display window", image);
 printf("Image displayed...\n");
 //wait till key is pressed
 printf("PRESS A KEY NOW...\n");
 cvWaitKey();
 imwrite( outputName, image );

 return 0;
}

int intSwap(int value)
{
  if(value>MAX_V/2){
  value=MAX_V/2-value;

  }
  if(value<MAX_V/2){
  value=MAX_V-value;
  }
   return (value);
}

int invertColor(int value)
{
   value=MAX_V-value;
   return (value);
}
