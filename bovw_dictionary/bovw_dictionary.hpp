#pragma once

#include "convert_dataset.hpp"
#include "serialize.hpp"
#include <opencv2/opencv.hpp>

/**
* @brief
* 1. Given cluster centroids i initialized in some way,
* 2. For iteration t=1..T:
* 1. Compute the distance from each point x to each cluster centroid ,
* 2. Assign each point to the centroid it is closest to,
* 3. Recompute each centroid as the mean of all points assigned to it,
*
* @param descriptors The input SIFT descriptors to cluster.
* @param k The size of the dictionary, ie, number of visual words.
* @param max_iterations Maximum number of iterations before convergence.
* @return cv::Mat One unique Matrix representing all the $k$-means(stacked).
*/
cv::Mat kMeans(const std::vector<cv::Mat>& descriptors, int k, int max_iter);

class BowDictionary {
public:

	static BowDictionary& get_instance();
	int get_max_iterations() const { return max_iterations_; };
	int get_size() const { return size_; };
	std::vector<cv::Mat> get_descriptors() const { return descriptors_; };
	cv::Mat get_vocabulary() const { return vocabulary_; };
	int get_total_features() const { return total_features_; };
	bool is_empty() const { return empty_; };

	void set_max_iterations(int max_iterations);
	void set_size(int size);
	void set_descriptors(std::vector<cv::Mat> descriptors);
	void set_params(int max_iterations, int size, std::vector<cv::Mat> descriptors);

private:
	BowDictionary() {}
	int max_iterations_ = 0;
	int size_ = 0;
	std::vector<cv::Mat> descriptors_;
	int total_features_ = 0;
	cv::Mat vocabulary_;
	bool empty_ = true;
public:
	BowDictionary(BowDictionary const&) = delete;
	void operator=(BowDictionary const&) = delete;
};