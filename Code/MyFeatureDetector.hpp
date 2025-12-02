//
//  MyFeatureDetector.hpp
//  Features
//
//  Created by Jean-Marie Normand on 28/11/2017.
//  Copyright © 2017 Jean-Marie Normand. All rights reserved.
//

#ifndef MyFeatureDetector_hpp
#define MyFeatureDetector_hpp

#include <stdio.h>
#include <iostream>

#include <opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;

// Corner detectors we could use
#define _CORNER_GFTT     0
#define _CORNER_HARRIS   1
#define _CORNER_MSER     2
#define _CORNER_FAST     3
#define _CORNER_ORB      4
#define _CORNER_AKAZE    5
#define _CORNER_BRISK    6
#define _NB_CORNER_DETECTORS  _CORNER_BRISK


// The following detectors are NOT free
/*
#define _SIFT
#define _SURF
#define _BRIEF
*/

class MyFeatureDetector {
private:
   // We want to be able to represent different types of detectors
   Ptr<Feature2D> _myFeatureDetector;
   // we store the method used to detect points
   int _myFeatureDetectorMethod;
   
   // We store the  image on which we want to detect points
   Mat   _myImage;
   
   // Features in the image _myImage
  	std::vector< KeyPoint > _myFeatures;
   
public:
   
   // Constructors
   MyFeatureDetector();
   MyFeatureDetector(int detectorType);
   
   // Reallocate a new detector
   // to be able to change at runtime
   void changeFeatureDetector(int detectorType);
   
   // Setting the image
   void setImage(cv::Mat image);
   
   // Getter to the images
   Mat getImage();
   
   // Detecting features in the image
   void detectFeatures();
   
   // Getters to the features
   std::vector< KeyPoint > getFeatures();
   
   // Displaying the features in the image (and returning a clone of this image)
   Mat displayFeatures(Scalar rgb=Scalar(0,0,255));
   
   // Getting the current detection method used
   int getFeatureDetectionMethod();
   
   // Getting the name of the detector given it's index
   const string getFeatureDetectorName();
   
   // Getting the name of the detector given it's index
   static const string getFeatureDetectorName(int detectorType);

private:
	Ptr<Feature2D> ORB_create();
};


#endif /* FeatureDetector_hpp */
