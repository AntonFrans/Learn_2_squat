#ifndef POSE_ESTIMATION_HPP
#define POSE_ESTIMATION_HPP

#define KEYPOINTS 14
#define PAIRS     2

#include <string>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace cv::dnn;
using namespace std;

class Pose_Estimation
{
    private:
        // Specify the paths
        const string PATH_ROOT_Pose_Estimation = "/home/error/Desktop/learn_2_squat/source/pose_estimation/" ;
        const string Proto_File                = PATH_ROOT_Pose_Estimation + "pose/mpi/pose_deploy_linevec_faster_4_stages.prototxt";
        const string Weights_File              = PATH_ROOT_Pose_Estimation + "pose/mpi/pose_iter_160000.caffemodel";

        // DNN specifications
        Net Dnn_Net = readNetFromCaffe(Proto_File, Weights_File);

        //Frame specifications
        int Frame_Width;
        int Frame_Height;
        Mat Frame;

    public:
        Pose_Estimation(int Frame_Width, int Frame_Height);

        Mat Prediction(Mat Frame);

        void Set_Net_Computation_On_GPU();

        ~Pose_Estimation();

};

#endif 