#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
using namespace std;
using namespace cv;
#include<string>

int main()
{
	//input and output
	string video_path = "2.MP4", output_video = "out.avi";
	int crop_x = 1000; int crop_y = 700; int crop_w = 1800; int crop_h = 1000;
	
	//define read and write video
	VideoCapture cap; VideoWriter writer;
	cap.open(video_path);
	writer.open(output_video, CV_FOURCC('M', 'J', 'P', 'G'), cap.get(CV_CAP_PROP_FPS), Size(static_cast<int>(cap.get(CV_CAP_PROP_FRAME_WIDTH)), static_cast<int>(cap.get(CV_CAP_PROP_FRAME_HEIGHT))), true);
	
	//print some information about video
	cout << cap.get(CV_CAP_PROP_FRAME_WIDTH) << endl;
	cout << cap.get(CV_CAP_PROP_FRAME_HEIGHT) << endl;

	//define crop area of frame
	Mat frame, crop_frame;
	string win_name = "see me", str;
	Rect rect(crop_x, crop_y, crop_w, crop_h);
	Point point1(crop_x, crop_y); Point point2(crop_x + crop_w, crop_y + crop_h);

	while(true)
	{
		cap >> frame;
		frame(rect).copyTo(crop_frame);
		//plot rectangle with read line
		rectangle(frame, point1, point2, Scalar(0, 0, 255));
		namedWindow(win_name, WINDOW_AUTOSIZE);
		writer << frame;
 		imshow(win_name, frame);
		if(waitKey(1) == 27)
		{
			destroyWindow(win_name);
			break;
		}
	}
	return 0;
}