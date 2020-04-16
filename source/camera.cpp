#include <camera.hpp>

Camera::Camera(int Video_Capture_Value, int Device_ID, int API_ID)
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
    imshow("Live", Frame);
    if (waitKey(5) >= 0)
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
}

int Camera::Get_Frame_Height()
{
    return Frame.size().height;
}

void Camera::Play(Mat Prediction_Output)
{
    const int Frame_Width  = 640;
    const int Frame_Height = 480;
    const int nPoints      = 15;
    const float thresh     = 0.01;
    int H = Prediction_Output.size[2];
    int W = Prediction_Output.size[3];
    double t = (double) cv::getTickCount();

    Mat Frame_Copy;
    
    VideoWriter Video_Writer("Output-Skeleton.avi",VideoWriter::fourcc('M','J','P','G'), 10, Size(Frame_Width, Frame_Height));

     // find the position of the body parts
        vector<Point> points(nPoints);
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
                p.x *= (float)Frame_Width / W ;
                p.y *= (float)Frame_Height / H ;

                circle(Frame_Copy, cv::Point((int)p.x, (int)p.y), 8, Scalar(0,255,255), -1);
                cv::putText(Frame_Copy, cv::format("%d", n), cv::Point((int)p.x, (int)p.y), cv::FONT_HERSHEY_COMPLEX, 1.1, cv::Scalar(0, 0, 255), 2);
            }
            points[n] = p;
        }

        int nPairs = sizeof(Keypoint_Index_Pairs)/sizeof(Keypoint_Index_Pairs[0]);

        for (int n = 0; n < nPairs; n++)
        {
            // lookup 2 connected body/hand parts
            Point2f partA = points[Keypoint_Index_Pairs[n][0]];
            Point2f partB = points[Keypoint_Index_Pairs[n][1]];

            if (partA.x<=0 || partA.y<=0 || partB.x<=0 || partB.y<=0)
                continue;

            line(Frame, partA, partB, Scalar(0,255,255), 8);
            circle(Frame, partA, 8, Scalar(0,0,255), -1);
            circle(Frame, partB, 8, Scalar(0,0,255), -1);
        }

        t = ((double)cv::getTickCount() - t)/cv::getTickFrequency();
        cv::putText(Frame, cv::format("time taken = %.2f sec", t), cv::Point(50, 50), cv::FONT_HERSHEY_COMPLEX, .8, cv::Scalar(255, 50, 0), 2);
        // imshow("Output-Keypoints", frameCopy);
        imshow("Output-Skeleton", Frame);
        Video_Writer.write(Frame);
    
    // When everything done, release the video capture and write object
    //Video_Capture.release();
    Video_Writer.release();
}

Camera::~Camera()
{
    // Empty
} // ~Camera
