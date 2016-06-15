#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>

static const unsigned int Threshold = 240;

using namespace std;
using namespace cv;

Mat *rectangles;

//image.at<Vec3b>(Point(x,y)) = color; //wstawia w x,y jakąś barwę

void cropImageIntoPieces(Mat *rectangles, Mat input, int numOfPieces)
{
	//firstly I need to draw as much rectangles as numOfPieces
	//rectangles = new Mat[numOfPieces];

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
		cout << "newRectXPosition=" << newRectXPosition << endl;
		Rect newRect(newRectXPosition, 0, rectangleWidth, rectangleHeight);
		Mat croppedRef(input, newRect);
		croppedRef.copyTo(rectangles[i]);
		newRectXPosition += rectangleWidth;
	}

	// namedWindow("windowName", CV_WINDOW_NORMAL);
	// imshow("windowName", rectangles[3]);


	// while(true)
	// {
	// 	int c;
	// 	c = waitKey(20);
	// 	if((char)c == 27)
	// 		break;
	// }

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
	Mat outputImage2;

	blur(inputImage, outputImage, Size(10, 10));

	//Mat sub_mat = Mat::ones(inputImage.size(), inputImage.type())*255;
 
    //subtract the original matrix by sub_mat to give the negative output new_image
    //subtract(sub_mat, outputImage, outputImage2);
	//cvNot(outputImage,outputImage2);

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
	if(argc < 1)
	{
		cout << endl << "Too less arguments!!!" << endl;
		cout << endl << "e.g. ./tester <filename>" << endl << endl;
		return 1;
	}

	Mat image1;
	const char *exampleSample = argv[1];
	const char *windowName = "probka";
	namedWindow(windowName, CV_WINDOW_NORMAL);

	image1 = imread(exampleSample, 1);

	image1 = convertToGrayScale(image1);

	imwrite("convertedToGrayscale.jpg", image1);

	image1 = blur(image1);

	imwrite("blurredImage.jpg", image1);

	//image1 = convertToGrayScale(image1);

	image1 = convertToBinary(image1);

	imwrite("convertedToBinary.jpg", image1);

	Mat dst, image;
 Canny(image1, image, 50, 200, 3);
 cvtColor(image, dst, CV_GRAY2BGR);

 image = rotate90(image);

	vector<Vec4i> lines;
	HoughLinesP(image, lines, 1, CV_PI/1, 90, 800, 2000 );

	for( size_t i = 0; i < lines.size(); i++ )
	{
	  Vec4i l = lines[i];
	  line(image, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(60,60,60), 5, CV_AA);
	  cout<<"l[0]: "<<l[0] << endl;
	  cout<<"l[1]: "<<l[1] << endl;
	  cout<<"l[2]: "<<l[2] << endl;
	  cout<<"l[3]: "<<l[3] << endl;
	}

	cout<< "lines size: " <<lines.size() << endl;
       
	//display image
        //namedWindow(windowName, CV_WINDOW_NORMAL);
        imshow(windowName, image);

	imwrite("resultImage.jpg", image);

        while(true)
        {
             int c;
             c = waitKey(20);
             if((char)c == 27)
                     break;
        }


	


	return 0;
}
