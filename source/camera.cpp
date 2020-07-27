#include <camera.hpp>

Camera::Camera(int Video_Capture_Value, int Device_ID, int API_ID, const int Frame_Height, const int Frame_Width) 
: points(nPoints), Frame_Height(Frame_Height), Frame_Width(Frame_Width)
{
    this->Video_Capture_Value = Video_Capture_Value;
    this->Device_ID           = Device_ID;
    this->API_ID              = API_ID;
} // Camera

void Camera::Open_Camera()
{
    Video_Capture.open(Video_Capture_Value);
    
    Video_Capture.open(Device_ID + API_ID);
} // Open_Camera

bool Camera::Set_Frame()
{
    bool Succeeded_Frame_Read = true;
        
    Video_Capture.read(Frame);

    // check if we succeeded
    if (Frame.empty()) {
        Succeeded_Frame_Read = false;
    }

    return Succeeded_Frame_Read; 
} // Set_Frame

Mat Camera::Get_Frame()
{
    return Frame;
} // Get_Frame

bool Camera::Start_Camera_Session()
{
    bool Start_Camera_Session = true;

    // show live and wait for a key with timeout long enough to show images
    imshow("Output-Skeleton", Frame);

    if (waitKey(1) >= 0)
    {
        Start_Camera_Session = false;
    }  

    return Start_Camera_Session;
} // Start_Camera_Interface

void Camera::Camera_Terminal_Description()
{
    cout << "1. Start grabbing" << endl
    << "2. Terminate by pressing CTRL + C" << endl; 
} // Camera_Terminal_Description


int Camera::Get_Frame_Width()
{
    return Frame.size().width;
} // Get_Frame_Width

int Camera::Get_Frame_Height()
{
    return Frame.size().height;
} // Get_Frame_Height

void Camera::Write_Text_To_Frame(double Process_Time)
{
    putText(Frame, cv::format("time taken = %.2f sec", Process_Time), cv::Point(50, 50), cv::FONT_HERSHEY_COMPLEX, .8, cv::Scalar(255, 50, 0), 2);
} // Write_Text_To_Frame

void Camera::Draw_Keypoints(Mat Prediction_Output)
{
    int H = Prediction_Output.size[2];
    int W = Prediction_Output.size[3];
    const float thresh     = 0.01;
    
    for (int n=0; n < nPoints; n++)
    { 
        // Probability map of corresponding body's part.
        Mat probMap(H, W, CV_32F, Prediction_Output.ptr(0,n));

        Point2f p(-1,-1);
        Point maxLoc;
        double prob;
        minMaxLoc(probMap, 0, &prob, 0, &maxLoc);
        if (prob > thresh)
        {
            p = maxLoc;
            p.x *= (float)Frame_Width / W;
            p.y *= (float)Frame_Height / H;

            // FOR DEVELOPMENT PURPOSE
            //circle(Frame, cv::Point((int)p.x, (int)p.y), 8, Scalar(0,255,255), -1);
            //cv::putText(Frame, cv::format("%d", n), cv::Point((int)p.x, (int)p.y), cv::FONT_HERSHEY_COMPLEX, 1.1, cv::Scalar(0, 0, 255), 2);
        }
        
        points[n] = p;
    }
} // Draw_Keypoints

void Camera::Write_Skeleton_To_Frame(Mat Prediction_Output, double Frame_Process_Time)
{
    const float thresh     = 0.01;
    int H                  = Prediction_Output.size[2];
    int W                  = Prediction_Output.size[3];

    Body_Part_Index Body_Part;

    Mat Frame_Copy = Frame;
    
    VideoWriter Video_Writer("Output-Skeleton.avi",VideoWriter::fourcc('M','J','P','G'), 10, Size(Frame_Width, Frame_Height));

    int nPairs = sizeof(Keypoint_Index_Pairs)/sizeof(Keypoint_Index_Pairs[0]);

    for (int n = 0; n < nPairs; n++)
    {
        // lookup 2 connected body/hand parts
        Point2f partA = points[Keypoint_Index_Pairs[n][0]];
        Point2f partB = points[Keypoint_Index_Pairs[n][1]];

        if (partA.x<=0 || partA.y<=0 || partB.x<=0 || partB.y<=0)
            continue;
        
        // FOR DEVELOPMENT PURPOSE
        line(Frame, partA, partB, Scalar(0,255,255), 8);
        circle(Frame, partA, 8, Scalar(0,0,255), -1);
        circle(Frame, partB, 8, Scalar(0,0,255), -1);
    }

/*     for (int n = static_cast<int>(BPI_FIRST_ELEMENT); n < static_cast<int>(BPI_LAST_ELEMENT); n++)
    {
        // lookup 2 connected body/hand parts
        Point2f partA = points[Skeleton_Body_Part_Connections[n].Connection_Fragment_From];
        Point2f partB = points[Skeleton_Body_Part_Connections[n].Connection_Fragment_To];

        // FOR DEVELOPMENT PURPOSE
        if(partA.x > 0 || partA.y > 0 || partB.x > 0 || partB.y > 0)
        {
            line(Frame, partA, partB, Scalar(0,255,255), 8);
            circle(Frame, partA, 8, Scalar(0,0,255), -1);
            circle(Frame, partB, 8, Scalar(0,0,255), -1);
        }
    }  */

} // Write_Skeleton_To_Frame



Camera::~Camera()
{
    // Empty
} // ~Camera
