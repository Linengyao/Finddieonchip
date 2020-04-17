// Finddieonchip.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <opencv.hpp>

using namespace cv;
using namespace std;
int main()
{
	cv::Mat srcMat = imread("E:\\课程\\大二下\\数字图像处理\\die_on_chip.png",0);
	cv::Mat Result	=imread("E:\\课程\\大二下\\数字图像处理\\die_on_chip.png");

	cv::Mat	BinaryMat;
	cv::Mat	OpenMat;
	cv::Mat GaussFilterMat;

	//二值化
	threshold(srcMat, BinaryMat, 125, 175, THRESH_BINARY);
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(BinaryMat, OpenMat, MORPH_OPEN, element);			//开运算

	//GaussianBlur(BinaryMat, GaussFilterMat, Size(3, 3), 2,2, BORDER_DEFAULT);//高斯滤波

	vector<vector<Point>> contours;
	findContours(OpenMat, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	for (int i = 0; i < contours.size(); i++)
	{
		//获得最小外接四边形
		RotatedRect rbox = minAreaRect(contours[i]);

		float width = rbox.size.width;
		float height = rbox.size.height;
		float proportion = width / height;
		float pixelsum = width * height;
		if (pixelsum > 1000)
		{
			if (fabs(proportion - 1) < 0.1)
			{
				cv::Point2f vtx[4];
				rbox.points(vtx);
				for (int i = 0; i < 4; ++i)
				{
					cv::line(Result, vtx[i], vtx[i < 3 ? i + 1 : 0], cv::Scalar(0, 0, 255), 2, CV_AA);
				}
			//绘制轮廓
			drawContours(Result, contours, i, Scalar(0, 255, 255), 1, 8);

			}
		}

	}

	imshow("srcMat", srcMat);
	imshow("binaryMat", BinaryMat);
	//imshow("OpenMat", OpenMat);
	//imshow("GaussFilterMat", GaussFilterMat);


	imshow("Result", Result);
	waitKey(0);

    //std::cout << "Hello World!\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
