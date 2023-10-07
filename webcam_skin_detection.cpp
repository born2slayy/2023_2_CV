#include <opencv2/opencv.hpp>

int main()
{
    cv::VideoCapture cap(0);

    if (!cap.isOpened())
    {
        std::cout << "Error opening video stream" << std::endl;
        return -1;
    }

    while (1)
    {
        cv::Mat img, img_HSV, HSV_mask, img_YCrCb, YCrCb_mask, merged_mask;
        std::vector<std::vector<cv::Point>> contours;

        if (!(cap.read(img)))
            break;

        cvtColor(img, img_HSV, cv::COLOR_BGR2HSV);
        inRange(img_HSV, cv::Scalar(0, 15, 0), cv::Scalar(17, 170, 255), HSV_mask);

        morphologyEx(HSV_mask, HSV_mask, cv::MORPH_OPEN, cv ::getStructuringElement(cv ::MORPH_RECT, cv ::Size(3, 3)));

        cvtColor(img, img_YCrCb, cv ::COLOR_BGR2YCrCb);

        inRange(img_YCrCb, cv ::Scalar(0, 135, 85), cv ::Scalar(255, 180, 135),
                YCrCb_mask);

        morphologyEx(YCrCb_mask, YCrCb_MASK, cv ::MORPH_OPEN, getStructuringElement(cv ::MORPH_RECT, Size(3, 3)));

        bitwise_and(HSV_MASK, YcrCB_MASK, MERGED_MASK);

        medianBlur(MERGED_MASK, MERGED_MASK);

        morphologyEx(MERGED_MASK, MERGED_MASK, CV_MORPH_OPEN, getStructuringElement(CV_SHAPE_RECT, Size(4, 4)));

        findContours(Merged_Mask.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

        for (auto &contour : contours)
        {
            auto bounding_rect = boundingRect(contour);
            auto aspect_ratio = bounding_rect.width / static_cast<double>(bounding_rect.height);

            if (bounding_rect.area() > 6500 && aspect_ratio > 0.6 && aspect_ratio < 1.3)
            {
                rectangle(img, bounding_rect.tl(), bounding_rect.br(), cv::Scalar(0, 255, 0), 3);
            }
        }

        imshow("Webcam", img);

        char c = (char)waitKey(25);

        if (c == 27)
            break;
    }

    cap.release();

    destroyAllWindows();

    return EXIT_SUCCESS;
}
