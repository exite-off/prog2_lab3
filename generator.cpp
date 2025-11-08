#include <fstream>
#include <random>
#include <vector>
#include <string>
#include <stdexcept>

void generateFile(const std::string &filename, int n, const std::vector<int> &freqs) {
    if (freqs.size() != 5) {
        throw std::invalid_argument("freqs must have 5 elements: read0, write0, read1, write1, string");
    }

    std::vector<int> relative_freqs(5);
    int sum_i = 0;
    for (size_t i = 0; i < freqs.size(); ++i) {
        sum_i += freqs[i];
        relative_freqs[i] = sum_i;
    }

    std::ofstream f(filename);
    if (!f.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);

    for (int i = 0; i < n; ++i) {
        int r = dis(gen);
        if (r <= relative_freqs[0]) {f << "read 0\n";}
        else if (r <= relative_freqs[1]) {f << "write 0 " << 11 << "\n";}
        else if (r <= relative_freqs[2]) {f << "read 1\n";}
        else if (r <= relative_freqs[3]) {f << "write 1 " << 12 << "\n";}
        else {f << "string\n";}
    }
    f.close();
}
