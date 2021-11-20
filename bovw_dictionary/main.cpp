#include <iostream>
#include "convert_dataset.hpp"
#include "serialize.hpp"
#include "bovw_dictionary.hpp"
#include "main.h"

int main() {
	serialization::sifts::ConvertDataset(R"(<directory>)");
	std::vector<cv::Mat> dataset = serialization::sifts::LoadDataset(R"(<directory>)");;
	BowDictionary& dictionary = BowDictionary::get_instance();
	dictionary.set_params(5, 5, dataset);
	cv::Mat vocab = dictionary.get_vocabulary();
	return 0;
}