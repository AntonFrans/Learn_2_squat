#include <camera.hpp>
#include <pose_estimation.hpp>
#include <utility.hpp>

int main(int, char**)
{
    Mat Camera_Frame;
    Mat Dnn_Prediction_Output;
    bool Camera_Session_Suceeded = true;    
    const int Frame_Width        = 640;
    const int Frame_Height       = 480; 
    
    Camera Camera(0, 0, cv::CAP_ANY, Frame_Height, Frame_Width);
    Camera.Open_Camera();
    Camera.Camera_Terminal_Description();

    Pose_Estimation Pose_Estimation(Frame_Height, Frame_Width);
    Pose_Estimation.Set_Net_Computation_On_GPU(GPU_Support); // Dont know if it works as expected
    
    Utility Measure_Frame_Processing_Time;
    double Calculated_FPS = 0.0;

    while(Camera_Session_Suceeded)
    {
        Measure_Frame_Processing_Time.Set_Processor_Start_Time();

        Camera_Session_Suceeded = Camera.Set_Frame();
        Camera_Frame            = Camera.Get_Frame();
        Dnn_Prediction_Output   = Pose_Estimation.Prediction(Camera_Frame);

        Camera.Draw_Keypoints(Dnn_Prediction_Output);
        Camera.Write_Skeleton_To_Frame(Dnn_Prediction_Output);

        Calculated_FPS = Measure_Frame_Processing_Time.Calculate_FPS();

        Camera.Write_Text_To_Frame(Calculated_FPS);

        Camera_Session_Suceeded = Camera.Start_Camera_Session();
    } 

    return 0;
}
