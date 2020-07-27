#include <camera.hpp>
#include <pose_estimation.hpp>

int main(int, char**)
{
    Mat Camera_Frame;
    Mat Dnn_Prediction_Output;
    bool Camera_Session_Suceeded = true;    
    const int Frame_Width        = 640; // 1280
    const int Frame_Height       = 360; // 720
    Camera Camera(0, 0, cv::CAP_ANY, Frame_Height, Frame_Width);

    Camera.Open_Camera();
    Camera.Camera_Terminal_Description();

    Pose_Estimation Pose_Estimation(Frame_Height, Frame_Width);
    Pose_Estimation.Set_Net_Computation_On_GPU();
    
    while(Camera_Session_Suceeded)
    {
        Camera_Session_Suceeded = Camera.Set_Frame();
        Camera_Frame            = Camera.Get_Frame();
        Dnn_Prediction_Output   = Pose_Estimation.Prediction(Camera_Frame);

        Camera.Draw_Keypoints(Dnn_Prediction_Output);
        Camera.Write_Skeleton_To_Frame(Dnn_Prediction_Output, 99);
        Camera.Write_Text_To_Frame(666);

        Camera_Session_Suceeded = Camera.Start_Camera_Session();
    }

    return 0;
}
