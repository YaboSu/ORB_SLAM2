#include <iostream>

#include <opencv2/opencv.hpp>

#include "ORBextractor.h"

using namespace std;

int main(int argc, char** argv) {
    if(argc != 3) {
        cerr << "Usage: ./view_features path_to_settings path_to_image" << endl;
        return 1;
    }

    cv::FileStorage settings(argv[1], cv::FileStorage::READ);
    if(!settings.isOpened()) {
       cerr << "Failed to open settings file at: " << argv[1] << endl;
       exit(-1);
    }

    int nFeatures = settings["ORBextractor.nFeatures"];
    float scaleFactor = settings["ORBextractor.scaleFactor"];
    int nLevels = settings["ORBextractor.nLevels"];
    int iniThFAST = settings["ORBextractor.iniThFAST"];
    int minThFAST = settings["ORBextractor.minThFAST"];

    cv::Mat img = cv::imread(argv[2]);
    if(img.empty()) {
        cerr << "Failed to load image at: " << argv[2] << endl;
        return 1;
    }
    cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);

    ORB_SLAM2::ORBextractor extractor = ORB_SLAM2::ORBextractor(nFeatures, scaleFactor, nLevels, iniThFAST, minThFAST);
    
    vector<cv::KeyPoint> keypoints;
    cv::Mat descriptors;
    extractor(img, cv::Mat(), keypoints, descriptors);
    cv::drawKeypoints(img, keypoints, img);
    cv::imwrite("test.jpg", img);
    int counter[8] = {};

    for(size_t i = 0; i < keypoints.size(); i++) {
        // cout << keypoints[i].pt << ", " <<  << ", " << keypoints[i].angle << endl;
        counter[keypoints[i].octave] += 1;
    }
    for(size_t i = 0; i < 8; i++) {
        cout << i << ": " << counter[i] << endl;
    }
}