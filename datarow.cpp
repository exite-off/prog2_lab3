#include "datarow.h"

#include <string>

DataRow::DataRow() {
    fields[0] = 0;
    fields[1] = 0;
}

int DataRow::get(int index) const {
    std::lock_guard<std::mutex> lock(mtx[index]);
    return fields[index];
}

void DataRow::set(int index, int value) {
    std::lock_guard<std::mutex> lock(mtx[index]);
    fields[index] = value;
}

DataRow::operator std::string() const {
    std::lock_guard<std::mutex> lock0(mtx[0]);
    std::lock_guard<std::mutex> lock1(mtx[1]);
    return "[" + std::to_string(fields[0]) + ", " + std::to_string(fields[1]) + "]";
}
