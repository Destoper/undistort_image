#include "undistortedCap.h"

using namespace std;

UndistortedCap::UndistortedCap(string undistort_data_path)
    : undistort_data_path(undistort_data_path) {
    try {
        this->set_undistort_rectify_map();
    } catch (const exception& e) {
        cerr << "Error in constructor: " << e.what() << endl;
        // ERROR HANDLER
    }
}

Mat UndistortedCap::undistort_frame(const Mat& distorted_image) {
    remap(distorted_image, undistorted_image, this->map_x, this->map_y, INTER_LINEAR);

    // cropping the image to remove black borders
    undistorted_image = undistorted_image(validPixROI);

    return undistorted_image;
}

void UndistortedCap::set_undistort_rectify_map() {
    this->set_undistort_data();
    this->optimal_camera_matrix = getOptimalNewCameraMatrix(this->camera_matrix, this->dist_coeffs, this->IMAGE_SIZE, 1, this->IMAGE_SIZE, &validPixROI, 0);

    initUndistortRectifyMap(
        this->camera_matrix,
        this->dist_coeffs,
        Mat(),
        this->optimal_camera_matrix,
        IMAGE_SIZE,
        CV_32FC1,
        this->map_x,
        this->map_y
    );
}

void UndistortedCap::set_undistort_data() {
    try {
        FileStorage fs(undistort_data_path, FileStorage::READ);
        if (!fs.isOpened()) {
            throw runtime_error("Could not open the undistort data file.");
        }

        fs["camera_matrix"] >> this->camera_matrix;
        fs["distortion_coefficients"] >> this->dist_coeffs;
        fs.release();
    } catch (const exception& e) {
        cerr << "Error in set_undistort_data: " << e.what() << endl;
        // ERROR HANDLER
    }
}
