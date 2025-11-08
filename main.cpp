// Author: Vitalii Fedin, K-26. Variant - 2. Compiler - MSVC.

#include <iostream>
#include <vector>
#include "datarow.h"

void generateFile(const std::string &filename, int n, const std::vector<int> &freqs);

int main() {
    DataRow data;
    std::cout << data.get(0) << std::endl;
    data.set(0, 34);
    data.set(1, 56);
    std::cout << std::string(data);

    return 0;
}