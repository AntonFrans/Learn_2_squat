#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <opencv2/opencv.hpp>

class Utility{

private:
double Start_Processor_Tick_Time;

public:
Utility();

void Set_Processor_Start_Time();

double Calculate_FPS();

~Utility();
};

#endif