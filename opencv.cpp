#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>
#include <cv.h>
#include <stdio.h>
#include <opencv\highgui.h>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

Mat cam,frame,src_gray,gaus;
Mat dst, detected_edges,edge;
Mat resized;

int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio = 1;
int kernel_size = 3;
char* window_name = "Edge Map";
int slider_value;
void on_trackbar(int, void*)
{
	cvtColor(cam, src_gray, CV_BGR2GRAY);
	GaussianBlur(src_gray, gaus, Size(3, 3), 0, 0);
	Canny(gaus, detected_edges, 50, 150, 3);
	
	cvtColor(detected_edges, detected_edges, CV_GRAY2BGR);

	double alpha = (double)slider_value / 100.0;
	double beta = (1.0 - alpha);
	dst = Scalar::all(0);
	addWeighted(detected_edges,alpha, cam , beta, 0.0, dst);
	resize(dst, resized, Size(dst.cols / 2.5, dst.rows / 2.5));

	Mat imageROI = frame(Rect(0, 0, resized.cols, resized.rows));
	resized.copyTo(imageROI);
	imshow("Video", frame);
	waitKey(30);
}

int main(int argc, char* argv[])
{
	VideoCapture CapVideo("Logan.mp4"); 
	VideoCapture CapCam(0);
	slider_value = 0;
	int slider_max_value = 100;

	if (!CapVideo.isOpened() || !CapCam.isOpened()) {
		cout << "cannot open the video or camera." << endl;
		return -1;
	}

	namedWindow("Video", 0);

	for (;;) {
		CapVideo.read(frame);
		CapCam >> cam;
		createTrackbar("Ratio", "Video", &slider_value, slider_max_value, on_trackbar);
		on_trackbar(slider_value, 0);
	}
	return 0;
}