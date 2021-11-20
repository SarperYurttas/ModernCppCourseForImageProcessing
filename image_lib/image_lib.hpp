#pragma once
#include "io_tools.hpp"
class Image {
public:
	Image() = default;
	Image(int row, int col);
	int rows() const { return image_data.rows; } ;
	int cols() const { return 0; };
	uint8_t at(int row, int col) const;
	uint8_t& at(int row, int col);
	bool FillFromPgm(const std::string& file_name);
	void WriteToPgm(const std::string& file_name);
	std::vector<float> ComputeHistogram(int bins) const;
	void upScale(int scale);
	void downScale(int scale);
	Image(Image&& var) = default;
	Image(const Image& var) = default;
	Image& operator=(Image&& var) = default;
	Image& operator=(const Image& var) = default;
private:
	struct io_tools::ImageData image_data { 0, 0, 0, {} };
};