// 블러 + 샤프닝 -> 노이즈 제거 후 엣지 선명화

#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat img = cv::imread("lena.jpg");
    if (img.empty())
        throw std::runtime_error("loading failed");

    cv::Mat gaussianBlurImg;

    // OpenCV 내장 GaussianBlur (7x7 커널, sigmaX=50 강한 블러)
    cv::GaussianBlur(img, gaussianBlurImg, cv::Size(7, 7), 50);
    // 내부: 자동 가우시안 커널 생성 + 컨볼루션 (SIMD 최적화)

    cv::hconcat(img, gaussianBlurImg, img);
    cv::imshow("좌: 원본 | 우: OpenCV GaussianBlur(7x7, sigma=50)", img);
    cv::waitKey(0);

    // 직접 3x3 가우시안 커널 구현 (합계=16 정규화)
    float kernel[9] = {
        1 / 16.0, 2 / 16.0, 1 / 16.0,  // 상단행: 중앙 가중치 ↑
        2 / 16.0, 4 / 16.0, 2 / 16.0,  // 중앙행: 4가 최대 (종 모양)
        1 / 16.0, 2 / 16.0, 1 / 16.0   // 하단행: 중앙 가중치 ↑
    };
    // 합계=16/16=1.0 → 밝기 보존 보장!

    cv::Mat kernelMat(3, 3, CV_32F, kernel);  // float형 3x3 행렬 생성

    // 직접 커널로 컨볼루션 적용 (filter2D)
    cv::Mat manualBlur;
    cv::filter2D(img, manualBlur, -1 /*출력 깊이 자동*/, kernelMat);
    // ddepth=-1: 입력과 동일한 깊이 (CV_8UC3 유지)

    cv::hconcat(img, manualBlur, img);
    cv::imshow("좌: 원본 | 우: 직접 3x3 가우시안 커널", img);
    cv::waitKey(0);
}
/*CV_8U:  8비트 unsigned (0~255, 이미지 기본)  
CV_8S:  8비트 signed (-128~127)
CV_16U: 16비트 unsigned
CV_16S: 16비트 signed
CV_32S: 32비트 정수
CV_32F: 32비트 부동소수점 (커널에 필수!) 
CV_64F: 64비트 double (고정밀도)*/