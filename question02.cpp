/*
 * question02.cpp
 *
 *  Created on: Jun 17, 2017
 *      Author: luizdaniel
 */

#include "question02.h"

using namespace std;
using namespace cv;

RNG randomGen(12345);

void question02() {

	cout << "Question 02" << endl;

	Mat image1 = imread("Image1.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	Mat image2 = imread("Image2.jpg", CV_LOAD_IMAGE_GRAYSCALE);


	Ptr<Feature2D> detector = ORB::create();

	vector<KeyPoint> image1keypoints, image2keypoints;

	Mat image1descriptors, image2descriptors;

	detector->detectAndCompute(image1, noArray(), image1keypoints, image1descriptors);

	detector->detectAndCompute(image2, noArray(), image2keypoints, image2descriptors);

	BFMatcher matcher(NORM_HAMMING);

	vector< vector<DMatch> > initialMatches;

	matcher.knnMatch(image2descriptors, image1descriptors, initialMatches, 2);

	vector<DMatch> matches;

	for (int i = 0; i < initialMatches.size(); ++i) {
		if (initialMatches[i][0].distance / initialMatches[i][1].distance <= 0.8) {
			matches.push_back(initialMatches[i][0]);
		}
	}

	vector<Point2f> image1Points, image2Points;

	for (int i = 0; i < 4; ++i) {
		int index = randomGen.uniform(0, matches.size() - 1);

		image1Points.push_back(image1keypoints[matches[index].trainIdx].pt);
		image2Points.push_back(image2keypoints[matches[index].queryIdx].pt);
	}

	Mat homography = findHomography(image2Points, image1Points, CV_RANSAC);

	Mat result;

	warpPerspective(image2, result, homography, Size(image2.cols*1.4, image2.rows*1.2));

	Mat halfImage(result, Rect(0, 0, image1.cols, image1.rows));

	image1.copyTo(halfImage);

	imshow("Result", result);

//	imshow("Image1", image1);
//	imshow("Image2", image2);

	waitKey();
}
