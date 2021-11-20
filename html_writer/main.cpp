#include "html_writer.hpp"
#include "image_browser.hpp"
#include <filesystem>
#include <iostream>

int main() {
	std::vector<image_browser::ScoredImage> imgs = image_browser::getImgs(R"(<directory>)");
	std::vector<image_browser::ImageRow> rows = image_browser::getRows(imgs);
	image_browser::CreateImageBrowser("Image Browser ", "stylesheet", rows);
	return 0;
}