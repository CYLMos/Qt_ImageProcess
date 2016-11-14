#ifndef DECODER_H
#define DECODER_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>


class Decoder
{
public:
    Decoder();
    int decode_and_recover(cv::Mat &image,int peak,int zero);

private:
    int abs(int a);
    int power(int a,int n);
    struct comvalue;
    void find_peak(cv::Mat &image , int &peak,int &zero);
    int decode(cv::Mat &image,int peak,int zero);
    void recover(cv::Mat &image,int peak,int zero);

};

#endif // DECODER_H
