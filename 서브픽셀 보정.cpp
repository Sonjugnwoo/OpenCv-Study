#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

int main() {
	cv::Mat img = cv::imread("street.jpg");   

    if (img.empty())
        throw std::runtime_error("img loading failed");

    // 코너 좌표 저장 (부동소수점)
    std::vector<cv::Point2f> corners;

    // 코너 검출용 그레이스케일 변환
    cv::Mat grayImg;
    cv::cvtColor(img, grayImg, cv::COLOR_BGR2GRAY);

    // 그리기용 컬러 복사본 (원본 훼손 방지)
    cv::Mat cornerImg = img.clone();

    // Shi-Tomasi 코너 검출
    // maxCorners=1000, quality=1%, minDist=10px
    cv::goodFeaturesToTrack(grayImg, corners, 1000, 0.01, 10);

    // 각 코너에 FILLED 녹색 원 그리기
    for (size_t i = 0; i < corners.size(); i++) {
        cv::circle(cornerImg, corners[i], 5, cv::Scalar(0, 255, 0), -1);
    }

    // 결과 표시
    cv::imshow("Corners", cornerImg);
    cv::waitKey(0);


}