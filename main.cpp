#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

/**
 * Use linear blending to fade in and out between two images.
 * Adapted from OpenCV 3 linear blend tutorial.
 * See http://docs.opencv.org/3.0-beta/doc/tutorials/core/adding_images/adding_images.html
 */
int main(int argc, char *argv[]) {
   // Validate command-line arguments
   if (argc != 3) {
      std::cout << "Usage: OpenCVLinearBlend file1 file2" << std::endl;
      return 1;
   }

   // Load the two images and resize to 1024x768
   cv::Mat src1 = cv::imread(argv[1]);
   if (src1.empty()) {
      std::cout << "Unable to load image: " << argv[1] << std::endl;
      return -1;
   }
   cv::resize(src1, src1, cv::Size(1024, 768));

   cv::Mat src2 = cv::imread(argv[2]);
   if (src2.empty()) {
      std::cout << "Unable to load image: " << argv[2] << std::endl;
      return -1;
   }
   cv::resize(src2, src2, cv::Size(1024, 768));

   // Fade gradually from the first image to the second
   cv::Mat dst;
   double beta;
   for (double alpha = 0.0; alpha < 1.0; alpha += 0.02) {
      beta = 1.0 - alpha;
      cv::addWeighted(src1, alpha, src2, beta, 0.0, dst);
      cv::imshow("Linear Blend", dst);
      cv::waitKey(30);
   }
   for (double alpha = 1.0; alpha >= 0.0; alpha -= 0.02) {
      beta = 1.0 - alpha;
      cv::addWeighted(src1, alpha, src2, beta, 0.0, dst);
      cv::imshow("Linear Blend", dst);
      cv::waitKey(30);
   }
   return 0;
}
