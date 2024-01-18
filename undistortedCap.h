#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;

class UndistortedCap {
public:
    UndistortedCap(std::string undistort_data_path);
    Mat undistort_frame(const Mat& distorted_image);

private:
    std::string undistort_data_path;
    Mat camera_matrix;
    Mat dist_coeffs;
    Mat map_x, map_y; 
    Mat optimal_camera_matrix;
    Mat undistorted_image;
    Size IMAGE_SIZE = Size(1920, 1080);
    Rect validPixROI;

    void set_undistort_rectify_map();
    void set_undistort_data();
};