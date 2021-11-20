#include <fstream>
#include <iostream>
#include <filesystem>
#include "html_writer.hpp"
#include "image_browser.hpp"

std::string fileNameGlobal = "my_html_doc";
std::ofstream outFile(fileNameGlobal + ".html");

void html_writer::OpenDocument() {
	if (!outFile.is_open()) {
		std::cerr << "An error occured when opening file" << "\n";
		exit(0);
	}
	outFile << "<!DOCTYPE html>\n<html>\n";
}
void html_writer::CloseDocument() {
	outFile << "</html>\n";
	outFile.close();
}
void html_writer::AddCSSStyle(const std::string& stylesheet) {
	outFile << "<head>\n";
	outFile << "\t<link rel = \"" << stylesheet << R"(" type = "text/css" href = "style.css" />)" << "\n";
	outFile << "</head>\n";
}
void html_writer::AddTitle(const std::string& title) {
	outFile << "<title>" << title << "</title>\n";
}
void html_writer::OpenBody() {
	outFile << "<body>\n";
}
void html_writer::CloseBody() {
	outFile << "</body>\n";
}
void html_writer::OpenRow() {
	outFile << "<div class=\"row\">\n";
}
void html_writer::CloseRow() {
	outFile << "</div>\n";
}
void html_writer::AddImage(const std::string& img_path, float score, bool highlight) {
	if(highlight == true)
		outFile << R"(<div class="column" style="border: 5px solid green;">)" << "\n";
	else
		outFile << R"(<div class="column">)" << "\n";
	outFile << "<h2>" << std::filesystem::path(img_path).stem() << "</h2>";
	outFile << R"(<img src=")" << img_path << R"(" />)";
	outFile << "<p>score =" << score << "</p>" << "\n";
	outFile << "</div>\n";
}
void image_browser::AddFullRow(const ImageRow& row, bool first_row) {
	bool firstImageFlag = true;
	html_writer::OpenRow();
	if (first_row == true){
		for (auto image : row) {
			auto [img_path, score] = image;
			html_writer::AddImage(img_path, score, firstImageFlag);
			firstImageFlag = false;
		}
	}
	else {
		for (auto image : row) {
			auto [img_path, score] = image;
			html_writer::AddImage(img_path, score, false);
		}
	}
	html_writer::CloseRow();
}
void image_browser::CreateImageBrowser(const std::string& title, const std::string& stylesheet,	const std::vector<ImageRow>& rows) {
	bool firstRowFlag = true;
	html_writer::OpenDocument();
	html_writer::AddTitle(title);
	html_writer::AddCSSStyle(stylesheet);
	html_writer::OpenBody();
	for (auto row : rows) {
		image_browser::AddFullRow(row, firstRowFlag);
		firstRowFlag = false;
	}
	html_writer::CloseBody();
	html_writer::CloseDocument();
	std::cout << "HTML file created successfully!" << "\n";
}

std::vector<image_browser::ScoredImage> image_browser::getImgs(std::string directory)
{
	std::vector<image_browser::ScoredImage> imgs;
	for (auto& path : std::filesystem::directory_iterator(directory)) {
		imgs.emplace_back(std::make_tuple(path.path().string(), 0.82));//chosen random score
	}
	return imgs;
}

std::vector<image_browser::ImageRow> image_browser::getRows(std::vector<image_browser::ScoredImage> imgs)
{
	std::vector<image_browser::ImageRow> rows;
	size_t size = imgs.size() / 3 + 1;
	for (size_t i = 0; i < size; ++i) {
		image_browser::ImageRow row;
		for (size_t j = 0; j < 3;++j) {
			if (!imgs.empty()) {
				row[j] = imgs.back();
				imgs.pop_back();
			}
		}
		rows.push_back(row);
	}
	return rows;
}
