#include <pose_estimation.hpp>

Pose_Estimation::Pose_Estimation( int Frame_Height, int Frame_Width) 
: Frame_Height(Frame_Height), Frame_Width(Frame_Width)
{
    // Empty
} // Pose_Estimation

Mat Pose_Estimation::Prediction(Mat Frame)
{   
    // Resizing the input image t
    //Mat Resized_Frame;

    //resize(Frame, Resized_Frame, Size(200, 200));
    
    // Make the Image to a imabe Blob
	Mat Image_Blob = blobFromImage(Frame, 1.0 / 255, Size(Frame_Width, Frame_Height), Scalar(0, 0, 0), false, false);
	//Mat Image_Blob = blobFromImage(Resized_Frame, 1.0 / 255, Size(300, 300), Scalar(0, 0, 0), false, false);

    // Set the prepared Blob as the input to the Dnn network
	Dnn_Net.setInput(Image_Blob);

    return Dnn_Net.forward();
} // Feed_Image_Blob_To_Dnn

void Pose_Estimation::Set_Net_Computation_On_GPU()
{
    Dnn_Net.setPreferableBackend(DNN_BACKEND_CUDA);
    Dnn_Net.setPreferableTarget(DNN_TARGET_CUDA);
}

Pose_Estimation::~Pose_Estimation()
{
 // Empty 
} // ~Pose_Estimation
