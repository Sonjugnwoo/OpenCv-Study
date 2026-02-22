#pragma once
#include <opencv2/opencv.hpp>

// ****************************************************************
// 전처리 파이프라인 
// ****************************************************************
class ImagePreprocessor {
public:
	cv::Mat preprocessor_image(const cv::Mat& input);
};