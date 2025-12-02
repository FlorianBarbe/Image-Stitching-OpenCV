//
//  MyFeatureDetector.cpp
//  Features
//
//  Created by Jean-Marie Normand on 28/11/2017.
//  Copyright © 2017 Jean-Marie Normand. All rights reserved.
//

#include "MyFeatureDetector.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d.hpp>
extern int g_numFeatures=500;

using namespace cv;

MyFeatureDetector::MyFeatureDetector() {
   changeFeatureDetector(_CORNER_ORB);
}

MyFeatureDetector::MyFeatureDetector(int detectorType) {
   changeFeatureDetector(detectorType);
}


void MyFeatureDetector::changeFeatureDetector(int detectorType){
   // First release the previous detector
   _myFeatureDetector.release();
   
   // and we store the method
   _myFeatureDetectorMethod = detectorType;
   
   // Depending on the detector type we will create the
   // correponsding corner detector
   switch (detectorType) {
         // ORB
      case _CORNER_ORB:
          // TODO : create detector
          _myFeatureDetector = ORB::create(g_numFeatures);

         // TODO store detector method
          _myFeatureDetectorMethod = _CORNER_ORB;
           
          break;
	  case _CORNER_FAST:
		  _myFeatureDetector = FastFeatureDetector::create();
		  _myFeatureDetectorMethod = _CORNER_FAST;

		  break;
	  case _CORNER_BRISK:
		  _myFeatureDetector = BRISK::create(10);
		  _myFeatureDetectorMethod = _CORNER_BRISK ;

		  break;


		   }
}


// Setting the  image
void MyFeatureDetector::setImage(cv::Mat image){
   _myImage = image.clone();
}

// Getters to the image
Mat MyFeatureDetector::getImage() {
   return _myImage;
}

// Detecting features in the image
void MyFeatureDetector::detectFeatures() {
   _myFeatures.clear();
   
   _myFeatureDetector->detect(_myImage,_myFeatures);
}

// Displaying features in the image (and returning a clone of this image)
Mat MyFeatureDetector::displayFeatures(Scalar rgb) {
   cv::Mat imgTmp = _myImage.clone();
   int r = 2;

   cout<<"** Number of features detected: "<<_myFeatures.size()<<endl;
   for(int i=0;i<_myFeatures.size();i++)
   {
      // Draw detected features
      cv::circle( imgTmp, _myFeatures[i].pt, r, rgb, -1, 8, 0 );
   }
   
   return imgTmp;
}


// Getters to the features
std::vector< KeyPoint > MyFeatureDetector::getFeatures() {
   return _myFeatures;
}

// Getting the current detection method used
int MyFeatureDetector::getFeatureDetectionMethod() {
   return _myFeatureDetectorMethod;
}


// Getting the name of the detector given it's index
const string MyFeatureDetector::getFeatureDetectorName() {
   return MyFeatureDetector::getFeatureDetectorName(_myFeatureDetectorMethod);
}

// Getting the name of the feature detector
const string MyFeatureDetector::getFeatureDetectorName(int detectorType) {
   string res;
   switch(detectorType) {
         //case _GFTT
      case _CORNER_GFTT:
         res = "GFTT";
         break;
         // HARRIS (it is a special configuration of the GFTT detector in OpenCV
      case _CORNER_HARRIS:
         res = "HARRIS";
         break;
         // MSER
      case _CORNER_MSER:
         res = "MSER";
         break;
         // FAST
      case _CORNER_FAST:
         res = "FAST";
         break;
         // AKAZE
      case _CORNER_AKAZE:
         res = "AKAZE";
         break;
         // BRISK
      case _CORNER_BRISK:
         res = "BRISK";
         break;
         // ORB
      case _CORNER_ORB:
         //default?
      default:
         res = "ORB";
         break;
   }
   
   return res;
}

cv::Ptr<cv::Feature2D> MyFeatureDetector::ORB_create()
{
	throw std::logic_error("The method or operation is not implemented.");
}
