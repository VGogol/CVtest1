#include<opencv2\opencv.hpp>
using namespace  cv;
using namespace  std;

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

//������alphaͨ����mat
void  CreateAlphaMat(Mat  &mat)
{
	for (int i = 0; i < mat.rows; i++)
	{
		for (int j = 0; j < mat.cols; j++)
		{
			Vec4b&rgba = mat.at<	Vec4b>(i, j);
			rgba[0] = UCHAR_MAX;
			rgba[1] = saturate_cast<uchar>((float(mat.cols - j)) / ((float)mat.cols)*UCHAR_MAX);
			rgba[2] = saturate_cast<uchar>((float(mat.rows - i)) / ((float)mat.rows)*UCHAR_MAX);
			rgba[3] = saturate_cast < uchar > (0.5*(rgba[1] + rgba[2]));
		}
	}
}

//��pngͼƬд�뵽��ǰ����Ŀ¼��
void  WritePNG()
{
	Mat   mat(480, 640, CV_8UC4);
	CreateAlphaMat(mat);
	vector<int>compression_params;
	compression_params.push_back(IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(9);

	try
	{
		imwrite("͸��alphaֵͼ.png", mat, compression_params);
		imshow("���ɵ�PNGͼ", mat);
		fprintf(stdout, "PNGͼƬ�ļ���alpha���ݱ������~\n�����ڹ���Ŀ¼�²鿴��imwrite�������ɵ�ͼƬ\n");
		waitKey(0);
	}
	catch (runtime_error &ex)
	{
		fprintf(stderr, "ͼ��ת����PNG��ʽ��������%s\n", ex.what());

	}
}

void main()
{
	//��ʾ�汾
	/*printf("��ǰOpenCV�汾Ϊ OpenCV %s", CV_VERSION);
	system("pause");*/
	WritePNG();
	
	//GOCanny();
	//GOReadVideo();
	//getchar();
	//return 0;
}