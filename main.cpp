#include<opencv2\opencv.hpp>
#include<iostream>
using namespace  cv;
using namespace  std;

#define  _TESTWINDOW_   "线性混合示例"

//图像均值滤波，图像模糊
void GOBlur()
{
	//载入原始图像
	Mat  srcimage = imread("8.jpg");
	//显示
	imshow("均值滤波原图", srcimage);
	//进行均值滤波操作
	Mat  dstimage;
	//用blur函数进行图像模糊以降噪
	blur(srcimage, dstimage, Size(7, 7));
	//显示效果图
	imshow("均值滤波效果图", dstimage);
	waitKey(0);
}

//腐蚀
void  GOErode()
{
	Mat  image = imread("8.jpg");
	imshow("显示图像", image);
	//进行腐蚀操作
	Mat  element = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat  dstimag;
	erode(image, dstimag, element);
	//显示效果图
	imshow("腐蚀操作效果图", dstimag);
	waitKey(0);
}

//Canny边缘检测
void  GOCanny()
{
	Mat  srcimage = imread("8.jpg");
	//显示原图
	imshow("Canny检测原图", srcimage);
	Mat   dstimage, edge, grayimage;
	//创建与src同类型大小的矩阵（dst）
	dstimage.create(srcimage.size(), srcimage.type());

	//将原图转成灰度图像
	//此句为OpenCV2 版本
	//cvtColor(srcimage, grayimage, CV_BGR2GRAY);
	//此句位OpenCV3版
	cvtColor(srcimage, grayimage, COLOR_BGR2GRAY);
	//先使用3X3内核来降噪
	blur(grayimage, edge, Size(3, 3));
	//运行Canny算子
	Canny(edge, edge, 3, 9, 3);
	//显示效果图
	imshow("效果图canny检测", edge);
	waitKey(0);
	return;
}

//读取视频文件
void  GOReadVideo()
{
	while (true)
	{
		//读入视频
		/*VideoCapture   capture("1.flv");*/
		//从摄像头读取视频
		VideoCapture   capture(0);
		while (true)
		{
			Mat  frame;            //用于存储每一帧的图像
			capture >> frame;             //读取当前帧
			imshow("读取视频", frame);
			waitKey(30);                 //延时30ms
		}
		
	}
}

//创建带alpha通道的mat
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

//将png图片写入到当前工程目录下
void  WritePNG()
{
	Mat   mat(480, 640, CV_8UC4);
	CreateAlphaMat(mat);
	vector<int>compression_params;
	compression_params.push_back(IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(9);

	try
	{
		imwrite("生成的透明alpha值图.png", mat, compression_params);
		imshow("生成的PNG图", mat);
		fprintf(stdout, "PNG图片文件的alpha数据保存完毕~\n可以在工程目录下查看由imwrite函数生成的图片\n");
		waitKey(0);
	}
	catch (runtime_error &ex)
	{
		fprintf(stderr, "图像转换成PNG格式发生错误：%s\n", ex.what());

	}
}

//合并图像操作
void   GOUnionImage()
{
	Mat  image1 = imread("3.jpg");
	namedWindow("图片1");
	imshow("图片1", image1);

	//图像混合
	Mat   image = imread("9.jpg", 199);
	Mat   image2 = imread("8.jpg");
	Mat   imageunion;
	//先显示图像
	namedWindow("2原图画");
	imshow("2原图画", image);

	namedWindow("3添加图");
	imshow("3添加图", image2);
	//定义一个Mat类型，用于存放图像ROI
	Mat  imageROI;
	//方法一
	//imageROI = image(Rect(800, 350, image2.cols, image2.rows));
	//方法二           出错
	imageROI = image(Range(100, 100 + image2.rows), Range(300, 300 + image2.cols));
	//将image2加到image
	addWeighted(imageROI, 0.5, image2, 0.5, 3, imageunion);
	//显示结果
	namedWindow("4原画+图");
	imshow("4原画加图", imageunion);
	//将图像保存
	imwrite("合成的图片.jpg", imageunion);
	waitKey(0);
}

//课程3实例代码
int    lesson3()
{
	Mat   image = imread("3.jpg",IMREAD_GRAYSCALE);
	//载入图像失败
	if (image.empty())
	{
		cout << "could not find  the image source.." << endl;
		return -1;
	}
	namedWindow("MyImage", CV_WINDOW_AUTOSIZE);
	imshow("MyImage", image);
	Mat   M;
	M.create(4, 3, CV_8UC2);
	//给每个元素赋值，第一个为127，第二个为111
	M = Scalar(127, 111);
	cout << "M=" << endl << "" << M << endl << endl;
	//返回地（）行的起点
	uchar*firstrow = M.ptr<uchar>(1);
	printf("%d\n", *firstrow);
	Mat  C = (Mat_<double>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	cout << "C=" << endl << "" << C << endl << endl;
	waitKey(0);
	return 0;
}

////////////////////////////////////////////////全局变量声明
const  int  g_nMaxAlphaValue = 100;                  //Alpha值的最大值
int   g_nAlphaValueSlider;                                 ///滑动条对应的变量
double    g_dAlphaValue; 
double    g_dBetaValue;
//声明图像变量
Mat   g_srcImage1;
Mat   g_srcImage2;
Mat   g_dstImage;

////响应滑动条的回调函数,供3.2.1调用
void on_TrackBar(int ,void*)
{
	///求出当前 Alpha值相对于最大值的比例
	g_dAlphaValue = (double)g_nAlphaValueSlider / g_nMaxAlphaValue;
	//beta值为1减去alpha的值
	g_dBetaValue = 1 - g_dAlphaValue;
	//根据alpha值和beta值进行线性混合
	addWeighted(g_srcImage1, g_dAlphaValue, g_srcImage2, g_dBetaValue, 0.0, g_dstImage);
	//显示效果图
	imshow(_TESTWINDOW_, g_dstImage);
}

void  lesson_3_2_1()
{
	//加载图像，两图像尺寸需要一致
	g_srcImage1 = imread("8.jpg");
	g_srcImage2 = imread("9.jpg");
	//载入图像失败
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
	//设置滑动条初始值为70
	g_nAlphaValueSlider = 50;
	//创建窗口
	namedWindow(_TESTWINDOW_, 1);
	//再创建的窗口中创建一个滑动条控件
	char   trackbarname[50];
	sprintf(trackbarname, "透明值%d", g_nMaxAlphaValue);
	createTrackbar(trackbarname, _TESTWINDOW_, &g_nAlphaValueSlider, g_nMaxAlphaValue, on_TrackBar);
	//结果在回调函数中显示
	on_TrackBar(g_nAlphaValueSlider, 0);
	//按任意键退出
	waitKey(0);
	return;

}


void main()
{
	//显示版本
	/*printf("当前OpenCV版本为 OpenCV %s", CV_VERSION);
	system("pause");*/
	//WritePNG();
	//GOUnionImage();
	//GOCanny();
	//腐蚀
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