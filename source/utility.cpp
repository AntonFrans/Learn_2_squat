#include <utility.hpp>

void Utility::Set_Processor_Start_Time()
{
    Start_Processor_Tick_Time = (double) cv::getTickCount();
}

double Utility::Calculate_Time_Taken()
{
    return ((double)cv::getTickCount() - Start_Processor_Tick_Time)/cv::getTickFrequency();
}
