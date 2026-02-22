#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

int main() {
    // =====================================================
    // Hough 직선 검출 (test.png)
    // =====================================================
    // 그레이스케일 이미지 로드
    cv::Mat img = cv::imread("test.png", cv::IMREAD_GRAYSCALE);

    if (img.empty())
        throw std::runtime_error("img loading failed");

    // 그레이 → 컬러 변환 (선 그리기용 BGR)
    cv::Mat colorImg;
    cv::cvtColor(img, colorImg, cv::COLOR_GRAY2BGR);

    // Canny 에지 검출 (100-150, 약화된 threshold)
    cv::Mat cannyEdge;
    cv::Canny(colorImg, cannyEdge, 100, 150);

    // HoughLines (rho=1, theta=1°, 최소 400px)
    std::vector<cv::Vec2f> lines;
    cv::HoughLines(cannyEdge, lines, 1, CV_PI / 180, 400);

    // 극좌표 → 직선 그리기 (컬러 이미지에 직접)
    for (size_t i = 0; i < lines.size(); i++) {
        float rho = lines[i][0], theta = lines[i][1];  // ρ, θ
        cv::Point pt1, pt2;
        double x0 = rho * cos(theta), y0 = rho * sin(theta);  // 법선점

        // ±1000px 길이 선분
        pt1.x = round(x0 + 1000 * (-sin(theta)));
        pt1.y = round(y0 + 1000 * (cos(theta)));
        pt2.x = round(x0 - 1000 * (-sin(theta)));
        pt2.y = round(y0 - 1000 * (cos(theta)));

        // **변경**: colorImg에 녹색 선 그리기 (원본 보존)
        cv::line(colorImg, pt1, pt2, cv::Scalar(0, 255, 0), 2, 8);
    }

    // 결과 표시 (컬러 + 녹색 직선)
	cv::imshow("Hough Lines on Original", colorImg);
	cv::waitKey(0);
    // =====================================================
    // Hough 원 검출 (circle.jpg)
    // =====================================================
    cv::Mat circleImg = cv::imread("circle.jpg", cv::IMREAD_GRAYSCALE);
    std::vector<cv::Vec3f> circle;  // (x,y,radius)

    cv::Mat circleColor;  // 컬러 표시용
    cv::cvtColor(circleImg, circleColor, cv::COLOR_GRAY2BGR);

    // HOUGH_GRADIENT (dp=1, minDist=30px)
    cv::HoughCircles(circleImg, circle, cv::HOUGH_GRADIENT, 1, 30);

    for (const auto& cir : circle) {
        cv::Point center(cvRound(cir[0]), cvRound(cir[1]));  // 중심
        int rad = cvRound(cir[2]);  // 반지름

        cv::circle(circleColor, center, rad, cv::Scalar(0, 0, 255), 3);   // 빨강 외곽선
        cv::circle(circleColor, center, 3, cv::Scalar(0, 255, 0), 2);     // 초록 중심점
    }
    cv::imshow("Hough Circles (100원 동전)", circleColor);
    cv::waitKey(0);


}