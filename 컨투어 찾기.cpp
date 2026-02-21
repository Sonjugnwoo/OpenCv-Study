#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat img = cv::imread("test.png",cv::IMREAD_GRAYSCALE);

    if (img.empty())
        throw std::runtime_error("img loading failed");

    // 외곽선 저장할 컨테이너들 (Point들 벡터의 벡터, 계층 구조)
    std::vector<std::vector<cv::Point>> contours;     // 검출된 외곽선들
    std::vector<cv::Vec4i> hierarchy;                 // 외곽선 간 부모-자식 관계

    // 고정 임계값(127)으로 이진화 → 흰색(255)/검은색(0)만 남김
    cv::Mat binaryImg;
    cv::threshold(img, binaryImg, 127, 255, cv::THRESH_BINARY);

    // 이진 이미지에서 외곽선 검출
    // RETR_EXTERNAL: 최외곽 컨투어만 (내부 홀 제외)
    // CHAIN_APPROX_NONE: 모든 점 저장 (압축 안함)
    cv::findContours(binaryImg, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);

    // 이진 이미지를 컬러(3채널)로 변환 → 색상 외곽선 그리기용
    cv::Mat colorImg;
    cv::cvtColor(binaryImg, colorImg, cv::COLOR_GRAY2BGR);

    // 모든 외곽선(-1)을 컬러 이미지에 녹색으로 그림 (두께 3)
    cv::drawContours(colorImg, contours, -1, cv::Scalar(0, 65, 0), 3);

    // 동적 윈도우 제목 생성: "발견된 contuours : [숫자]"
    std::string title = "발견된 contuours : " + std::to_string(contours.size());

    // 결과 이미지 표시 (제목에 검출 개수 포함)
    cv::imshow(title, colorImg);
    cv::waitKey(0);  // 키 입력 대기 (창 닫기)
}