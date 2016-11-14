#ifndef ENCODER_H
#define ENCODER_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>


class Encoder
{
public:
    Encoder();
    void encode(cv::Mat &image , int &peak,int &zero,int &peak_c,int ciphertext);

private:
    int abs(int a);
    struct comvalue;
    void find_peak(cv::Mat &image , int &peak,int &zero,int &peak_c);
    void hide(cv::Mat &image,int peak,int zero,int hi,int peak_c);

};

#endif // ENCODER_H
