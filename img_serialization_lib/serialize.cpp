#include "serialize.hpp"
#include <opencv2/opencv.hpp>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

void serialization::Serialize(const cv::Mat& m, const std::string& filename) {
	if (m.empty()) {
		std::cerr << "An error occured: mat is empty";
		exit(0);
	}
	cv::Mat descriptors = computeDescriptors(m);

	std::vector<uchar> vec;
	if (descriptors.isContinuous()) {
		vec.assign(descriptors.data, descriptors.data + descriptors.total() * descriptors.channels());
	}
	std::ofstream file(filename, std::ios_base::out | std::ios_base::binary);
	file.write(reinterpret_cast<char*>(&descriptors.rows), sizeof(descriptors.rows));
	file.write(reinterpret_cast<char*>(&descriptors.cols), sizeof(descriptors.cols));
	file.write(reinterpret_cast<char*>(&vec.front()), vec.size() * sizeof(uchar));
}

cv::Mat serialization::Deserialize(const std::string& filename) {
	int rows = 0, cols = 0;
	std::ifstream input_file(filename, std::ios_base::in | std::ios_base::binary);

	input_file.read(reinterpret_cast<char*>(&rows), sizeof(rows));
	input_file.read(reinterpret_cast<char*>(&cols), sizeof(cols));

	std::vector<uchar> input_data(rows * cols, 0);

	input_file.read(reinterpret_cast<char*>(&input_data.front()), input_data.size() * sizeof(input_data.front()));

	cv::Mat input_mat(rows, cols, CV_8UC1);

	if (input_data.size() == rows * cols) {
		memcpy(input_mat.data, input_data.data(), input_data.size() * sizeof(uchar));
	}
	return input_mat;
}

cv::Mat serialization::computeDescriptors(const cv::Mat m)
{
	auto dedector = cv::SiftFeatureDetector::create();
	auto extractor = cv::SiftDescriptorExtractor::create();

	std::vector<cv::KeyPoint> keypoints;
	cv::Mat descriptors;

	dedector->detect(m, keypoints);
	extractor->compute(m, keypoints, descriptors);

	return descriptors;
}