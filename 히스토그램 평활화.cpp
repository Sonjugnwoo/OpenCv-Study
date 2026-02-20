#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat img = cv::imread("lena.jpg");
    if (img.empty())
        throw std::runtime_error("loading failed");

    // 컬러 → 그레이스케일 변환 (CLAHE는 1채널 전용)
    cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
    // 결과: CV_8UC1 (0~255 밝기 정보만)

    // CLAHE 생성
    // clipLimit=4.0: 대비 제한 (1~40, 클수록 강한 대비)
    // tileGridSize=8x8: 64개 영역별 히스토그램 평탄화
    cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE(4.0, cv::Size(8,8));
    /*
    clipLimit↑: 국부적 대비↑ (어두운 부분 밝아짐)
    tileGridSize↓: 지역적 처리↑ (블록 현상 가능)
    */

    cv::Mat claheImg;
    // CLAHE 적용 (입력=출력 모두 1채널)
    clahe->apply(img, claheImg);
    // 내부: 64개 타일별 히스토그램 평탄화 + 대비 제한

    // 원본 vs CLAHE 가로 비교
    cv::hconcat(img, claheImg, img);
    cv::imshow("좌: 원본 Gray | 우: CLAHE(clip=4.0, tile=8x8)", img);
    cv::waitKey(0);
}