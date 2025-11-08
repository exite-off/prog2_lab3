#include <iostream>
#include "generator.cpp"

int main() {
    std::string filename = "data.txt";
    int n = 100;
    std::vector<int> freqs = {40, 5, 5, 5, 45};

    try {
        generateFile(filename, n, freqs);
        std::cout << "File generated successfully: " << filename << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}