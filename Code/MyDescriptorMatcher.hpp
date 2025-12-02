//
//  MyDescriptorMatcher.hpp
//  Features
//
//  Created by Jean-Marie Normand on 28/11/2017.
//  Copyright © 2017 Jean-Marie Normand. All rights reserved.
//

#ifndef MyDescriptorMatcher_hpp
#define MyDescriptorMatcher_hpp

#include <stdio.h>

#include <opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;


// Possible matchers
#define _BRUTE_FORCE             0
#define _BRUTE_FORCE_L1          1
#define _BRUTE_FORCE_HAMMING     2
#define _BRUTE_FORCE_HAMMING_2   3
#define _FLANN                   4
#define _NB_MATCHERS             _FLANN

#define _MIN_DIST_MULTIPLIER     10.

#define _EPSILON_DIST   0.001

class MyDescriptorMatcher {
private:
   // The descriptor matcher
   Ptr<DescriptorMatcher>  _myDescriptorMatcher;
   // the descriptor method
   int                     _myDescriptorMatchedMethod;
   
   // Max and min distances between the matches
   double                  _maxDist;
   double                  _minDist;
   
   // Matches
   vector<DMatch>          _matches;
   vector<DMatch>          _bestMatches;
   
public:
   // Constructors
   // note that NOT every matcher can be used with every descriptor
   MyDescriptorMatcher();
   MyDescriptorMatcher(int matcherType, int colorDescriptorType, int colorDescriptorDefaultNorm, int thermalDescriptorType, int thermalDescriptorDefaultNorm);
   
   
   // Changing the current matching method
   void changeMatchingMethod(int matcherType);
   
   void changeMatchingMethod(int matcherType, int colorDescriptorType, int colorDescriptorDefaultNorm, int thermalDescriptorType, int thermalDescriptorDefaultNorm);
   
   
   // Performs the matching based on the descriptors and fills in a vector of DMatches
   void match(Mat descColorImg, Mat descThermalImg, vector<DMatch>& matches, vector<DMatch>& bestMatches);
   
   // Draw best matches into an image and returns it
   Mat drawMatchingResults(Mat colImg, std::vector< KeyPoint > colKeypoints, Mat thermalImg, std::vector< KeyPoint > thermalKeypoints, vector<DMatch> matches);
   
   
   // Returns a string corresponding to the name of the current matching method
   const string getMatcherName();
   
   // Returns a string corresponding to the name of the current matching method
   static const string getMatcherName(int matcherType);
};

#endif /* MyDescriptorMatcher_hpp */
