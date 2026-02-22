#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

int main() {
    // 그레이스케일 이미지 로드
    cv::Mat img = cv::imread("street.jpg", cv::IMREAD_GRAYSCALE);       // 비교 대상1
    cv::Mat targetImg = cv::imread("target.jpg", cv::IMREAD_GRAYSCALE); // 비교 대상2

    if (img.empty() || targetImg.empty())
        throw std::runtime_error("이미지 로드 실패");

    // CLAHE 적용 (로컬 대비 향상) - 조명 차이 보정
    cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE(1.0, cv::Size(8, 8));    // clipLimit=1.0, 8x8 타일
    cv::Mat claheImg, targetClahe;

    clahe->apply(img, claheImg);        // street.jpg CLAHE 처리
    clahe->apply(targetImg, targetClahe); // target.jpg CLAHE 처리

    // 히스토그램 계산 (256bin, 0-256 범위)
    cv::Mat histStreet, histTarget;     // 히스토그램 저장소
    int histSize = 256;                 // 밝기 레벨 수
    float range[] = { 0, 256 };         // 히스토그램 범위
    const float* histRange = { range };

    cv::calcHist(&claheImg, 1, 0, cv::Mat(), histStreet, 1, &histSize, &histRange);   // street 히스토그램
    cv::calcHist(&targetClahe, 1, 0, cv::Mat(), histTarget, 1, &histSize, &histRange); // target 히스토그램

    // 히스토그램 상관계수 비교 (1에 가까울수록 유사)
    auto result = cv::compareHist(histStreet, histTarget, cv::HISTCMP_CORREL);

    // 결과 해석 및 출력
    std::cout << "히스토그램 상관계수: " << result << std::endl;

    if (result > 0.8)
        std::cout << "매우 유사 (패턴/밝기 일치)" << std::endl;
    else if (result > 0.5)
        std::cout << "  약간 유사" << std::endl;
    else
        std::cout << "다름 (전혀 다른 이미지)" << std::endl;
}
/* cv::calcHist 
파라미터	값   	의미
images	&claheImg	1개 그레이 이미지를 배열처럼 취급
nimages	1	이미지 1개 사용
channels	0	0번 채널 (그레이스케일=채널0)
mask	cv::Mat()	전체 이미지 사용 (마스크 없음)
hist	histStreet	결과 저장 1x256 히스토그램
dims	1	1차원 히스토그램
histSize	&256	256개 bin (0~255 밝기)
ranges	&{0,256}	0~256 범위 (CLAHE 후 범위)*/