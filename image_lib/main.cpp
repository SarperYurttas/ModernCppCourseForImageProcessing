#include <iostream>
#include "image_lib.hpp"
#include "io_tools.hpp"

int main() {
	Image img;
	img.FillFromPgm("lena.ascii.pgm");
	return 0;
}