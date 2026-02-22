#include <iostream>
#include "BrandSearch.h"
int main() {

    // BrandSearch 인스턴스 생성
    BrandSearch search;

    // 페라리 템플릿 폴더 로드
    boost::filesystem::path p("./Ferrari");
    search.addTemplate(p);

    // 테스트 이미지 로드
    cv::Mat img = cv::imread("Ferrari.png");

    // 이미지 로드 실패 체크
    if (img.empty())
        return -1;

    // 로고 검출 (기본 threshold 0.65)
    auto rect = search.Search(img);

    // 검출 결과 시각화 (빨간 사각형)
    for (auto& it : rect) {
        cv::rectangle(img, it, cv::Scalar(0, 0, 255), 3);
    }
	cv::imshow("페라리 로고 검출", img);
	cv::waitKey(0);
}