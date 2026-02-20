#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
	cv::Mat img = cv::imread("lena.jpg");	

	if (img.empty())	
		throw std::runtime_error("img loading failed");
	
    cv::Mat cannyImg;

    // Canny 엣지 검출 (Grayscale 권장, 컬러도 가능)
    // lowThreshold=100, highThreshold=150, apertureSize=3 (Sobel 커널), L2gradient=false
    cv::Canny(img, cannyImg, 100, 150, 3, false);

    // 원본 컬러 vs 흑백 엣지 가로 합성
    cv::hconcat(img, cannyImg, img);
    cv::imshow("좌: 원본 컬러 | 우: Canny 엣지 검출(100-150)", img);
	cv::waitKey(0);
}