#include<opencv2\opencv.hpp>
#include<iostream>
using namespace  cv;
using namespace  std;

#define  _TESTWINDOW_   "���Ի��ʾ��"

//ͼ���ֵ�˲���ͼ��ģ��
void GOBlur()
{
	//����ԭʼͼ��
	Mat  srcimage = imread("8.jpg");
	//��ʾ
	imshow("��ֵ�˲�ԭͼ", srcimage);
	//���о�ֵ�˲�����
	Mat  dstimage;
	//��blur��������ͼ��ģ���Խ���
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
			Vec4b&rgba = mat.at<Vec4b>(i, j);
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
		imwrite("���ɵ�͸��alphaֵͼ.png", mat, compression_params);
		imshow("���ɵ�PNGͼ", mat);
		fprintf(stdout, "PNGͼƬ�ļ���alpha���ݱ������~\n�����ڹ���Ŀ¼�²鿴��imwrite�������ɵ�ͼƬ\n");
		waitKey(0);
	}
	catch (runtime_error &ex)
	{
		fprintf(stderr, "ͼ��ת����PNG��ʽ��������%s\n", ex.what());

	}
}

//�ϲ�ͼ�����
void   GOUnionImage()
{
	Mat  image1 = imread("3.jpg");
	namedWindow("ͼƬ1");
	imshow("ͼƬ1", image1);

	//ͼ����
	Mat   image = imread("9.jpg", 199);
	Mat   image2 = imread("8.jpg");
	Mat   imageunion;
	//����ʾͼ��
	namedWindow("2ԭͼ��");
	imshow("2ԭͼ��", image);

	namedWindow("3���ͼ");
	imshow("3���ͼ", image2);
	//����һ��Mat���ͣ����ڴ��ͼ��ROI
	Mat  imageROI;
	//����һ
	//imageROI = image(Rect(800, 350, image2.cols, image2.rows));
	//������           ����
	imageROI = image(Range(100, 100 + image2.rows), Range(300, 300 + image2.cols));
	//��image2�ӵ�image
	addWeighted(imageROI, 0.5, image2, 0.5, 3, imageunion);
	//��ʾ���
	namedWindow("4ԭ��+ͼ");
	imshow("4ԭ����ͼ", imageunion);
	//��ͼ�񱣴�
	imwrite("�ϳɵ�ͼƬ.jpg", imageunion);
	waitKey(0);
}

//�γ�3ʵ������
int    lesson3()
{
	Mat   image = imread("3.jpg",IMREAD_GRAYSCALE);
	//����ͼ��ʧ��
	if (image.empty())
	{
		cout << "could not find  the image source.." << endl;
		return -1;
	}
	namedWindow("MyImage", CV_WINDOW_AUTOSIZE);
	imshow("MyImage", image);
	Mat   M;
	M.create(4, 3, CV_8UC2);
	//��ÿ��Ԫ�ظ�ֵ����һ��Ϊ127���ڶ���Ϊ111
	M = Scalar(127, 111);
	cout << "M=" << endl << "" << M << endl << endl;
	//���صأ����е����
	uchar*firstrow = M.ptr<uchar>(1);
	printf("%d\n", *firstrow);
	Mat  C = (Mat_<double>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	cout << "C=" << endl << "" << C << endl << endl;
	waitKey(0);
	return 0;
}

////////////////////////////////////////////////ȫ�ֱ�������
const  int  g_nMaxAlphaValue = 100;                  //Alphaֵ�����ֵ
int   g_nAlphaValueSlider;                                 ///��������Ӧ�ı���
double    g_dAlphaValue; 
double    g_dBetaValue;
//����ͼ�����
Mat   g_srcImage1;
Mat   g_srcImage2;
Mat   g_dstImage;

////��Ӧ�������Ļص�����,��3.2.1����
void on_TrackBar(int ,void*)
{
	///�����ǰ Alphaֵ��������ֵ�ı���
	g_dAlphaValue = (double)g_nAlphaValueSlider / g_nMaxAlphaValue;
	//betaֵΪ1��ȥalpha��ֵ
	g_dBetaValue = 1 - g_dAlphaValue;
	//����alphaֵ��betaֵ�������Ի��
	addWeighted(g_srcImage1, g_dAlphaValue, g_srcImage2, g_dBetaValue, 0.0, g_dstImage);
	//��ʾЧ��ͼ
	imshow(_TESTWINDOW_, g_dstImage);
}

void  lesson_3_2_1()
{
	//����ͼ����ͼ��ߴ���Ҫһ��
	g_srcImage1 = imread("8.jpg");
	g_srcImage2 = imread("9.jpg");
	//����ͼ��ʧ��
	if (!g_srcImage1.data)
	{
		cout << "could not find  the image1 source.." << endl;
		return;
	}
	if (!g_srcImage2.data)
	{
		cout << "could not find the image2 soure .." << endl;
		return;
	}
	//���û�������ʼֵΪ70
	g_nAlphaValueSlider = 50;
	//��������
	namedWindow(_TESTWINDOW_, 1);
	//�ٴ����Ĵ����д���һ���������ؼ�
	char   trackbarname[50];
	sprintf(trackbarname, "͸��ֵ%d", g_nMaxAlphaValue);
	createTrackbar(trackbarname, _TESTWINDOW_, &g_nAlphaValueSlider, g_nMaxAlphaValue, on_TrackBar);
	//����ڻص���������ʾ
	on_TrackBar(g_nAlphaValueSlider, 0);
	//��������˳�
	waitKey(0);
	return;

}


void main()
{
	//��ʾ�汾
	/*printf("��ǰOpenCV�汾Ϊ OpenCV %s", CV_VERSION);
	system("pause");*/
	//WritePNG();
	//GOUnionImage();
	//GOCanny();
	//��ʴ
	//GOErode();
	//GOReadVideo();
	//getchar();
	//return 0;
	//if (-1 == GOUnionImage())
	//{
	//	return;
	//}
	lesson_3_2_1();
}