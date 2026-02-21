#include "BrandSearch.h"
#include "ImagePreprocessor.h"
#include <iostream>

namespace fs = boost::filesystem;

void BrandSearch::addTemplate(fs::path p) {
	ImagePreprocessor image;
	for (auto& entry : fs::directory_iterator(p)) {
		if (fs::is_regular_file(entry)) {

			cv::Mat img = cv::imread(entry.path().string());
			if (!img.empty()) {
				cv::Mat processedImg = image.preprocessor_image(img);
				cv::imshow("debug", processedImg);
				templates.push_back(processedImg);
				if (cv::waitKey(1) == 'q') continue;
			}
		}
	}
	//std::cout << "총 몇개 :" << templates.size();
}

std::vector<cv::Rect> BrandSearch::Search(const cv::Mat& img, double threshold ) {
	std::vector<cv::Rect> rect;
	ImagePreprocessor image;
	cv::Mat processedImg = image.preprocessor_image(img);
	for (auto& logoImg : templates) {
		cv::Mat result;
		cv::matchTemplate(processedImg, logoImg, result, cv::TM_CCOEFF_NORMED, cv::noArray());
		double minVal, maxVal;           // 최소/최대 매칭값
		cv::Point minLoc, maxLoc, matchLoc;  // 최소/최대 위치
		cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());
		std::cout << "MaxVal : " << maxVal << std::endl;

		if (maxVal > threshold) {
			cv::Rect detected(maxLoc.x, maxLoc.y, logoImg.cols, logoImg.rows);
			std::cout << "MaxVal : " << maxVal << std::endl;
			cv::imshow("debug", logoImg);
			cv::waitKey(1) == 'q';
			rect.push_back(detected);
		}
	}
	return rect;
}