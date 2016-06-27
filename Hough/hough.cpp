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

Mat blur(Mat inputImage, int size)
{
	Mat outputImage;
	Mat outputImage2;
 

	//Rect rect = Rect (0, 0, 5, 10);
 	//GaussianBlur(inputImage(rect), outputImage, Size(1, 1), 1.5, 1.5);
	blur(inputImage, outputImage, Size(size, size));
	//outputImage.convertToBinary(outputImage);
	//outputImage = cv2.GaussianBlur(inputImage,(5,5),0);
	return outputImage;
}

Mat convertByThreshold(Mat outputImage) {

	int thresh = 200;
int max_thresh = 500;


	//Mat sub_mat = Mat::ones(inputImage.size(), inputImage.type())*255;
 
    //subtract the original matrix by sub_mat to give the negative output new_image
    //subtract(sub_mat, outputImage, outputImage2);
	//cvNot(outputImage,outputImage2);

Mat threshold_output;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  /// Detect edges using Threshold
  threshold( outputImage, threshold_output, thresh, 255, THRESH_BINARY );
  /// Find contours
  findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

  cout<< "ilosc konturów: "<< contours.size() <<endl;

  /// Approximate contours to polygons + get bounding rects and circles
  vector<vector<Point> > contours_poly( contours.size() );
  vector<Rect> boundRect( contours.size() );
  vector<Point2f>center( contours.size() );


  for( int i = 1; i < contours.size(); i++ )
     { approxPolyDP( Mat(contours[i]), contours_poly[i], 1, true );
       boundRect[i] = boundingRect( Mat(contours_poly[i]) );
     }


  /// Draw polygonal contour + bonding rects + circles
  Mat drawing = Mat::ones( threshold_output.size(), CV_8UC3);

drawing = Scalar(255,255,255);
    

  for( int i = 0; i< contours.size(); i++ )
     {
       Scalar color = Scalar(0,0,0);
       int wysokosc = (boundRect[i].tl().y+boundRect[i].br().y)/2;
       rectangle( drawing, Point(boundRect[i].tl().x,wysokosc-1), Point(boundRect[i].br().x+100,wysokosc+1), color, 5, 8 , 0 );
//cout<< "tl: "<< boundRect[i].tl().x <<endl;
//cout<< "br: "<< boundRect[i].br().x <<endl;

//cout<< "ilosc kolumns: "<< threshold_output.cols <<endl;
       //drawContours( drawing, contours_poly, i, color, CV_FILLED, 8, vector<Vec4i>(), 0, Point() );
       //rectangle(drawing, rect1, Scalar(255), CV_FILLED);
     }


	return drawing;
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
	Mat original;
	const char *exampleSample = argv[1];
	const char *windowName = "probka";
	//namedWindow(windowName, CV_WINDOW_NORMAL);

	image1 = imread(exampleSample, 1);

	image1 = convertToGrayScale(image1);

	imwrite("convertedToGrayscale.jpg", image1);
	original = image1;
	image1 = blur(image1, 20);

	imwrite("blurredImage.jpg", image1);

	//image1 = convertToGrayScale(image1);

	image1 = convertToBinary(image1);

	image1 = convertByThreshold(image1); 


	for(int j=0; j<1; j++) {
		image1 = convertToGrayScale(image1);
		image1 = blur(image1, 10);
		image1 = convertToBinary(image1);
		image1 = convertByThreshold(image1); 
	}
	

	imwrite("convertedToBinary.jpg", image1);

	Mat dst, image;

	int numOfPieces = 1;

	Mat *rectangles;
	rectangles = new Mat[numOfPieces+1];

	cropImageIntoPieces(rectangles, image1, numOfPieces);

	int result = 0;
	int tempResult;

	rectangles[numOfPieces] = Mat::ones( rectangles[0].size(), CV_8UC3);
	
	rectangles[numOfPieces] =  Scalar(0,0,0);

	rectangles[numOfPieces] = rotate90(rectangles[numOfPieces]);
	for(int j = 0; j < numOfPieces; j++)
	{
		//ofstream outputFile;
		//outputFile.open("mainOutput" + to_string(j), ios::out | ios::trunc);

		/*rectangles[j] = convertToGrayScale(rectangles[j]);
		rectangles[j] = blur(rectangles[j], 10);
		rectangles[j] = convertToBinary(rectangles[j]);
		rectangles[j] = convertByThreshold(rectangles[j]); */


	Canny(rectangles[j], image, 50, 200, 3);
 	cvtColor(image, dst, CV_GRAY2BGR);

 	image = rotate90(image);

//vector<Vec2f> lines;
//HoughLines(dst, lines, 1, CV_PI/180, 100, 0, 0 );
	vector<Vec2f> lines;
	HoughLines(image, lines, 1, CV_PI/1, rectangles[j].cols*0.4, 0, 0 );

	cout<< " rectangle kolumny:  " <<rectangles[j].cols << endl;

	for( size_t i = 0; i < lines.size(); i++ )
	{
		Point pt1, pt2;
		float rho = lines[i][0];
		float theta = lines[i][1];

		double a = cos(theta), b = sin(theta);
  		double x0 = a*rho, y0 = b*rho;

  		pt1.x = cvRound(x0 + 1000*(-b));
		  pt1.y = cvRound(y0 + 1000*(a));
		  pt2.x = cvRound(x0 - 1000*(-b));
		  pt2.y = cvRound(y0 - 1000*(a));
		  line( image, pt1, pt2, Scalar(255,255,255), 1, CV_AA);
		  line( rectangles[numOfPieces], pt1, pt2, Scalar(255,255,255), 1, CV_AA);

	  //Vec2f l = lines[i];
	 // line(image, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255,255,255), 6, CV_AA);
	 // cout<<"l[0]: "<<l[0] << endl;
	  //cout<<"l[1]: "<<l[1] << endl;
	 // cout<<"l[2]: "<<l[2] << endl;
	 // cout<<"l[3]: "<<l[3] << endl;
	}

	tempResult = lines.size();

	cout<< exampleSample << " results " <<tempResult << endl;



	


		
		namedWindow(windowName, CV_WINDOW_NORMAL);


		//imshow(windowName, original);
        imshow(windowName, image);

	imwrite("resultImage.jpg", image);

        while(true)
        {
             int c;
             c = waitKey(20);
             if((char)c == 27)
                     break;
        }


		//convert to grayscale
		//rectangles[j] = convertToGrayScale(rectangles[j]);

		//rotate90
		//rectangles[j] = rotate90(rectangles[j]);

		//convert to binary
		//rectangles[j] = convertToBinary(rectangles[j]);


		//countedBlacks = countBlackPixs(rectangles[j]);

		//for(int i = 0; i < rectangles[j].cols; i++)
		//	outputFile << "" << i << ";" << countedBlacks[i] << ";" <<endl;
		//outputFile.close();

		//system((sysCmd + to_string(j) + " " + rangeWidth).c_str());
	}



 	/*Canny(image1, image, 50, 200, 3);
 	cvtColor(image, dst, CV_GRAY2BGR);

 	image = rotate90(image);

	vector<Vec4i> lines;
	HoughLinesP(image, lines, 1, CV_PI/2, 200, 200, 3500 );

	
	for( size_t i = 0; i < lines.size(); i++ )
	{
	  Vec4i l = lines[i];
	  line(image, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(250,60,60), 8, CV_AA);
	 // cout<<"l[0]: "<<l[0] << endl;
	  //cout<<"l[1]: "<<l[1] << endl;
	 // cout<<"l[2]: "<<l[2] << endl;
	 // cout<<"l[3]: "<<l[3] << endl;
	}

	int result = lines.size() /2;

	cout<< exampleSample << " results " <<result << endl;
       */
	//display image
      /*  namedWindow(windowName, CV_WINDOW_NORMAL);
	rectangles[numOfPieces] = blur(rectangles[numOfPieces], 5);
	Mat outputImage1 = rectangles[numOfPieces] > 200;
	//Mat outputImage1 = convertToBinary(rectangles[numOfPieces]);
	outputImage1 = convertToGrayScale(outputImage1);
	outputImage1 = rotate90(outputImage1);
		//imshow(windowName, original);
     imshow(windowName, outputImage1);

	imwrite("resultImage.jpg", outputImage1);

        while(true)
        {
             int c;
             c = waitKey(20);
             if((char)c == 27)
                     break;
        }*/

	//outputImage1 = convertByThreshold(outputImage1); 
	imshow(windowName, rectangles[numOfPieces]);

	imwrite("resultImage.jpg", rectangles[numOfPieces]);

        while(true)
        {
             int c;
             c = waitKey(20);
             if((char)c == 27)
                     break;
        }


	return 0;
}
