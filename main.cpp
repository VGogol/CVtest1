#include<opencv2\opencv.hpp>
using namespace  cv;

int main()
{
	Mat  image = imread("3.jpg");
	imshow("ÏÔÊ¾Í¼Ïñ", image);
	waitKey(6000);
}