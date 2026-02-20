#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat img = cv::imread("lena.jpg");
    if (img.empty())
        throw std::runtime_error("loading failed"); 

    cv::Mat hsvImg, grayImg;

    // 컬러 원본(BGR 3채널) → 그레이스케일(1채널) 변환
    cv::cvtColor(img, grayImg, cv::COLOR_BGR2GRAY);
    // grayImg.shape = [높이, 너비, 1] - 밝기 정보만 보존

    // 그레이스케일(1채널) → 회색 BGR(3채널) 확장
    cv::cvtColor(grayImg, grayImg, cv::COLOR_GRAY2BGR);
    // grayImg.shape = [높이, 너비, 3], 모든 픽셀 R=G=B
    // 색상 정보는 생성되지 않음 - 밝기 값만 3채널로 복제

    // 디버깅: 회색 이미지 확인 (선택사항)
    /*cv::imshow("grayImg (1→3채널 회색)", grayImg);
    cv::waitKey(0);*/

    // 회색 BGR → HSV 변환
    cv::cvtColor(grayImg, hsvImg, cv::COLOR_BGR2HSV);
    // HSV에서 S(채도)=0, H(색상)=무의미, V(명도)=원래 Gray값 보존

    // 원본 컬러 vs 회색-HSV 가로 합성
    cv::hconcat(img, hsvImg, img);

    cv::imshow("좌: 원본 컬러 BGR | 우: Gray→BGR→HSV 변환 결과", img);
    cv::waitKey(0);
}