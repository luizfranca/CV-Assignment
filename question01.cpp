/*
 * question01.cpp
 *
 *  Created on: Jun 17, 2017
 *      Author: luizdaniel
 */

#include "question01.h"

using namespace std;
using namespace cv;

RNG rng(12345);

void question01() {
	cout << "Question 01" << endl;

	Mat image = imread("polygons.png", CV_LOAD_IMAGE_GRAYSCALE);

	Mat binary;

	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;

	vector< vector<Point> > approx(8);

    threshold(image, binary, 250, 255, THRESH_BINARY);

    findContours(binary.clone(), contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);

    Mat drawing = Mat::zeros(binary.size(), CV_8UC3);
    for (int i = 1; i < contours.size(); ++i) {
    	Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));

    	approxPolyDP(contours[i], approx[i], 10, true);

    	cout << "Polygon vertexes[" << i << "]: " << approx[i].size() << endl;

    	for (int j = 0; j < approx[i].size(); ++j) {
    		cout << "Vertex[" << j << "] x: " << approx[i][j].x << " y: " << approx[i][j].y << endl;

    		circle(drawing, approx[i][j], 5, Scalar(0, 33, 255), -1);

//    		imshow("Contours", drawing);

//    		waitKey();
    	}

    	drawContours(drawing, approx, i, color);

    	imshow("Contours", drawing);

    	waitKey();
    }

    waitKey();
}
