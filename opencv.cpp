// opencv.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
/*#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
VideoCapture cap("video.mp4"); // open the video file for reading
VideoCapture capcam(0);

if (!cap.isOpened())  // if not success, exit program
{
cout << "Cannot open the video file" << endl;
return -1;
}

//cap.set(CV_CAP_PROP_POS_MSEC, 300); //start the video at 300ms

double fps = cap.get(CV_CAP_PROP_FPS); //get the frames per seconds of the video
double Width = capcam.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
double Height = capcam.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

cout << "Frame per seconds : " << fps << endl;

namedWindow("MyVideo", CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"

while (1)
{
Mat frame, frame1;
cap >> frame;
capcam >> frame1;
//show the frame in "MyVideo" window
for (int i = 0; i < Width; i++) {
for (int j = 0; j < Height; j++) {
frame.at<Vec3b>(j, i)[0] = frame1.at<Vec3b>(j, i)[0]; //B
frame.at<Vec3b>(j, i)[1] = frame1.at<Vec3b>(j, i)[1];//G
frame.at<Vec3b>(j, i)[2] = frame1.at<Vec3b>(j, i)[2];//R
}
}
imshow("MyVideo", frame);

if (waitKey(30) == 27) //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
{
cout << "esc key is pressed by user" << endl;
break;
}
}

return 0;

}*/

#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <cv.h>
//#include <stdio.h>
//#include <opencv\highgui.h>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

Mat src, src_gray;
Mat dst, detected_edges;

int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio = 1;
int kernel_size = 3;
char* window_name = "Edge Map";

/*void on_trackbar(int, void*) {
	double alpha = (double)slider_value/100.0;
	double beta = (1.0 - alpha);
	//Mat dst;

	addWeighted(src1,alpha,src1,beta,0.0,dst);
//	imshow("MyVideo", dst);
}*/

void CannyThreshold(int, void*)
{
	/// Reduce noise with a kernel 3x3
	//blur(src_gray, detected_edges, Size(3, 3));
	cvtColor(src, src_gray, CV_BGR2GRAY);
	/// Canny detector
	Canny(src_gray, detected_edges,20,60,3);

	/// Using Canny's output as a mask, we display our result
	dst = Scalar::all(0);
	double alpha = (double)0 / 100.0;
	double beta = (1.0 - alpha);
	//src.copyTo(dst, detected_edges);
	addWeighted(src, alpha,detected_edges , beta, 0.0, dst);
	imshow("MyVideo", dst);
}


int main(int argc, char* argv[])
{
	VideoCapture cap(0); // open the video camera no. 0

	if (!cap.isOpened())  // if not success, exit program
		return -1;

	/*Mat edges;
	namedWindow("MyVideo", CV_WINDOW_FREERATIO); //create a window called "MyVideo"
	slider_value = 0;
	int slider_max_value = 100;

	createTrackbar("Ratio", "MyVideo", &slider_value, slider_max_value, on_trackbar);*/
	for(;;)
	{
		//Mat gray;
		cap >> src; // read a new frame from video
		/*cvtColor(src1,gray,CV_BGR2GRAY);
		Canny(gray,src2,20,60,3);*/
		
		/// Create a matrix of the same type and size as src (for dst)
		dst.create(src.size(), src.type());

		/// Convert the image to grayscale
		cvtColor(src, src_gray, CV_BGR2GRAY);

		/// Create a window
		namedWindow("MyVideo", CV_WINDOW_AUTOSIZE);
		
		/// Create a Trackbar for user to enter threshold
		createTrackbar("Ratio:", "MyVideo", &lowThreshold, max_lowThreshold, CannyThreshold);

		/// Show the image
		CannyThreshold(0, 0);


		/*on_trackbar(slider_value,0);
		imshow("MyVideo", dst);*/
		if (waitKey(30) == 27) break; //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
	}
	return 0;
	
}
/*
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
VideoCapture CapVideo("video .mp4");  // open the video file for reading
if (!CapVideo.isOpened())  // if not success, exit program
{
cout << "Cannot open the video file" << endl;
return -1;
}
VideoCapture CapCamera(0); 	        // open the video camera no. 0
if (!CapCamera.isOpened())  // if not success, exit program
{
cout << "Cannot open the video cam" << endl;
return -1;
}

//cap.set(CV_CAP_PROP_POS_MSEC, 300); //start the video at 300ms

//double fps = cap.get(CV_CAP_PROP_FPS); //get the frames per seconds of the video

//cout << "Frame per seconds : " << fps << endl;

namedWindow("VideoWindow", CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"

while (1)
{
Mat frameVid,frameCam;

bool bSuccess = CapVideo.read(frameVid); // read a new frame from video
bool aSuccess = CapCamera.read(frameCam);

if (!bSuccess || !aSuccess) 			 //if not success, break loop
{
cout << "Cannot read the frame from video file" << endl;
break;
}

imshow("VideoWindow", frameVid); //show the frame in "MyVideo" window
imshow("CameraWindow", frameCam);
}

return 0;

}*/