#ifndef POSE_ESTIMATION_HPP
#define POSE_ESTIMATION_HPP

#define KEYPOINTS 14
#define PAIRS     2

#include <string>

// Opencv
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

// Tensorflowlite
#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/model.h"
#include "tensorflow/lite/tools/gen_op_registration.h"

// Standard namespaces
using namespace std;

// Opencv namespaces
using namespace cv;
using namespace cv::dnn;

// Tensorflow Lite namespaces
using namespace tflite;
using namespace tflite::ops::builtin;

typedef enum
{
    First_Enum_Element = 0,

    CPU_Support = First_Enum_Element,
    GPU_Support,

    Last_Enum_Element
}GPU_Support_Type;

class Pose_Estimation
{
    private:
        // Specify the paths
        const string Pose_Estimation_ROOT_Path = "/home/error/Desktop/learn_2_squat/source/pose_estimation_models/" ;
        const string Proto_File                = Pose_Estimation_ROOT_Path + "pose/mpi/pose_deploy_linevec_faster_4_stages.prototxt";
        const string Weights_File              = Pose_Estimation_ROOT_Path + "pose/mpi/pose_iter_160000.caffemodel";

        // DNN specifications
        Net Dnn_Net = readNetFromCaffe(Proto_File, Weights_File);

        //Frame specifications
        int Frame_Width;
        int Frame_Height;
        Mat Frame;

    public:
        Pose_Estimation(int Frame_Width, int Frame_Height);

        Mat Prediction(Mat Frame);

        void Set_Net_Computation_On_GPU(GPU_Support_Type Backend_Support );

        void TFlite_Model();

        ~Pose_Estimation();

};

#endif 