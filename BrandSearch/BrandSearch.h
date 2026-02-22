#pragma once
#ifndef BRANDSEARCH_H
#define BRANDSEARCH_H 

#include <boost/filesystem.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

// ****************************************************************
// 로고 검출 엔진
// ****************************************************************
class BrandSearch {
private:
	std::vector<cv::Mat> templates;// 전처리 완료 템플릿 이미지 컬렉션

public:
	void addTemplate(boost::filesystem::path p);		   // 폴더에서 템플릿 추가
	std::vector<cv::Rect> Search(const cv::Mat& img, double threshold = 0.65); // 이미지에서 로고  검출
};


#endif // !BRANDSEARCH_H
