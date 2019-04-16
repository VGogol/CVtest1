#include<opencv2\opencv.hpp>
using namespace  cv;

int main()
{
	Mat  image = imread("3.jpg");
	imshow("显示图像", image);
	//进行腐蚀操作
	Mat  element = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat  dstimag;
	erode(image, dstimag, element);
	//显示效果图
	imshow("腐蚀操作效果图", dstimag);
	waitKey(0);
	return 0;
}