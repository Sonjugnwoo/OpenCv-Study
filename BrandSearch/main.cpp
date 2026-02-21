#include <iostream>
#include "BrandSearch.h"
int main() {
	
	BrandSearch search;
	boost::filesystem::path p("./Hyundai");
	search.addTemplate(p);

	cv::Mat img = cv::imread("test.jpg");
	cv::Mat thresholdImg;
	//cv::threshold(img, thresholdImg, 50, 100, cv::INTER_LINEAR);

	auto rect = search.Search(img);

	for (auto &it : rect) {
		cv::rectangle(img, it, cv::Scalar(0, 0, 255),3);
	}
	cv::imshow("로고", img);
	cv::waitKey(0);
}