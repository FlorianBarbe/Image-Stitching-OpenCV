//
//  MyDescriptorExtractor.hpp
//  Features
//
//  Created by Jean-Marie Normand on 28/11/2017.
//  Copyright © 2017 Jean-Marie Normand. All rights reserved.
//

#ifndef MyDescriptorExtractor_hpp
#define MyDescriptorExtractor_hpp

#include <stdio.h>

#include <opencv2/features2d/features2d.hpp>


using namespace std;
using namespace cv;


// List of possible descriptors
#define _DESC_AKAZE        0
#define _DESC_BRISK        1
#define _DESC_MSER         2
#define _DESC_ORB          3
#define _NB_DESCRIPTORS    _DESC_ORB

class MyDescriptorExtractor {
   
private:
   // The actual descriptor extractor
   Ptr<DescriptorExtractor>   _myDescriptorExtractor;
   // the "type" of descriptor extractor
   int                        _myDescriptorExtractorMethod;
   
   // Storing the image (why?)
   Mat                        _myImage;
   
   // Storing the descriptors
   Mat                        _myDescriptors;
   
   // The keypoints we want to compute the descriptors
   vector< KeyPoint >         _myDetectedFeatures;
   
   
public:
   // Constructor (default)
   MyDescriptorExtractor();
   // Constructor by the name of the descriptor extractor
   MyDescriptorExtractor(int descriptorType);
   
   // Chaning the descriptor extractor
   void changeDescriptorExtractor(int descriptorType);
   
   // Setting the image (not sure why OpenCV needs it)
   void setImage(Mat img);
   
   // Setting the keypoints
   void setFeatures(vector<KeyPoint> features);
   
   // Compute the descriptors on the parameters keypoints
   Mat computeDescriptors(Mat image, vector<KeyPoint> features);
   
   // Compute the descriptors of the stored keypoints
   Mat computeDescriptors();
   
   // Return the descriptors (if computed)
   Mat getDescriptors();
   
   // Getting the descriptor type associated with the detector
   int getDescriptorExtractorMethod();

   // Getting the name of the detector given it's index
   const string getDescriptorExtractorName();
   
   // Getting the name of the detector given it's index
   static const string getDescriptorExtractorName(int descriptorType);
};

#endif /* MyDescriptorExtractor_hpp */
