#include "Encoder.h"

Encoder::Encoder()
{

}

struct Encoder::comvalue{
    bool operator()(std::pair<int,int> &lef , std::pair<int,int> &rig)
    {
        return (lef.second) < (rig.second);
    }

};

void Encoder::encode(cv::Mat &image , int &peak,int &zero,int &peak_c,int ciphertext){
    this->find_peak(image,peak,zero,peak_c);
    this->hide(image,peak,zero,ciphertext,peak_c);
}

int Encoder::abs(int a){
    a = a < 0 ? -a : a;
    return a;
}

void Encoder::find_peak(cv::Mat &image , int &peak,int &zero,int &peak_c){
    std::map<int,int> my;
    std::vector< std::pair<int,int> >::iterator itr;

    for(int o=0;o<256;o++)
        my[o]++;
    for(int i=0;i<image.rows;i++)
    {
        for(int j=0;j<image.cols;j++)
        {
                int a = image.at<cv::Vec3b>(i,j)[0];
                my[a]++;
        }
    }

    std::vector< std::pair<int,int> > vec(my.begin(),my.end());
    std::sort(vec.begin(),vec.end(),comvalue());
    /*int jj=0;
    for(itr = vec.begin();itr!=vec.end();++itr)
    {
        jj++;
        if(jj%9 == 0) cout<<endl;
        //cout<<setw(3)<<itr->first<<":"<<setw(3)<<itr->second<<"  ";
        printf("%4d:%4d|",itr->first,itr->second);
    }*/

    peak = vec.rbegin()->first;
    peak_c = vec.rbegin()->second;
    //cout<<"----------------------"<<peak_c<<endl;
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

void Encoder::hide(cv::Mat &image,int peak,int zero,int hi,int peak_c){
    if(zero > peak)
    {
        for(int n=zero-1;n>peak;n--)
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
        for(int n=zero+1;n<peak;n++)
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

    int i=0,a[99];
    while(hi>0)
    {
        a[i++]=hi%2;
        hi=hi/2;
    }
    i--;
    //cout<<"i="<<i<<"*********************peak_c="<<peak_c<<endl;

    int temp_i=i;

    for(int k=0;k<image.rows;k++)
    {
        for(int j=0;j<image.cols;j++)
        {
            if(image.at<cv::Vec3b>(k,j)[0]==peak)
            {
                //cout<<image.at<uchar>(k,j)<<" ";
                peak_c--;
                if(peak_c<temp_i+2){
                    //cout<<"k="<<k<<" j="<<j<<endl;
                    //cout<<"-------i"<<i<<" "<<al<<endl;
                    if(a[i--]==1){
                        if(zero > peak)
                            image.at<cv::Vec3b>(k,j)[0]+=1;
                        if(zero < peak)
                            image.at<cv::Vec3b>(k,j)[0]-=1;
                    }
                }
            }
        }
    }

}
