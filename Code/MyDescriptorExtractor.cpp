//
//  MyDescriptorExtractor.cpp
//  Features
//
//  Created by Jean-Marie Normand on 28/11/2017.
//  Copyright © 2017 Jean-Marie Normand. All rights reserved.
//

#include "MyDescriptorExtractor.hpp"

MyDescriptorExtractor::MyDescriptorExtractor() {
   changeDescriptorExtractor(_DESC_ORB);
}

MyDescriptorExtractor::MyDescriptorExtractor(int descriptorType) {
   changeDescriptorExtractor(descriptorType);
}

void MyDescriptorExtractor::changeDescriptorExtractor(int descriptorType) {
   // First release the previous detector
   _myDescriptorExtractor.release();
   
   // and we store the method
   _myDescriptorExtractorMethod = descriptorType;
   
   // Creating the new descriptor extractor based on the type
   switch (descriptorType) {
      
      // ORB (feature descriptor)
      // + default
      case _DESC_ORB:
      default:
         // TODO create descriptor
		 _myDescriptorExtractor = ORB::create();
         // TODO store descriptor name
		 _myDescriptorExtractorMethod = _DESC_ORB;   

         break;
        case _DESC_BRISK:
         _myDescriptorExtractor = BRISK::create();
		 _myDescriptorExtractorMethod = _DESC_BRISK;

		 break;
   }
   
}

// Setting the image (not sure why OpenCV needs it)
void MyDescriptorExtractor::setImage(Mat img) {
   _myImage = img.clone();
}

// Setting the features
void MyDescriptorExtractor::setFeatures(vector<KeyPoint> features) {
   _myDetectedFeatures = features;
}

// Compute the descriptors on the features given as parameters
Mat MyDescriptorExtractor::computeDescriptors(Mat image, vector<KeyPoint> features) {
   this->setImage(image);
   this->setFeatures(features);
   return this->computeDescriptors();
}

// Compute the descriptors of the stored features
Mat MyDescriptorExtractor::computeDescriptors() {
   
   // TODO compute descriptors!
	_myDescriptorExtractor->compute(_myImage, _myDetectedFeatures, _myDescriptors);

   
   return this->getDescriptors();
}

// Return the descriptors (if computed)
Mat MyDescriptorExtractor::getDescriptors() {
   return _myDescriptors;
}

// Getting the current descriptor extractor method used
int MyDescriptorExtractor::getDescriptorExtractorMethod() {
   return _myDescriptorExtractorMethod;
}

// Getting the name of the detector given it's index
const string MyDescriptorExtractor::getDescriptorExtractorName() {
   return MyDescriptorExtractor::getDescriptorExtractorName(_myDescriptorExtractorMethod);
}

// Getting the name of the detector given it's index
const string MyDescriptorExtractor::getDescriptorExtractorName(int descriptorType) {
   string res;
   switch(descriptorType) {
         // MSER
      case _DESC_MSER:
         res = "MSER";
         break;
         // ORB
      case _DESC_ORB:
         res = "ORB";
         break;
         // AKAZE
      case _DESC_AKAZE:
         res = "AKAZE";
         break;
         // BRISK
      case _DESC_BRISK:
         res = "BRISK";
         break;
         //default?
      default:
         res="BRISK";
         break;
   }
   
   return res;
}
