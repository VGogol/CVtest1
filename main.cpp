#include<opencv2\opencv.hpp>
using namespace  cv;

int main()
{
	Mat  image = imread("3.jpg");
	imshow("��ʾͼ��", image);
	waitKey(6000);
}