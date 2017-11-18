#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
using namespace std;
using namespace cv;

//draw rectangle function
void draw_rect(Mat& src, Point p1, Point p2)
{
	rectangle(src, p1, p2, Scalar(0, 0, 255));
}

bool click_flag = false;
Point click_left;

//define mouse event  function
void on_Mouse(int event, int x1, int y1, int flag, void* para)
{
	Point p1, p2;
	Mat& img = *static_cast<Mat *>(para);
	if(event == EVENT_LBUTTONDOWN)
		{
			click_flag = true;
			cout << "(" << x1 <<","<< y1 << ")" << endl;
			click_left = Point(x1, y1);
		}
	else if(click_flag && event == EVENT_RBUTTONDOWN)
	{
		cout << "(" << x1 <<","<< y1 << ")" << endl;
		p1.x = click_left.x;
		p1.y = click_left.y;
		p2 = Point(x1, y1);
		draw_rect(img, p1, p2);
		click_flag = false;
	}
}

int main()
{
	
	Mat img; string winname = "！！！！栖心厘！！！！";
	img = imread("meinv.jpg");
	namedWindow(winname, CV_WINDOW_AUTOSIZE);
	setMouseCallback(winname, on_Mouse, (void*)& img);
	while(1)
	{
		imshow(winname, img);
		if(waitKey(2) == 27)
		{
			destroyWindow(winname);
			break;
		}
	}
	imwrite("plot.jpg", img);
	return 0;
}