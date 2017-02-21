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

Mat cam,src_gray;
Mat dst, detected_edges;

int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio = 1;
int kernel_size = 3;
char* window_name = "Edge Map";

/*void on_trackbar(int, void*) {
	double alpha = (double)slider_value / 100.0;
	double beta = (1.0 - alpha);
	Mat dst;

	addWeighted(src, alpha, src1, beta, 0.0, dst);
	imshow("Video", dst);
}*/

void CannyThreshold(int, void*)
{
	/// Reduce noise with a kernel 3x3
	blur(src_gray, detected_edges, Size(3, 3));
	//cvtColor(src, src_gray, CV_BGR2GRAY);
	/// Canny detector
	Canny(src_gray, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size);

	/// Using Canny's output as a mask, we display our result
	dst = Scalar::all(0);
	//double alpha = (double)0 / 100.0;
	//double beta = (1.0 - alpha);
	cam.copyTo(dst, detected_edges);
	//addWeighted(src, alpha,detected_edges , beta, 0.0, dst);
	//imshow("Video", dst);
}

int main(int argc, char* argv[])
{
	Mat frame;
	VideoCapture CapVideo("video.mp4");  // open the video file for reading
	VideoCapture CapCam(0);
	CapCam.set(CV_CAP_PROP_FRAME_WIDTH, 200);
	CapCam.set(CV_CAP_PROP_FRAME_HEIGHT, 150);
	int slider_value = 0;
	int slider_max_value = 100;
	//createTrackbar("Ratio", "Video", &slider_value, slider_max_value, on_trackbar);
	if (!CapVideo.isOpened() || !CapCam.isOpened()) {
		cout << "cannot open the video or camera." << endl;
		return -1;
	}
	
	for (;;) {
		namedWindow("Video", CV_WINDOW_AUTOSIZE);
		Mat gray;
		CapVideo.read(frame);
		CapCam >> cam;

		/// Create a matrix of the same type and size as src (for dst)
		dst.create(cam.size(), cam.type());
		/// Convert the image to grayscale
		cvtColor(cam, src_gray, CV_BGR2GRAY);
		/// Create a Trackbar for user to enter threshold
		createTrackbar("Ratio:", "Video", &lowThreshold, max_lowThreshold, CannyThreshold);

		/// Show the image
		CannyThreshold(0, 0);
		//on_trackbar(slider_value, 0);
		Mat imageROI = frame(Rect(0,0,dst.cols,dst.rows));
		dst.copyTo(imageROI, dst);
		imshow("Video",dst);
		waitKey(30);
	}
	return 0;
}