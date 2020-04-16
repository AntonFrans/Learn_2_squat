#ifndef CAMERA_HPP
#define CAMERA_HPP

#define KEYPOINTS 14
#define PAIRS     2

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

class Camera 
{
private: 
    Mat          Frame;
    VideoCapture Video_Capture;
    VideoWriter  Video_Writer;
    int          Device_ID;
    int          API_ID;
    int          Video_Capture_Value;
    const int Keypoint_Index_Pairs[KEYPOINTS][PAIRS] = 
    {   
        {0,1}  , {1,2}, 
        {2,3}  , {3,4}, 
        {1,5}  , {5,6},
        {6,7}  , {1,14}, 
        {14,8} , {8,9}, 
        {9,10} , {14,11}, 
        {11,12}, {12,13}
    };

public:
    Camera(int Video_Capture_Value, int Device_ID, int API_ID);

    void Open_Camera();
    
    bool Set_Frame();

    Mat Get_Frame();

    bool Start_Camera_Session();

    void Camera_Terminal_Description();
    
    int Get_Frame_Width();

    int Get_Frame_Height();

    void Play(Mat Frame);

    ~Camera();
};

#endif
