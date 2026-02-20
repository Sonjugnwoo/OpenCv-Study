#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat img = cv::imread("lena.jpg");
    if (img.empty())
        throw std::runtime_error("loading failed");

    cv::Mat resizeImg, resizeImgAbs;

    // 절대 크기 지정 resize (860x640 고정)
    // INTER_LINEAR: 양선형 보간 (기본값, 확대/축소 균형 좋음)
    cv::resize(img, resizeImgAbs, cv::Size(860, 640), 0, 0, cv::INTER_LINEAR);
    // 파라미터: src, dst_size(fx,fy=0시 무시), interpolation

    // 상대 비율 지정 resize (50% 축소)
    // fx=0.5, fy=0.5: 가로세로 50% 축소
    cv::resize(img, resizeImg, cv::Size(), 0.5, 0.5, cv::INTER_LINEAR);
    // Size() 빈 크기 + fx,fy 사용

    cv::imshow("50% 축소 (상대비율)", resizeImg);
    cv::waitKey(0);

    // 회전 변환 (중심 30도 반시계방향)
    cv::Mat warpImg;
    // getRotationMatrix2D: 중심점, 각도(degree), 스케일
    cv::Mat M = cv::getRotationMatrix2D(
        cv::Point2f(img.cols / 2.0, img.rows / 2.0),  // 회전 중심 (이미지 중앙)
        30,                                           // 30도 반시계 (음수=시계방향)
        1.0                                           // 크기 그대로
    );

    // warpAffine: 원본, 변환행렬, 출력크기, 보간법, 테두리 처리
    cv::warpAffine(img, warpImg, M, cv::Size(860, 640),
        cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(255, 255, 255));
    // BORDER_CONSTANT: 테두리 흰색(255,255,255) 채움

    cv::imshow("30도 회전 (warpAffine)", warpImg);
    cv::waitKey(0);
}