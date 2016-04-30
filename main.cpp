#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;
using namespace cv;

Mat convertToGrayScale(Mat inputImage)
{
	Mat outputImage;

	cvtColor(inputImage, outputImage, CV_BGR2GRAY);

	return outputImage;
}

Mat blur(Mat inputImage)
{
	Mat outputImage;

	blur(inputImage, outputImage, Size(50, 50));

	return outputImage;
}

Mat rotate90(Mat inputImage)
{
	Mat outputImage;
	double angle = 90;  // or 270

	Size src_sz = inputImage.size();
	Size dst_sz(src_sz.height, src_sz.width);

	int len = max(inputImage.cols, inputImage.rows);
	Point2f center(len/2., len/2.);
	Mat rot_mat = getRotationMatrix2D(center, angle, 1.0);
	warpAffine(inputImage, outputImage, rot_mat, dst_sz);

	return outputImage;
}


int main()
{
	const char *exampleSample = "../mag_tester/probki/SkanyRazem/dokument004.jpg";
	const char *windowName = "probka";
	struct stat sb;
	Mat image;

	if(stat(exampleSample, &sb) == -1)
	{
		cout << "File " << exampleSample << " cannot be accessed!";
	}

	image = imread(exampleSample, 1);

	//convert to grayscale
	image = convertToGrayScale(image);

	//rotate90
	image = rotate90(image);

	//display image
	namedWindow(windowName, CV_WINDOW_NORMAL);
	imshow(windowName, image);

	while(true)
	{
		int c;
		c = waitKey(20);
		if((char)c == 27)
			break;
	}

	return 0;
}
