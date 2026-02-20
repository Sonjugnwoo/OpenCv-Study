#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
	cv::Mat img = cv::imread("lena.jpg");	// 컬러 이미지 로드 (3채널)
	cv::Mat imgCopy = img.clone();			// 완전 복사본 생성
	cv::Mat imgInverse = img.clone();

	// ===== 검은색 변환 (imgCopy) =====
	// 전체 픽셀 3채널(BGR) 모두 0으로 설정
	for (int y = 0; y < imgCopy.rows; y++) {
		for (int x = 0; x < imgCopy.cols; x++) {
			for (int n = 0; n < 3; n++)	 //  n=0(B),1(G),2(R) 순회
				imgCopy.at<cv::Vec3b>(y, x)[n] = 0;	 // 각 채널 검은색
		}
	}

	// ===== 반전 변환 (imgInverse) =====
	// 모든 픽셀값을 255 - 원본값으로 변환 (Negative 필름 효과)
	for (int y = 0; y < img.rows; y++) {
		for (int x = 0; x < img.cols; x++) {
			for (int n = 0; n < 3; n++) {
				int data = img.at<cv::Vec3b>(y, x).val[n];     // 원본 픽셀값 읽기
				imgInverse.at<cv::Vec3b>(y, x)[n] = 255 - data; // 반전값 저장
				// 예: 검은색(0) → 흰색(255), 흰색(255) → 검은색(0)
			}
		}
	}

	// ===== 이미지 합치기 =====
	//cv::hconcat(img, imgCopy, img);           // 주석처리: 원본+검은색 (덮어쓰기 위험)
	cv::hconcat(img, imgInverse, img);        // 실행: 원본+반전 합치기 

	//cv::imshow("좌:원본 | 우:전체 검은색", img);     // 합쳐진 이미지 표시
	cv::imshow("좌:원본 | 우:전체 반전", img);     // 합쳐진 이미지 표시
	cv::waitKey(0);
}