#ifndef CAMERA_HPP
#define CAMERA_HPP

#define nPoints    16
#define KEYPOINTS  14
#define BODY_PARTS 14
#define PAIRS      2

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

typedef enum 
{
    BPI_FIRST_ELEMENT = 0,

    Head = BPI_FIRST_ELEMENT,
    Chin,
    Left_Shoulder,
    Left_Elbow,
    Left_Wrist,
    Right_Shoulder,
    Right_Elbow,
    Right_Wrist,
    Right_Pelvic,
    Right_Knee,
    Left_Ancle,
    Left_Pelvic,
    Left_Knee,
    Right_Ancle,
    Solar_Plexus,

    BPI_LAST_ELEMENT
} Body_Part_Index;

typedef struct 
{
    Body_Part_Index Connection_Fragment_From;
    Body_Part_Index Connection_Fragment_To;
} Keypoint_Pairs_Type;


class Camera 
{
private:
    Mat           Frame;
    VideoCapture  Video_Capture;
    VideoWriter   Video_Writer;
    vector<Point> points;
    int           Device_ID;
    int           API_ID;
    int           Video_Capture_Value;
    const int     Frame_Height;
    const int     Frame_Width;

    const Keypoint_Pairs_Type Skeleton_Body_Part_Connections[BODY_PARTS] = 
    {
        {Head         , Chin}          , {Chin          , Left_Shoulder}, 
        {Left_Shoulder, Left_Elbow}    , {Left_Elbow    , Left_Wrist}   , 
        {Chin         , Right_Shoulder}, {Right_Shoulder, Right_Elbow}  ,
        {Right_Elbow  , Right_Wrist}   , {Chin          , Solar_Plexus} , 
        {Solar_Plexus , Right_Pelvic}  , {Right_Pelvic  , Right_Knee}   , 
        {Right_Knee   , Left_Ancle}    , {Solar_Plexus  , Left_Pelvic}  , 
        {Left_Pelvic  , Left_Knee}     , {Left_Knee     , Right_Ancle}
    };

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
    Camera(int Video_Capture_Value, int Device_ID, int API_ID, const int Frame_Height, const int Frame_Width);

    void Open_Camera();
    
    bool Set_Frame();

    Mat Get_Frame();

    bool Start_Camera_Session();

    void Camera_Terminal_Description();
    
    int Get_Frame_Width();

    int Get_Frame_Height();

    void Write_Text_To_Frame(double Process_Time);

    void Draw_Keypoints(Mat Prediction_Output);

    void Write_Skeleton_To_Frame(Mat Frame, double Frame_Process_Time);

    ~Camera();
};

#endif
