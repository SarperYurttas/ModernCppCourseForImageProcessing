#include "convert_dataset.hpp"
#include "serialize.hpp"
#include <opencv2/opencv.hpp>
#include <filesystem>

namespace fs = std::filesystem;

void serialization::sifts::ConvertDataset(const std::filesystem::path& img_path){
	fs::current_path(img_path);
	fs::create_directories("../bin");
	for (auto& p : fs::directory_iterator(img_path)) {
		std::string input_file_path = fs::path(p).string();
		std::string output_file_path = "../bin/" + fs::path(p).stem().string() + ".bin";

		cv::Mat m = cv::imread(input_file_path, cv::IMREAD_GRAYSCALE);
		serialization::Serialize(m, output_file_path);
	}
}

std::vector<cv::Mat> serialization::sifts::LoadDataset(const std::filesystem::path& bin_path){
	std::vector<cv::Mat> bins;
	for (auto& p : fs::directory_iterator(bin_path)) {
		std::string file_path = fs::path(p).string();
		bins.emplace_back(serialization::Deserialize(file_path));
	}
	return bins;
}