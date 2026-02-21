#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    // 입력 이미지(거리 사진)와 템플릿 이미지(자동차) 로드
    cv::Mat img = cv::imread("street.jpg");           // 큰 이미지 - 찾을 대상
    cv::Mat targetImg = cv::imread("target.jpg");     // 작은 이미지 - 템플릿

    // 이미지 로드 확인 (둘 중 하나라도 실패시 종료)
    if (img.empty() && targetImg.empty())
        throw std::runtime_error("loading failed");

    // 템플릿 리사이즈 (100x100 고정 크기, 비율 유지)
    cv::Mat tempImg;
    cv::resize(targetImg, tempImg, cv::Size(100, 100), 0, 0, cv::INTER_LINEAR);

    // 리사이즈된 템플릿 미리보기 (크기 확인용)
    //cv::imshow("target", tempImg);
    //cv::waitKey(0);

    // 템플릿 매칭 수행 (결과는 히트맵)
    // TM_CCOEFF_NORMED: 상관계수 정규화 (0~1 범위, 1에 가까울수록 좋음)
    cv::Mat result;
    cv::matchTemplate(img, tempImg, result, cv::TM_CCOEFF_NORMED, cv::noArray());

    // 히트맵에서 최고 매칭 위치/값 찾기
    double minVal, maxVal;           // 최소/최대 매칭값
    cv::Point minLoc, maxLoc, matchLoc;  // 최소/최대 위치
    cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());

    // 최고 매칭 위치에 녹색 사각형 그리기 (두께 5)
    // Rect(x, y, width, height)
    cv::rectangle(img, cv::Rect(maxLoc.x, maxLoc.y, tempImg.cols, tempImg.rows),
        cv::Scalar(0, 255, 0), 5);

    // 윈도우 제목에 매칭 정확도(maxVal) 표시
    std::string title = "maxVal: " + std::to_string(maxVal);

    // 최종 결과 표시 (자동차에 녹색 박스)
    cv::imshow(title, img);
    cv::waitKey(0);
}