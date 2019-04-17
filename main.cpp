#include<opencv2\opencv.hpp>
using namespace  cv;

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

int main()
{
	//GOCanny();
	GOReadVideo();
	
	return 0;
}