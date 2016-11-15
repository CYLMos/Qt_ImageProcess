#include "Decoder.h"

Decoder::Decoder()
{

}

int Decoder::decode_and_recover(cv::Mat &image,int peak,int zero){
    int result = 0;
    result = this->decode(image,peak,zero);
    //this->recover(image,peak,zero);
    //this->find_peak(image,peak,zero);

    return result;
}

struct Decoder::comvalue{
    bool operator()(std::pair<int,int> &lef , std::pair<int,int> &rig)
    {
        return (lef.second) < (rig.second);
    }
};

int Decoder::abs(int a){
    a = a < 0 ? -a : a;
    return a;
}

int Decoder::power(int a,int n){
    int to=1;
    for(int i=0;i<n;i++)
    {
        to*=a;
    }
    return to;

}

void Decoder::find_peak(cv::Mat &image , int &peak,int &zero){
    std::map<int,int> my;
    std::vector< std::pair<int,int> >::iterator itr;

    for(int o=0;o<256;o++)
        my[o]++;
    for(int i=0;i<image.rows;i++)
    {
        for(int j=0;j<image.cols;j++)
        {
            int a = image.at<cv::Vec3b>(i,j)[1];
            my[a]++;
        }
    }
    std::vector< std::pair<int,int> > vec(my.begin(),my.end());
    std::sort(vec.begin(),vec.end(),comvalue());
    int jj=0;
    for(itr = vec.begin();itr!=vec.end();++itr)
    {
        jj++;
        //if(jj%9==0) cout<<endl;
        //cout<<itr->first<<"  "<<itr->second<<endl;
        //printf("%4d:%4d|",itr->first,itr->second);
    }

    peak = vec.rbegin()->first;
    zero = vec.begin()->first;
    int zero2 = vec.begin()->second;
    int mine=256;
    for(itr = vec.begin();itr!=vec.end();++itr)
    {
        if( (itr->second) == zero2 && this->abs(peak-(itr->first)) < mine  )
        {
            mine = this->abs(peak-(itr->first));
            zero = itr->first;

        }
    }

}

int Decoder::decode(cv::Mat &image,int peak,int zero){
    bool sav=false;
    std::list<int> deq;
    //std::list<int> test;
    int n = 0;
    for(int i=0;i<image.rows;i++)
    {
        for(int j=0;j<image.cols;j++)
        {
            //test.push_back(image.at<uchar>(i,j));
            //if((int)image.at<uchar>(i,j) == 153){n++;}
            if(image.at<cv::Vec3b>(i,j)[0] == (peak+1))
            {
                //cout<<"p:"<<peak+1<<"  1"<<endl;
                //cout<<"k="<<i<<" j="<<j<<endl;
                sav=true;
                deq.push_back(1);
                image.at<cv::Vec3b>(i,j)[0]=peak;
            }
            else if((sav == true) && (image.at<cv::Vec3b>(i,j)[0]==peak))
            {
                //cout<<"k="<<i<<"j="<<j<<endl;
                deq.push_back(0);
            }
        }

    }
    int deq_size = deq.size();
    int total=0;
    for(int i=0;i<deq_size;i++)
    {

        total+=(deq.front()*power(2,deq_size-(i+1)));
        deq.pop_front();
    }
    return total;
}

void Decoder::recover(cv::Mat &image,int peak,int zero){
    if(peak > zero)
    {
        for(int n=peak-2;n>=zero;n--)
        {
            for(int i=0;i<image.rows;i++)
            {
                for(int j=0;j<image.cols;j++)
                {
                    if(image.at<cv::Vec3b>(i,j)[0]==n)
                        image.at<cv::Vec3b>(i,j)[0]+=1;
                }
            }
        }
    }
    else
    {
        for(int n=peak+2;n<=zero;n++)
        {
            for(int i=0;i<image.rows;i++)
            {
                for(int j=0;j<image.cols;j++)
                {
                    if(image.at<cv::Vec3b>(i,j)[0]==n)
                        image.at<cv::Vec3b>(i,j)[0]-=1;
                }
            }
        }
    }
}
