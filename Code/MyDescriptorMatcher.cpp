//
//  MyDescriptorMatcher.cpp
//  Features
//
//  Created by Jean-Marie Normand on 28/11/2017.
//  Copyright © 2017 Jean-Marie Normand. All rights reserved.
//

#include "MyDescriptorMatcher.hpp"
#include <iostream>

// Constructors
// note that NOT every matcher can be used with every descriptor

MyDescriptorMatcher::MyDescriptorMatcher() {
   // First release the previous detector
   _myDescriptorMatcher.release();
   // Create a brute force matcher
   _myDescriptorMatcher = DescriptorMatcher::create("BruteForce");
   _myDescriptorMatchedMethod = _BRUTE_FORCE;
}


MyDescriptorMatcher::MyDescriptorMatcher(int matcherType, int colorDescriptorType, int colorDescriptorDefaultNorm, int thermalDescriptorType, int thermalDescriptorDefaultNorm) {
   changeMatchingMethod(matcherType, colorDescriptorType, colorDescriptorDefaultNorm, thermalDescriptorType, thermalDescriptorDefaultNorm);
}



// Changing the current matching method
void MyDescriptorMatcher::changeMatchingMethod(int matcherType) {
   
   // First release the previous detector
   _myDescriptorMatcher.release();
   // and we store the method
   _myDescriptorMatchedMethod = matcherType;
   
   // Trying to create the matcher
   switch (matcherType) {
         // Brute Force matching with L2 distance
      case _BRUTE_FORCE:
         _myDescriptorMatcher = DescriptorMatcher::create("BruteForce");
         break;
         // Brute Force matching with L1 distance
      case _BRUTE_FORCE_L1:
         _myDescriptorMatcher = DescriptorMatcher::create("BruteForce-L1");
         break;
         // Brute Force matching with Hamming distance
      case _BRUTE_FORCE_HAMMING:
         _myDescriptorMatcher = DescriptorMatcher::create("BruteForce-Hamming");
         break;
         // Brute Force matching with Hamming2 distance
      case _BRUTE_FORCE_HAMMING_2:
         _myDescriptorMatcher = DescriptorMatcher::create("BruteForce-Hamming(2)");
         break;
         // Flann based matching
      case _FLANN:
         _myDescriptorMatcher = DescriptorMatcher::create("FlannBased");
         break;
         
         
      default:
         _myDescriptorMatcher = DescriptorMatcher::create("BruteForce");
         _myDescriptorMatchedMethod = _BRUTE_FORCE;
         break;
   }

}


void MyDescriptorMatcher::changeMatchingMethod(int matcherType, int colorDescriptorType, int colorDescriptorDefaultNorm, int thermalDescriptorType, int thermalDescriptorDefaultNorm) {

   // First release the previous detector
   _myDescriptorMatcher.release();
   // and we store the method
   _myDescriptorMatchedMethod = matcherType;
   
   // Trying to create the matcher
   switch (matcherType) {
         // Brute Force matching with L2 distance
      case _BRUTE_FORCE:
         _myDescriptorMatcher = DescriptorMatcher::create("BruteForce");
         break;
         // Brute Force matching with L1 distance
      case _BRUTE_FORCE_L1:
         _myDescriptorMatcher = DescriptorMatcher::create("BruteForce-L1");
         break;
         // Brute Force matching with Hamming distance
      case _BRUTE_FORCE_HAMMING:
         _myDescriptorMatcher = DescriptorMatcher::create("BruteForce-Hamming");
         break;
         // Brute Force matching with Hamming2 distance
      case _BRUTE_FORCE_HAMMING_2:
         _myDescriptorMatcher = DescriptorMatcher::create("BruteForce-Hamming(2)");
         break;
         // Flann based matching
      case _FLANN:
         _myDescriptorMatcher = DescriptorMatcher::create("FlannBased");
         break;
         
         
      default:
         _myDescriptorMatcher = DescriptorMatcher::create("BruteForce");
         _myDescriptorMatchedMethod = _BRUTE_FORCE;
         break;
   }
   
   // Checking if the matcher is compatible with the descriptor
   // 1: Hamming distance should only be used with binary descriptors
   if( (matcherType == _BRUTE_FORCE_HAMMING || matcherType == _BRUTE_FORCE_HAMMING_2) && ((colorDescriptorType == CV_32F || colorDescriptorDefaultNorm <= NORM_L2SQR) || (thermalDescriptorType == CV_32F || thermalDescriptorDefaultNorm <= NORM_L2SQR)) ) {
      cout << "**************************************************************************"<<endl;
      cout << "It's strange. You should use Hamming distance only for a binary descriptor"<<endl;
      cout << "We default to Brute Force matcher with L2 distance"<<endl;
      cout << "**************************************************************************"<<endl;
      _myDescriptorMatcher = DescriptorMatcher::create("BruteForce");
   }
   
   // 2: L1 or L2 distances should not be used with binary descriptors
   if( (matcherType == _BRUTE_FORCE || matcherType == _BRUTE_FORCE_L1) && ((colorDescriptorDefaultNorm >= NORM_HAMMING)||(thermalDescriptorDefaultNorm >= NORM_HAMMING)) ) {
      cout << "**************************************************************************"<<endl;
      cout << "It's strange. You shouldn't use L1 or L2 distance for a binary descriptor"<<endl;
      cout << "We default to Brute Force matcher with Hamming distance"<<endl;
      cout << "**************************************************************************"<<endl;
      _myDescriptorMatcher = DescriptorMatcher::create("BruteForce-Hamming");
   }
   
}


// Performs the matching based on the descriptors and fills in a vector of DMatches
void MyDescriptorMatcher::match(Mat descColorImg, Mat descThermalImg, vector<DMatch>& matches, vector<DMatch>& bestMatches) 
{

    // Cleaning up previous matches
    matches.clear();
    bestMatches.clear();

    // Resetting distances
    _minDist = 1000.;
    _maxDist = 0.;

    try
    {
        // Perform matching
        _myDescriptorMatcher->match(descColorImg, descThermalImg, matches, Mat());

        cout << "*** NUMBER OF MATCHES: " << matches.size() << endl;

        // Quick calculation of max and min distances between keypoints
        for (int i = 0; i < matches.size(); i++)
        {
            double dist = matches[i].distance;
            if (dist < _minDist) {
                _minDist = dist;
            }
            if (dist > _maxDist) {
                _maxDist = dist;
            }
        }

        if (_minDist < _EPSILON_DIST) {
            _minDist = _EPSILON_DIST;
        }

        // Use only "good" matches (i.e. which distance is less than a threshold)
        for (int i = 0; i < matches.size(); i++)
        {
            // TODO: keep only good matches
            if (matches[i].distance <= 3*_minDist) {
                bestMatches.push_back(matches[i]);
            }

        }
        cout << "*** NUMBER OF GOOD MATCHES: " << bestMatches.size() << endl;

        // Cumulative distance
        double cumulativeDistance = 0.0;
        for (size_t i = 0; i < bestMatches.size(); i++) {
            cumulativeDistance += bestMatches[i].distance;
        }
        cout << "*** CUMULATIVE DISTANCE OF GOOD MATCHES: " << cumulativeDistance << endl;

    }

        catch (Exception& e)
        {
            cout << e.msg << endl;
            cout << "Cumulative distance cannot be computed." << endl;
        }
    
}
    
    // Draw best matches into an image and returns it
    Mat MyDescriptorMatcher::drawMatchingResults(Mat colImg, std::vector< KeyPoint > colKeypoints, Mat thermalImg, std::vector< KeyPoint > thermalKeypoints, vector<DMatch> matches) {
        Mat result;
        drawMatches(colImg, colKeypoints, thermalImg, thermalKeypoints, matches, result);

        return result;
    }


    // Return a string corresponding to the name of the current matching method
    const string MyDescriptorMatcher::getMatcherName() {
        return MyDescriptorMatcher::getMatcherName(_myDescriptorMatchedMethod);
    }

    // Getting the name of the corner detector
    const string MyDescriptorMatcher::getMatcherName(int matcherType) {
        string res;
        switch (matcherType) {
            //case _BRUTE_FORCE (with L2 distance
        case _BRUTE_FORCE:
            res = "Brute Force L2 distance";
            break;
            // _BRUTE_FORCE (it is a special configuration of the GFTT detector in OpenCV
        case _BRUTE_FORCE_L1:
            res = "Brute Force L1 distance";
            break;
            // _BRUTE_FORCE_HAMMING
        case _BRUTE_FORCE_HAMMING:
            res = "Brute Force Hamming distance";
            break;
            // _BRUTE_FORCE_HAMMING_2
        case _BRUTE_FORCE_HAMMING_2:
            res = "Brute Force Hamming2 distance (to use with ORB only)";
            break;
            // _FLANN
        case _FLANN:
            res = "Flann";
            break;
            //default?
        default:
            res = "Brute Force L2 distance";
            break;
        }

        return res;
    }