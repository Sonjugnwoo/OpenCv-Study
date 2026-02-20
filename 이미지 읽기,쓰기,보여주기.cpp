#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
	cv::Mat img = cv::imread("lena.jpg");	//"lena.jpg" 파일을 메모리에 Mat 객체로 로드

	if (img.empty())	// 이미지가 제대로 로드됐는지 확인
		throw std::runtime_error("img loading failed");

	cv::imshow("Lena", img);	// 이미지 표시 (제목: "Lena", 무한 대기)
	cv::waitKey(0);	// 키 입력(ESC 등)까지 창 유지 (0=무한대기)

	cv::imwrite("Lena.bmp", img);	// 원본 그대로 "Lena.bmp"로 저장 (BMP 포맷)
}