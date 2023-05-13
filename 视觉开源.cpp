#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <vector>
using namespace std;
using namespace cv;

class low      //对低级别图片的预处理方法
{  
public:
    Mat low_img;   //读取图片的接口
    Mat gray;
    Mat transformer()
    {
    //转换成灰度图
    cvtColor(low_img,gray,COLOR_BGR2GRAY);
    //全局二值化
    threshold(gray,bin,0,255,THRESH_BINARY|THRESH_OTSU);
    if (bin.empty()) return low_img;
    else return bin;
    }
private:
    //储存转换后的图片
    Mat bin;
};
class mid_high   //对中、高级图片的预处理方法
{
public:
    Mat high_img,median,hsv_img,mask;
    //定义转换颜色空间的函数
    Mat transformer()
    {
        medianBlur(high_img,median,(7,7));
        cvtColor(median,hsv_img,COLOR_BGR2HSV);
        //读取图片左上角像素点的HSV值并储存于相应成员变量
        Vec3b left_upside = hsv_img.at<Vec3b>(Point(0,0));
        int h_left_upside = left_upside[0];
        int s_left_upside = left_upside[1];
        int v_left_upside = left_upside[2];
        //储存inRange函数所需要的颜色阈值,可适当上下调节
        Scalar lower_color,upper_color;
        lower_color = Scalar((0.96*h_left_upside)/1,(0.7*s_left_upside)/1,(0.8*v_left_upside)/1);
        upper_color = Scalar((1.04*h_left_upside)/1,255,255);
        inRange(hsv_img,lower_color,upper_color,mask);
        Mat zhong;
        //方便观察
        bitwise_not(mask,zhong);
        //做开运算，消除残留的噪声
        Mat kernel = getStructuringElement(MORPH_RECT,Size(5,5));
        morphologyEx(zhong,oppo,MORPH_OPEN,kernel);
        return oppo;
    }
private:
    //存储最终所需图片
    Mat oppo;
    
};

void recognition(Mat img,Mat clo)  //对预处理得到的图片，寻找角点，识别出来
{
    vector<vector<Point>> contours;   //存放轮廓的角点
    vector<Vec4i> hierarchy;          
    findContours(img,contours,hierarchy,RETR_TREE,CHAIN_APPROX_SIMPLE);
    vector<vector<Point>> con(contours.size());
    for (int i=0;i<contours.size();i++)
    {
        double area = contourArea(contours[i]);
        double peri = arcLength(contours[i],true);
        Scalar color = Scalar(0,0,255);
        String objname;
        if (area > 600)
        {    //可上下调节阈值，避免识别的误差
             approxPolyDP(contours[i],con[i],0.025*peri,true);
             //定义角点
             int Line = con[i].size();
             //没有用switch结构
             if (Line == 3)
             {
                objname = "3";
             }
             if (Line == 4)
             {
                objname = "4";
             }
             if (Line == 5)
             {
                objname ="5";
             }
             if (Line == 6)
             {
                objname = "6";
             }
             if (Line == 7)
             {
                objname = "7";
             }
             if (Line == 8)
             {
                objname = "8";
             }
             if (Line == 9)
             {
               objname = "9";
             }
             if (Line == 10)
             {
                objname ="Star";
             }
             //在多边形上画框
             Rect rect = boundingRect(con[i]);
             rectangle(clo,rect,color,2);
             putText(clo,objname,rect.tl(),FONT_HERSHEY_SIMPLEX,1,color,2);
        }
    }
}

int main()
{   
    mid_high hi;
    //读入图片
    Mat picture = imread("/home/zhouhao/test/school_robo/high/2.jpg");
    hi.high_img = picture.clone(); 
    Mat hs = hi.transformer();
    Mat clo = picture.clone();
    printf("H: %d , S: %d , V: %d", h_left_upside,s_left_upside,v_left_upside);
    recognition(hs,clo);
    imshow("window",clo);
    waitKey(0);
    system("pause");
    return 0;
}
