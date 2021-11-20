#include "io_tools.hpp"
#include "image_lib.hpp"
#include <opencv2/opencv.hpp>
Image::Image(int row, int col)
{
	image_data.cols = row;
	image_data.rows = col;
	image_data.data.resize(row * col);
}
uint8_t Image::at(int row, int col) const
{
	int point = row * image_data.cols + col;
	return image_data.data[point];
}

uint8_t& Image::at(int row, int col)
{
	int point = row * image_data.cols + col;
	return image_data.data[point];
}

bool Image::FillFromPgm(const std::string& file_name)
{
	image_data = io_tools::ReadFromPgm(file_name);
	return true;
}

void Image::WriteToPgm(const std::string& file_name)
{
	io_tools::WriteToPgm(image_data, file_name);
}

std::vector<float> Image::ComputeHistogram(int bins) const
{
	float f = image_data.max_val / (float)bins, f1 = 0, f2 = f;
	int pixel_count = image_data.rows * image_data.cols;
	std::vector<float> hist(bins, 0);
	for (auto& bin : hist) {
		float cnt = 0;
		for (auto s : image_data.data) {
			if (s > f1 && s <= f2 ){
				cnt++;
			}
			bin = cnt / pixel_count;
		}
		f1 += f;
		f2 += f;
	}
	return hist;
}

void Image::downScale(int scale)
{
	float scale_factor = (static_cast<double>(1) / scale);
	cv::Mat input_mat(image_data.rows, image_data.cols, CV_8UC1);
	cv::Mat output_mat(image_data.rows/scale, image_data.cols/scale, CV_8UC1);

	if (image_data.data.size() == image_data.rows * image_data.cols) {
		memcpy(input_mat.data, image_data.data.data(), image_data.data.size() * sizeof(uint8_t));
	}
	cv::resize(input_mat, output_mat, cv::Size(0, 0), scale_factor, scale_factor);
	

	image_data.rows /= scale;
	image_data.cols /= scale;
	if (output_mat.isContinuous()) {
		image_data.data.assign(output_mat.data, output_mat.data + output_mat.total() * output_mat.channels());
	}
}

void Image::upScale(int scale)
{
	cv::Mat input_mat(image_data.rows, image_data.cols, CV_8UC1);
	cv::Mat output_mat(image_data.rows * scale, image_data.cols * scale, CV_8UC1);

	if (image_data.data.size() == image_data.rows * image_data.cols) {
		memcpy(input_mat.data, image_data.data.data(), image_data.data.size() * sizeof(uint8_t));
	}
	cv::resize(input_mat, output_mat, cv::Size(0, 0), scale, scale);
	cv::imshow("winname", output_mat);
	cv::waitKey(0);
	cv::destroyAllWindows();
	image_data.rows *= scale;
	image_data.cols *= scale;
	if (output_mat.isContinuous()) {
		image_data.data.assign(output_mat.data, output_mat.data + output_mat.total() * output_mat.channels());
	}
}
