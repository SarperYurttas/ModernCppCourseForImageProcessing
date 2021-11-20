#include "bovw_dictionary.hpp"

cv::Mat kMeans(const std::vector<cv::Mat>& descriptors, int k, int max_iter)
{
	cv::Mat labels;
	cv::Mat_<cv::Point2f> output_mat;
	std::vector<cv::Point2f> centers, points;
	for (const auto& descriptor : descriptors) {
		for (int x = 0; x < descriptor.rows; x++)
			for (int y = 0; y < descriptor.cols; y++) {
				if (descriptor.at<uchar>(x, y) > 0)
					points.emplace_back(cv::Point(x, y));
			}
	}
	cv::kmeans(points, k, labels, 
		cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, max_iter, 1.0),
		3, cv::KmeansFlags::KMEANS_PP_CENTERS, centers);
	output_mat.push_back(centers);
	return output_mat;
}


BowDictionary& BowDictionary::get_instance()
{
	static BowDictionary instance;
	return instance;
}

void BowDictionary::set_max_iterations(int max_iterations)
{
	if (is_empty())
		std::cerr << "Dictionary is empty, set parameters first" << "\n";
	else {
		max_iterations_ = max_iterations;
		vocabulary_= kMeans(descriptors_, size_, max_iterations_);
	}
}

void BowDictionary::set_size(int size)
{
	if (is_empty()) 
		std::cerr << "Dictionary is empty, set parameters first" << "\n";
	else {
		size_ = size;
		vocabulary_ = kMeans(descriptors_, size_, max_iterations_);
	}
}

void BowDictionary::set_descriptors(std::vector<cv::Mat> descriptors)
{
	if (is_empty())
		std::cerr << "Dictionary is empty, set parameters first" << "\n";
	else {
		descriptors_ = descriptors;
		vocabulary_ = kMeans(descriptors_, size_, max_iterations_);
	}
}

void BowDictionary::set_params(int max_iterations, int size, std::vector<cv::Mat> descriptors)
{
	max_iterations_ = max_iterations;
	size_ = size;
	descriptors_ = descriptors;
	total_features_ = descriptors.size();
	vocabulary_ = kMeans(descriptors_, size_, max_iterations_);
	empty_ = false;
}