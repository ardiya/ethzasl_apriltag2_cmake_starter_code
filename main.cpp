#include <string>
#include <vector>

#include "apriltags/Tag36h11.h"
#include "apriltags/TagDetector.h"
#include "opencv2/opencv.hpp"
#include "vis.hpp"
#include "libconfig.h++"

int main(int argc, char* argv[]) {
  std::string filename = "../data/sample.png";
  std::string filename_cfg = "../data/example.cfg";
  if (argc > 1) filename = argv[1];
  if (argc > 2) filename_cfg = argv[2];
  cv::Mat image = cv::imread(filename, cv::IMREAD_GRAYSCALE);

  libconfig::Config cfg;
  try {
    cfg.readFile(filename_cfg.c_str());
  }
  catch(const libconfig::FileIOException &fioex) {
    std::cerr << "I/O error while reading file." << std::endl;
    return(EXIT_FAILURE);
  }

  AprilTags::TagDetector tagDetector(AprilTags::tagCodes36h11);
  vector<AprilTags::TagDetection> detections = tagDetector.extractTags(image);

  displayDetection(image, detections);

  return 0;
}
