#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat img = cv::imread("lena.jpg");

    if (img.empty())
        throw std::runtime_error("img loading failed");

    cv::Mat erodeImg;
    // 침식(Erosion): 흰색 영역 축소, 검은색 영역 확대
    // 구조 요소 생략=3x3 사각형, 반복 5회
    cv::erode(img, erodeImg, cv::Mat(), cv::Point(-1, -1), 5);
    // Point(-1,-1)=기본 앵커(중앙), 반복횟수=5
    cv::hconcat(img, erodeImg, img);
    cv::imshow("좌: 원본 | 우: 침식(Erode x5)", img);
    cv::waitKey(0);

    cv::Mat dilateImg;
    // 팽창(Dilation): 흰색 영역 확대, 검은색 영역 축소
    cv::Mat grayImg = cv::imread("lena.jpg", cv::IMREAD_GRAYSCALE);  // Gray 전용

    cv::dilate(grayImg, dilateImg, cv::Mat(), cv::Point(-1, -1), 5);
    cv::hconcat(grayImg, dilateImg, grayImg);
    cv::imshow("좌: Gray 원본 | 우: 팽창(Dilate x5)", grayImg);
    cv::waitKey(0);

    cv::Mat morphologyExImg;
    // 모폴로지 변환 (MorphologyEx): 침식+팽창 조합
    cv::Mat grayImg2 = cv::imread("lena.jpg", cv::IMREAD_GRAYSCALE);  // Gray 고정

    // MORPH_OPEN: 침식 → 팽창 (노이즈 제거)
    // MORPH_CLOSE: 팽창 → 침식 (구멍 메우기)
    cv::morphologyEx(grayImg2, morphologyExImg,
        cv::MORPH_OPEN , cv::Mat(), cv::Point(-1, -1), 2);
    // 반복 2회
    cv::hconcat(grayImg2, morphologyExImg, grayImg2);
    cv::imshow("좌: Gray 원본 | 우: MorphologyEx(OPEN x2)", grayImg2);
    cv::waitKey(0);
}