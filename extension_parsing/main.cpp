#include <iostream>
#include <string>
void getArgs(std::string fileName, int& num, std::string& ext) {
	auto pos = fileName.find(".");
	if (pos == std::string::npos) {
		std::cout << "Error: entered wrong name";
		exit(0);
	}
	num = std::stoi(fileName.substr(0, pos));
	fileName.erase(0, pos + 1);
	ext = fileName;
}
int main() {
	std::string fileName1, fileName2, ext1, ext2;
	int num1 = 0, num2 = 0;
	std::cout << "Enter filenames:" << std::endl;
	std::cin >> fileName1 >> fileName2;
	getArgs(fileName1, num1, ext1);
	getArgs(fileName2, num2, ext2);
	if (ext1 != "txt" || ext2 != "txt" || ext1 != "png" || ext2 != "png") {
		std::cout << "Error: entered wrong name";
		exit(0);
	}
	else if (ext1 == "txt" && ext2 == "txt") {
		std::cout << (num1 + num2) / 2 << std::endl;
	}
	else if (ext1 == "png" && ext2 == "png") {
		std::cout << num1 + num2 << std::endl;
	}
	else if (ext1 == "txt" && ext2 == "png" || ext1 == "png" && ext2 == "txt") {
		std::cout << num1 % num2 << std::endl;
	}
	return 0;
}