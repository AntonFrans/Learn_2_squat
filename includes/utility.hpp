#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <opencv2/opencv.hpp>

class Utility{

private:
double Start_Processor_Tick_Time;

public:
void Set_Processor_Start_Time();

double Calculate_Time_Taken();

};

#endif