#include <utility.hpp>

Utility::Utility()
{
    //Empty
} // Constructor

void Utility::Set_Processor_Start_Time()
{
    Start_Processor_Tick_Time = (double) cv::getTickCount();
}

double Utility::Calculate_FPS()
{
    return 1/(((double)cv::getTickCount() - Start_Processor_Tick_Time)/cv::getTickFrequency());
}

Utility::~Utility()
{
    // Empty
} // Destructor