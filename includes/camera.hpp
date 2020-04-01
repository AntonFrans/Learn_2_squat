#ifndef CAMERA_HPP
#define CAMERA_HPP
 
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

class Camera 
{
private: 
    Mat          Frame;
    VideoCapture Video_Capture;
    int          Device_ID;
    int          API_ID;
    int          Video_Capture_Value;

public:
    Camera(int Video_Capture_Value, int Device_ID, int API_ID);

    void Open_Camera();

    ~Camera();
};

#endif
