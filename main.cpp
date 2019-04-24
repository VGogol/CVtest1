#include<opencv2\opencv.hpp>
using namespace  cv;
using namespace  std;

//图像模糊
void GOBlur()
{
	//载入原始图像
	Mat  srcimage = imread("8.jpg");
	//显示
	imshow("均值滤波原图", srcimage);
	//进行均值滤波操作
	Mat  dstimage;
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
			Vec4b&rgba = mat.at<	Vec4b>(i, j);
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
		imwrite("透明alpha值图.png", mat, compression_params);
		imshow("生成的PNG图", mat);
		fprintf(stdout, "PNG图片文件的alpha数据保存完毕~\n可以在工程目录下查看由imwrite函数生成的图片\n");
		waitKey(0);
	}
	catch (runtime_error &ex)
	{
		fprintf(stderr, "图像转换成PNG格式发生错误：%s\n", ex.what());

	}
}

void main()
{
	//显示版本
	/*printf("当前OpenCV版本为 OpenCV %s", CV_VERSION);
	system("pause");*/
	WritePNG();
	
	//GOCanny();
	//GOReadVideo();
	//getchar();
	//return 0;
}