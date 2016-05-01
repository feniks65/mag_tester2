#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static const unsigned int Threshold = 180;

using namespace std;
using namespace cv;

//image.at<Vec3b>(Point(x,y)) = color; //wstawia w x,y jakąś barwę

int* countBlackPixs(Mat inputImage)
{
	int *countedBlacks = new int[inputImage.cols];

	for(int i=0; i < inputImage.cols; i++)
	{
		countedBlacks[i] = inputImage.rows - countNonZero(inputImage.col(i));
	}

	return countedBlacks;
}

Mat convertToGrayScale(Mat inputImage)
{
	Mat outputImage;

	cvtColor(inputImage, outputImage, CV_BGR2GRAY);

	return outputImage;
}

Mat convertToBinary(Mat inputImage)
{
	Mat outputImage;

	//cvThreshold(inputImage, outputImage, 128, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);

	outputImage = inputImage > Threshold;

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

	outputImage = inputImage.t();

	return outputImage;
}

Mat drawChart(Mat inputImage, int *countedBlacks, int cols)
{
	Mat outputImage;
	Mat plotResult;
	//image.at<Vec3b>(Point(x,y)) = color; //wstawia w x,y jakąś barwę

	//Ptr<plot::Plot2d> plot;
	//plot = plot::createPlot2d(data);
	//plot->render(plot_result);

	outputImage.ones(inputImage.cols, inputImage.rows, CV_8UC3);

	for(int y=0;y<outputImage.rows;y++)
	{
	    for(int x=0;x<outputImage.cols;x++)
	    {
		// get pixel
		//Vec3b color = input.at<Vec3b>(Point(x,y));

		// ... do something to the color ....

		// set pixel
/*		if()
		{
			outputImage.at<Vec3b>(Point(x,y)) = 0;
		}
		else
		{
			outputImage.at<Vec3b>(Point(x,y)) = 255;
		}*/
	    }
	}
	//-------------------------------//
	//     fill your data here
	//-------------------------------//
/*
	Ptr<plot::Plot2d> plot;
	plot = plot::createPlot2d(outputImage);
	plot->render(plotResult);
*/
	return plotResult;
}

int main()
{
	const char *exampleSample = "../mag_tester/probki/SkanyRazem/dokument004.jpg";
	const char *windowName = "probka";
	struct stat sb;
	Mat image;
	int *countedBlacks = NULL;

	if(stat(exampleSample, &sb) == -1)
	{
		cout << "File " << exampleSample << " cannot be accessed!";
	}

	image = imread(exampleSample, 1);

	//convert to grayscale
	image = convertToGrayScale(image);

	//rotate90
	image = rotate90(image);

	//convert to binary
	image = convertToBinary(image);


	countedBlacks = countBlackPixs(image);

	for(int i = 0; i < image.cols; i++)
		cout << "col=" << i << " ,val=" << countedBlacks[i] << endl;

	//display chart
	image = drawChart(image, countedBlacks, image.cols);

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
