//
//  main.h
//  Features
//
//  Created by Jean-Marie Normand on 28/11/2017.
//  Copyright © 2017 Jean-Marie Normand. All rights reserved.
//

#ifndef main_h
#define main_h

#include <string.h>
#include <iostream>
#include <opencv2/core/core.hpp>

#include "MyFeatureDetector.hpp"
#include "MyDescriptorExtractor.hpp"
#include "MyDescriptorMatcher.hpp"

using namespace std;
using namespace cv;

// Names of the images
#define DEFAULT_IMG_NAME1 "C:\\Users\\flole\\Desktop\\CENTRALE\\VSION\\TP_Stitching\\IMG_1_reduced.jpg"
#define DEFAULT_IMG_NAME2 "C:\\Users\\flole\\Desktop\\CENTRALE\\VSION\\TP_Stitching\\IMG_2_reduced.jpg"

#define ESC_KEY   27

// Global variables

// The feature detector
MyFeatureDetector _myFeatureDetector1;
MyFeatureDetector _myFeatureDetector2;
int               _myFeatureDetectorMethod1;
int               _myFeatureDetectorMethod2;

// images
Mat im1, im2;
Mat imKP1, imKP2;

// The Ptr<descriptor extractor
MyDescriptorExtractor _myFeatureExtractor1;
MyDescriptorExtractor _myFeatureExtractor2;
int _myFeatureExtractorMethod1;
int _myFeatureExtractorMethod2;

// Descriptors
Mat descr1, descr2;


// MATCHING
// The descriptor matcher
MyDescriptorMatcher  _myDescriptorMatcher;
// the descriptor method
int                  _myMatchingMethod;

// Max and min distances between the matches
double              _matchingMaxDist;
double              _matchingMinDist;

// Storing the matches
vector<DMatch>       _myMatches;
vector<DMatch>       _myBestMatches;

// Image to display the matching result
Mat                  matchingResult;
Mat                  homography;

// Resized image (testing purpose)
Mat resizedColorimage;

// Storing the keypressed by the user (ESC to quit)
int retK;

#endif /* main_h */
