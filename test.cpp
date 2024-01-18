#include <opencv2/opencv.hpp>
#include "undistortedCap.h"

using namespace cv;
using namespace std;

int main() {
    string img_path = "image0.png";
    UndistortedCap undistortedCap("calib_data/calibration_data_1920x1080.xml");
    Mat img = imread(img_path);
    Mat undistorted = undistortedCap.undistort_frame(img);
    imwrite("undistorted0C.png", undistorted);
    return 0;
}