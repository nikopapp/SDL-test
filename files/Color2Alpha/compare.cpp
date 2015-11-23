/////////////////////////////////////////////////////////////////////////////
//
//   Compare RGBA
//
/////////////////////////////////////////////////////////////////////////////

// header inclusion
#include <stdio.h>
#include "openCV.h"

using namespace cv;

int main( int argc, char** argv )
{

 // LOADING THE IMAGE
 char* imageName1 = argv[1];
 char* imageName2 = argv[2];

 Mat image1;
 Mat image2;

 image1 = imread( imageName1, -1 );
 image2 = imread( imageName2, -1 );

 if( argc != 3 || !image1.data || !image2.data )
 {
   printf( " No image data \n " );
   return -1;
 }
int Temp[image1.rows][image1.cols];

 // THRESHOLD BY LOOPING THROUGH ALL PIXELS
 for(int i=0; i<image1.rows; i++) {
   for(int j=0; j<image1.cols; j++) {
     uchar pixelBlue1 = image1.at<Vec3b>(i,j)[0];
     uchar pixelGreen1 = image1.at<Vec3b>(i,j)[1];
     uchar pixelRed1 = image1.at<Vec3b>(i,j)[2];
     uchar pixelBlue2 = image2.at<Vec3b>(i,j)[0];
     uchar pixelGreen2 = image2.at<Vec3b>(i,j)[1];
     uchar pixelRed2 = image2.at<Vec3b>(i,j)[2];

   }
 }
printf("%5c%5c%5c%5c--------",'R','G','B','A' );
printf("%c%5c%5c%5c\n",'R','G','B','A' );
 for(int i=0; i<10; i++) {
   for(int j=0; j<10; j++) {
          uchar pixelRed1 = image1.at<Vec3b>(i,j)[2];
          uchar pixelRed2 = image2.at<Vec3b>(i,j)[2];
printf("%5d%5d%5d%5d      ",
image1.at<Vec3b>(i,j)[2],image1.at<Vec3b>(i,j)[1],image1.at<Vec3b>(i,j)[0],image1.at<Vec3b>(i,j)[3] );
printf("%3d%5d%5d%5d---------%3d\n",
image2.at<Vec3b>(i,j)[2],image2.at<Vec3b>(i,j)[1],image2.at<Vec3b>(i,j)[0],image2.at<Vec3b>(i,j)[3],pixelRed2-pixelRed1 );


     }


   }
   namedWindow( "Image 1", CV_WINDOW_AUTOSIZE );
   moveWindow("Image 1",0,0);
   imshow( "Image 1", image1 );
   namedWindow( "Image 2", CV_WINDOW_AUTOSIZE );
   moveWindow("Image 2",image1.cols+50,0);
   imshow( "Image 2", image2 );
   waitKey(0);
 // imwrite( outputName, image1 );

 return 0;
}
