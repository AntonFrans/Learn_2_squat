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
        Mat Dnn_Prediction_Output;
        
        //Frame specifications
        const int Frame_Width;
        const int Frame_Height;
        Mat       Frame;


        // Keypoint specifications
        const int Keypoint_Index_Pairs[KEYPOINTS][PAIRS] = 
        {   
            {0,1}  , {1,2}, 
            {2,3}  , {3,4}, 
            {1,5}  , {5,6},
            {6,7}  , {1,14}, 
            {14,8} , {8,9}, 
            {9,10} , {14,11}, 
            {11,12}, {12,13}
        };
        

    public:
        Pose_Estimation(int Frame_Width, int Frame_Height);

        void Prediction(Mat Frame);

        void Draw_Keypoints(Mat Frame);

        void test();

        ~Pose_Estimation();

};

#endif 