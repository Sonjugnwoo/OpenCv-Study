#include "BrandSearch.h"
#include "ImagePreprocessor.h"
#include <iostream>

namespace fs = boost::filesystem;
// ====================================================================================
// 폴더 → resize → 전처리 → 저장
// ====================================================================================
void BrandSearch::addTemplate(fs::path p) {
	ImagePreprocessor image;  // 전처리 객체

	for (auto& entry : fs::directory_iterator(p)) {  // 폴더 순회
		if (fs::is_regular_file(entry)) {  // 파일만 처리

			cv::Mat img = cv::imread(entry.path().string());  // 이미지 로드
			if (!img.empty()) {
				cv::Mat resizeImg;  // 55x55 고정 크기	
				cv::resize(img, resizeImg, cv::Size(55, 55), 0, 0, cv::INTER_LINEAR);
				cv::Mat processedImg = image.preprocessor_image(resizeImg);  // 전처리

				//cv::imshow("debug", processedImg);  // 디버깅
				templates.push_back(processedImg);  // 템플릿 저장
			}
		}
	}
}

// ====================================================================================
//  TM_CCOEFF_NORMED + threshold 필터링
// ====================================================================================
std::vector<cv::Rect> BrandSearch::Search(const cv::Mat& img, double threshold ) {
	std::vector<cv::Rect> rect;  // 검출 결과
	ImagePreprocessor image;
	cv::Mat processedImg = image.preprocessor_image(img);  // 검색 이미지 전처리

	for (auto& logoImg : templates) {  // 각 템플릿별 매칭
		cv::Mat result;
		cv::matchTemplate(processedImg, logoImg, result, cv::TM_CCOEFF_NORMED, cv::noArray());

		double minVal, maxVal;           // 최소/최대 매칭값
		cv::Point minLoc, maxLoc, matchLoc;  // 최소/최대 위치
		cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());
		std::cout << "MaxVal : " << maxVal << std::endl;

		if (maxVal > threshold) {
			cv::Rect detected(maxLoc.x, maxLoc.y, logoImg.cols, logoImg.rows);  // 55x55 영역
			rect.push_back(detected);
		}
	}
	return rect;
	// TODO: 멀티스케일 + 반복 매칭 (그릴+스티어링 2개)
}