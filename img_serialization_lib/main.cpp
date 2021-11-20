#include <opencv2/opencv.hpp>
#include "convert_dataset.hpp"
#include "serialize.hpp"

int main() {
	serialization::sifts::ConvertDataset(R"(<directory>)");
	std::vector<cv::Mat> vec = serialization::sifts::LoadDataset(R"(<directory>)");
	return 0;
}
