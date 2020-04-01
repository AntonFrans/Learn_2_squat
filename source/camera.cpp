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

    // Check if camera started succeeded.
    if (!Video_Capture.isOpened()) {
        cerr << "ERROR! Unable to open camera\n";
    }

    cout << "Start grabbing" << endl
        << "Press any key to terminate" << endl;
    for (;;)
    {
        // wait for a new frame from camera and store it into 'frame'
        Video_Capture.read(Frame);
        // check if we succeeded
        if (Frame.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }

        // show live and wait for a key with timeout long enough to show images
        imshow("Live", Frame);
        if (waitKey(5) >= 0)
        {
            break;
        }     
    }

} // Open_Camera

Camera::~Camera()
{
    // Empty
} // ~Camera


int main(int, char**)
{
    Camera object(0, 0, cv::CAP_ANY);
    object.Open_Camera();
    
    return 0;
} 
