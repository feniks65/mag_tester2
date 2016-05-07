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

void cropImageIntoPieces(Mat *rectangles, Mat input, int numOfPieces)
{
	//firstly I need to draw as much rectangles as numOfPieces
	rectangles = new Mat[numOfPieces];

//Rect(int x, int y, int width, int height) ---> starts from top left corner

	int width = input.cols;

	cout << "width=" << width << endl;

	int height = input.rows;

	cout << "height=" << height << endl;

	int rectangleWidth = input.cols / numOfPieces;

	cout << "rectangleWidth=" << rectangleWidth << endl;

	int rectangleHeight = input.rows; // heigh of the input image

	cout << "rectangleHeight=" << rectangleHeight << endl;

	int newRectXPosition = 0;
	for(int i = 0; i < numOfPieces; i++)
	{
		newRectXPosition = i * rectangleWidth;
		cout << "newRectXPosition=" << newRectXPosition << endl;
		Rect newRect(newRectXPosition, 0, rectangleWidth, rectangleHeight);
		Mat croppedRef(input, newRect);
		croppedRef.copyTo(rectangles[i]);
	}

	//return rectangles;

//cv::Mat source = getYourSource();

// Setup a rectangle to define your region of interest

//cv::Rect myROI(10, 10, 100, 100);

// Crop the full image to that image contained by the rectangle myROI
// Note that this doesn't copy the data

//cv::Mat croppedRef(source, myROI);

//cv::Mat cropped;

// Copy the data into new matrix

//croppedRef.copyTo(cropped);
}

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
	//Mat outputImage = inputImage.clone();
	Mat outputImage;
	inputImage.copyTo(outputImage);

	cout << "outputImage.cols=" << outputImage.cols << ", outputImage.rows=" << outputImage.rows << endl;

	for(int i =0; i < outputImage.cols; i++)
	{
		for(int j = 0; j < outputImage.rows; j++)
		{
			if(countedBlacks[i] == outputImage.rows - j)
				outputImage.at<uchar>(j, i) = 0;
			else
				outputImage.at<uchar>(j, i) = 255;
			//outputImage.at<>(j, i) = 0;
			//outputImage.at<Vec3b>(j, i)[2] = 0;
		}
	}

	outputImage.t();
	outputImage.t();

	return outputImage;
}

int main(int argc, char **argv)
{
	const char *exampleSample = "../mag_tester/probki/SkanyRazem/dokument048.jpg";
	const char *windowName = "probka";
	struct stat sb;
	Mat image;
	int *countedBlacks = NULL;
	int numOfPieces = 4;
	Mat *rectangles;

	if(stat(exampleSample, &sb) == -1)
	{
		cout << "File " << exampleSample << " cannot be accessed!";
	}

	image = imread(exampleSample, 1);

	cropImageIntoPieces(rectangles, image, numOfPieces);

	//convert to grayscale
	rectangles[0] = convertToGrayScale(image);

	//rotate90
	rectangles[0] = rotate90(rectangles[0]);

	//convert to binary
	rectangles[0] = convertToBinary(rectangles[0]);


	countedBlacks = countBlackPixs(rectangles[0]);

	for(int i = 0; i < rectangles[0].cols; i++)
		cout << "" << i << ";" << countedBlacks[i] << ";" <<endl;

	//display chart
	rectangles[0] = drawChart(rectangles[0], countedBlacks, rectangles[0].cols);

	//display image
	namedWindow(windowName, CV_WINDOW_NORMAL);
	imshow(windowName, rectangles[0]);


	while(true)
	{
		int c;
		c = waitKey(20);
		if((char)c == 27)
			break;
	}

	return 0;
}
