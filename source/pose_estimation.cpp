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
	//Mat Image_Blob = blobFromImage(Frame, 1.0 / 255, Size(400, 300), Scalar(0, 0, 0), false, false);

    // Set the prepared Blob as the input to the Dnn network
	Dnn_Net.setInput(Image_Blob);

    return Dnn_Net.forward();
} // Feed_Image_Blob_To_Dnn

void Pose_Estimation::Set_Net_Computation_On_GPU(GPU_Support_Type Backend_Support)
{
    if(GPU_Support)
    {
        Dnn_Net.setPreferableBackend(DNN_BACKEND_CUDA);
        Dnn_Net.setPreferableTarget(DNN_TARGET_CUDA);
    }
}

void Pose_Estimation::TFlite_Model()
{
    const string Model_Path = "/home/error/Desktop/learn_2_squat/source/pose_estimation_models/pose/posenet/posenet_mobilenet_v1_100_257x257_multi_kpt_stripped.tflite";

    // Load the model
    unique_ptr<FlatBufferModel> model = FlatBufferModel::BuildFromFile(Model_Path.c_str());

    // Build the interpreter
    BuiltinOpResolver resolver;
    unique_ptr<Interpreter> interpreter;
    InterpreterBuilder(*model, resolver)(&interpreter);

    // Resize input tensors, if desired.
    interpreter->AllocateTensors();

    float* input = interpreter->typed_input_tensor<float>(0);
    // Fill `input`.

    interpreter->Invoke();

    float* output = interpreter->typed_output_tensor<float>(0);

}

Pose_Estimation::~Pose_Estimation()
{
 // Empty 
} // ~Pose_Estimation
