#pragma once
#include <opencv2/opencv.hpp>

class ImagePreprocessor {
public:
	cv::Mat preprocessor_image(const cv::Mat& input);
};