#include <camera.hpp>
#include <pose_estimation.hpp>

int main(int, char**)
{
    Mat Camera_Frame;
    bool Camera_Session_Suceeded = true;    
    const int Frame_Width        = 640;
    const int Frame_Height       = 480;
    Camera Camera(0, 0, cv::CAP_ANY);

    //Camera.Open_Camera();
    //Camera.Camera_Terminal_Description();

    Pose_Estimation Pose_Estimation(Frame_Width, Frame_Height);
    
    while(Camera_Session_Suceeded)
    {
        //Camera_Session_Suceeded = Camera.Set_Frame() && Camera.Start_Camera_Session();

        //Camera_Frame = Camera.Get_Frame();
        //Pose_Estimation.Prediction(Camera_Frame); 
        //Pose_Estimation.Draw_Keypoints(Camera_Frame);

        Pose_Estimation.test();
    }

    return 0;
}
