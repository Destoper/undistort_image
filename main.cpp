#include <opencv2/opencv.hpp>
#include "undistortedCap.h"

using namespace cv;
using namespace std;

int main() {
    // Open the default camera (camera index 0)
    Mat undistorted;
    VideoCapture cap(0);
    UndistortedCap undistortedCap("calib_data/calibration_data.xml");

    // Check if the camera opened successfully
    if (!cap.isOpened()) {
        cerr << "Error opening the camera" << endl;
        return -1;
    }

    // Create a window to display the camera feed
    namedWindow("Camera Capture", WINDOW_NORMAL);

    while (true) {
        Mat frame;

        // Capture a frame from the camera
        cap >> frame;

        // Check if the frame is empty
        if (frame.empty()) {
            cerr << "Error capturing frame" << endl;
            break;
        }

        // Undistort the frame
        undistorted = undistortedCap.undistort_frame(frame);

        // Display the captured frame
        imshow("Camera Capture", undistorted);

        // Check if the 's' key is pressed
        if (waitKey(1) == 's') {
            // Save the undistorted frame as an image
            imwrite("undistorted_frame.jpg", undistorted);
            cout << "Undistorted frame saved as undistorted_frame.jpg" << endl;
        }

        // Break the loop if the 'ESC' key is pressed
        if (waitKey(1) == 27) {
            break;
        }
    }

    // Release the camera and close the window
    cap.release();
    destroyAllWindows();

    return 0;
}
