#include<opencv2\opencv.hpp>
using namespace  cv;

int main()
{
	Mat  image = imread("3.jpg");
	imshow("��ʾͼ��", image);
	//���и�ʴ����
	Mat  element = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat  dstimag;
	erode(image, dstimag, element);
	//��ʾЧ��ͼ
	imshow("��ʴ����Ч��ͼ", dstimag);
	waitKey(0);
	return 0;
}