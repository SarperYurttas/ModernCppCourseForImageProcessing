#include <iostream>
#include <random>
int main() {
	std::random_device rd;
	std::uniform_int_distribution<int> dist(0, 100);
	int number = dist(rd);
	int guess = 0;
	while (1) {
		std::cout << "Enter your guess: " << std::endl;
		std::cin >> guess;
		if (guess == number) {
			std::cout << "Your guess is right!" << std::endl;
			break;
		}
		else if (guess > number) {
			std::cout << "Your guess is too high" << std::endl;
		}
		else if (guess < number) {
			std::cout << "Your guess is too low" << std::endl;
		}
	}
	return 0;
}