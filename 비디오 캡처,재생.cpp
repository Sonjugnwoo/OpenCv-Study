#include <iostream>
#include <opencv2/opencv.hpp>

int main() {

	cv::VideoCapture cap("test.avi");		// 동영상 파일 열기

	if (!cap.isOpened())	// isOpened() = false면 파일 없음/지원 안됨/웹캠 연결 안됨
		throw std::runtime_error("loading failed");

	cv::Mat frame;	// 각 프레임을 저장할 이미지 객체

	while (true) {	// 무한 루프 = 동영상 끝날 때까지 재생
		cap >> frame;	// 한 프레임 읽기 

		if (frame.empty())	break;	// 프레임 읽기 실패 = 동영상 끝

		imshow("Test", frame);	// 현재 프레임 화면 출력 (제목: "Test")

		if (cv::waitKey(30) == 'q')	break;	 // 30ms 대기 (약 33FPS) + 'q' 키 체크
	}

	// 정리 작업
	cap.release();       // VideoCapture 메모리 해제
	cv::destroyAllWindows();  // 모든 OpenCV 창 닫기
}