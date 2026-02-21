#pragma once
#ifndef BRANDSEARCH_H
#define BRANDSEARCH_H 

#include <boost/filesystem.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

class BrandSearch {
private:
	std::vector<cv::Mat> templates;

public:
	void addTemplate(boost::filesystem::path p);
	std::vector<cv::Rect> Search(const cv::Mat& img, double threshold = 0.75);
};


#endif // !BRANDSEARCH_H
