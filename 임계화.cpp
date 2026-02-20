#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat img = cv::imread("lena.jpg");
    if (img.empty())
        throw std::runtime_error("loading failed");

    cv::Mat thresholdImg;

    // 전역 임계화 (Global Threshold)
    // 컬러 이미지도 가능! 각 채널(B/G/R) 독립 적용
    // thresh=50, maxval=150, THRESH_BINARY: >50→150, ≤50→0
    cv::threshold(img, thresholdImg, 50.0, 150.0, cv::THRESH_BINARY);
    // 컬러 이진화 (B/G/R 각각 임계화)

    cv::hconcat(img, thresholdImg, img);
    cv::imshow("좌: 원본 컬러 | 우: 전역 임계화(50→150)", img);
    cv::waitKey(0);

    cv::Mat adaptive;

    // 적응형 임계화 준비 (Grayscale 필수!)
    cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);  // 컬러→1채널 회색

    // 적응형 임계화: 주변 영역 평균으로 로컬 임계값 계산
    // ADAPTIVE_THRESH_GAUSSIAN_C: 가우시안 가중 평균
    // blockSize=3(3x3 영역), C=0(보정값 없음)
    cv::adaptiveThreshold(img, adaptive, 50.0 /*최대값*/,
        cv::ADAPTIVE_THRESH_GAUSSIAN_C,
        cv::THRESH_BINARY, 3, 0);
    /*
    장점: 조명 불균일 자동 보상
    단점: Grayscale 전용 (1채널만)
    */

    cv::Mat row;
    cv::hconcat(img, adaptive, row);
    cv::imshow("좌: Gray 원본 | 우: 적응형 임계화(Gaussian,3x3)", row);
    cv::waitKey(0);
}