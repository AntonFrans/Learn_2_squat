#include <pose_estimation.hpp>

Pose_Estimation::Pose_Estimation(int Frame_Width, int Frame_Height) 
: Frame_Width(Frame_Width), Frame_Height(Frame_Height)
{
    // Empty
} // Pose_Estimation

void Pose_Estimation::Prediction(Mat Frame)
{   
    // Make the Image to a imabe Blob
	Mat Image_Blob = blobFromImage(Frame, 1.0 / 255, Size(Frame_Width, Frame_Height), Scalar(0, 0, 0), false, false);

    // Set the prepared Blob as the input to the Dnn network
	Dnn_Net.setInput(Image_Blob);

    Dnn_Prediction_Output = Dnn_Net.forward();
} // Feed_Image_Blob_To_Dnn

void Pose_Estimation::Draw_Keypoints(Mat Frame)
{
    int nPoints = 15;
    int inWidth = 368;
    int inHeight = 368;
    float thresh = 0.01;    
    
    VideoWriter video("Output-Skeleton.avi",VideoWriter::fourcc('M','J','P','G'), 30, Size(480,640));

    Mat frameCopy;
    double t=0;

    while( waitKey(1) < 0)
    {       
        double t = (double) cv::getTickCount();

    
        frameCopy = Frame.clone();

        int H = Dnn_Prediction_Output.size[2];
        int W = Dnn_Prediction_Output.size[3];

        // find the position of the body parts
        vector<Point> points(nPoints);
        for (int n=0; n < nPoints; n++)
        {
            // Probability map of corresponding body's part.
            Mat probMap(H, W, CV_32F, Dnn_Prediction_Output.ptr(0,n));

            Point2f p(-1,-1);
            Point maxLoc;
            double prob;
            minMaxLoc(probMap, 0, &prob, 0, &maxLoc);
            if (prob > thresh)
            {
                p = maxLoc;
                p.x *= (float)480 / W ;
                p.y *= (float)640 / H ;

                circle(frameCopy, cv::Point((int)p.x, (int)p.y), 8, Scalar(0,255,255), -1);
                cv::putText(frameCopy, cv::format("%d", n), cv::Point((int)p.x, (int)p.y), cv::FONT_HERSHEY_COMPLEX, 1.1, cv::Scalar(0, 0, 255), 2);
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
        video.write(Frame);
    }
    // When everything done, release the video capture and write object
/*     cap.release(); */
    video.release();
} // Prediction


void Pose_Estimation::test(){
    
    int nPoints = 15;
    int inWidth = 640;
    int inHeight = 480;
    float thresh = 0.01;    
    Mat frame, frameCopy;   
    cv::VideoCapture cap;

    cap.open(0);
    
    cap.open(0 + cv::CAP_ANY);

    cap.read(frame);
    
    int frameWidth = 640;
    int frameHeight = 480;
    
    VideoWriter video("Output-Skeleton.avi",VideoWriter::fourcc('M','J','P','G'), 10, Size(frameWidth,frameHeight));

    Net net = readNetFromCaffe(Proto_File, Weights_File);

    double t=0;
    while( waitKey(1) < 0)
    {       
        double t = (double) cv::getTickCount();

        cap >> frame;
        frameCopy = frame.clone();
        Mat inpBlob = blobFromImage(frame, 1.0 / 255, Size(inWidth, inHeight), Scalar(0, 0, 0), false, false);

        net.setInput(inpBlob);

        Mat output = net.forward();

        int H = output.size[2];
        int W = output.size[3];

        // find the position of the body parts
        vector<Point> points(nPoints);
        for (int n=0; n < nPoints; n++)
        {
            // Probability map of corresponding body's part.
            Mat probMap(H, W, CV_32F, output.ptr(0,n));

            Point2f p(-1,-1);
            Point maxLoc;
            double prob;
            minMaxLoc(probMap, 0, &prob, 0, &maxLoc);
            if (prob > thresh)
            {
                p = maxLoc;
                p.x *= (float)frameWidth / W ;
                p.y *= (float)frameHeight / H ;

                circle(frameCopy, cv::Point((int)p.x, (int)p.y), 8, Scalar(0,255,255), -1);
                cv::putText(frameCopy, cv::format("%d", n), cv::Point((int)p.x, (int)p.y), cv::FONT_HERSHEY_COMPLEX, 1.1, cv::Scalar(0, 0, 255), 2);
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

            line(frame, partA, partB, Scalar(0,255,255), 8);
            circle(frame, partA, 8, Scalar(0,0,255), -1);
            circle(frame, partB, 8, Scalar(0,0,255), -1);
        }

        t = ((double)cv::getTickCount() - t)/cv::getTickFrequency();
        cv::putText(frame, cv::format("time taken = %.2f sec", t), cv::Point(50, 50), cv::FONT_HERSHEY_COMPLEX, .8, cv::Scalar(255, 50, 0), 2);
        // imshow("Output-Keypoints", frameCopy);
        imshow("Output-Skeleton", frame);
        video.write(frame);
    }
    // When everything done, release the video capture and write object
    cap.release();
    video.release();
}

Pose_Estimation::~Pose_Estimation()
{
 // Empty 
} // ~Pose_Estimation
