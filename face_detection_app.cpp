#include <opencv\build\include\opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    // Initialize the cascade classifier
    CascadeClassifier face_cascade;
    if (!face_cascade.load("haarcascade_frontalface_alt2.xml")) {
        cout << "Error loading cascade file for face" << endl;
        return 1;
    }

    // Initialize the video capture
    VideoCapture capture(0);
    if (!capture.isOpened()) {
        cout << "Error opening video capture" << endl;
        return 1;
    }

    Mat frame;
    while (true) {
        capture >> frame;

        if (frame.empty()) {
            cout << "No captured frame. Exiting..." << endl;
            break;
        }

        // Detect faces
        vector<Rect> faces;
        face_cascade.detectMultiScale(frame, faces, 1.1, 10, 0, Size(30, 30));

        // Draw rectangles around faces
        for (auto& face : faces) {
            rectangle(frame, face, Scalar(255, 0, 0), 2);
        }

        // Show the frame
        imshow("Face Detection", frame);

        // Exit the loop if 'q' is pressed
        if (waitKey(1) == 'q') {
            break;
        }
    }

    // Release resources
    capture.release();
    destroyAllWindows();

    return 0;
}
