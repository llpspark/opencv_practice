#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
using namespace std;
using namespace cv;


void draw_rect(Mat& src, Point p1, Point p2)
{
	rectangle(src, p1, p2, Scalar(0, 0, 255));
}

vector<string> read_substr(string str, string pattern)
{
	vector<string> sub;
	string :: size_type pos; unsigned int len;
	while(str.find(pattern, 0) != string::npos)
	{
		len = str.size();
		pos = str.find(pattern, 0);
		sub.push_back(str.substr(0, pos));
		str = str.substr(pos + 1, len - pos -1);
	}
	sub.push_back(str);
	return sub;

}

void on_Mouse(int event, int x1, int y1, int flag, void* para)
{
	fstream file;
	Mat& img = *static_cast<Mat *>(para);
	if(event == EVENT_LBUTTONDOWN)
		{
			cout << "(" << x1 <<","<< y1 << ")" << endl;
			//draw_point(img, x, y);
			file.open("a.txt", ios::app|ios::out);
			file << x1 << " " << y1 << endl;
			file.close();
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
	fstream file;
	file.open("a.txt", ios:: in);
	Point p1, p2;

	string str; vector<string> sub;
	getline(file, str);
	sub = read_substr(str, " ");
	p1.x = atoi(sub[0].c_str());
	p1.y = atoi(sub[1].c_str());
	getline(file, str);
	sub = read_substr(str, " ");
	p2.x = atoi(sub[0].c_str());
	p2.y = atoi(sub[1].c_str());

	file.close();
	draw_rect(img, p1, p2);
	imshow(winname, img);
	waitKey(2222);
	imwrite("plot.jpg", img);

	return 0;
}