#include<opencv2\opencv.hpp>
using namespace  cv;

//ͼ��ģ��
void GOBlur()
{
	//����ԭʼͼ��
	Mat  srcimage = imread("8.jpg");
	//��ʾ
	imshow("��ֵ�˲�ԭͼ", srcimage);
	//���о�ֵ�˲�����
	Mat  dstimage;
	blur(srcimage, dstimage, Size(7, 7));
	//��ʾЧ��ͼ
	imshow("��ֵ�˲�Ч��ͼ", dstimage);
	waitKey(0);
}

//��ʴ
void  GOErode()
{
	Mat  image = imread("8.jpg");
	imshow("��ʾͼ��", image);
	//���и�ʴ����
	Mat  element = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat  dstimag;
	erode(image, dstimag, element);
	//��ʾЧ��ͼ
	imshow("��ʴ����Ч��ͼ", dstimag);
	waitKey(0);
}

//Canny��Ե���
void  GOCanny()
{
	Mat  srcimage = imread("8.jpg");
	//��ʾԭͼ
	imshow("Canny���ԭͼ", srcimage);
	Mat   dstimage, edge, grayimage;
	//������srcͬ���ʹ�С�ľ���dst��
	dstimage.create(srcimage.size(), srcimage.type());

	//��ԭͼת�ɻҶ�ͼ��
	//�˾�ΪOpenCV2 �汾
	//cvtColor(srcimage, grayimage, CV_BGR2GRAY);
	//�˾�λOpenCV3��
	cvtColor(srcimage, grayimage, COLOR_BGR2GRAY);
	//��ʹ��3X3�ں�������
	blur(grayimage, edge, Size(3, 3));
	//����Canny����
	Canny(edge, edge, 3, 9, 3);
	//��ʾЧ��ͼ
	imshow("Ч��ͼcanny���", edge);
	waitKey(0);
	return;
}

//��ȡ��Ƶ�ļ�
void  GOReadVideo()
{
	while (true)
	{
		//������Ƶ
		/*VideoCapture   capture("1.flv");*/
		//������ͷ��ȡ��Ƶ
		VideoCapture   capture(0);
		while (true)
		{
			Mat  frame;            //���ڴ洢ÿһ֡��ͼ��
			capture >> frame;             //��ȡ��ǰ֡
			imshow("��ȡ��Ƶ", frame);
			waitKey(30);                 //��ʱ30ms
		}
		
	}
}

int main()
{
	//GOCanny();
	GOReadVideo();
	
	return 0;
}