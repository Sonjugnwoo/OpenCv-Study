#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat img = cv::imread("pic.jpg",cv::IMREAD_GRAYSCALE);

    if (img.empty())
        throw std::runtime_error("img loading failed");

    cv::CascadeClassifier faceCascade;

    faceCascade.load("haarcascade_frontalface_default.xml");

    if (faceCascade.empty())
        return -1;

}