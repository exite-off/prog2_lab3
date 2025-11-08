#include "datarow.h"

#include <string>
#include <format>

DataRow::DataRow() {
    fields[0] = 0;
    fields[1] = 0;
}

int DataRow::get(int index) const {
    std::lock_guard lock(mtx[index]);
    return fields[index];
}

void DataRow::set(int index, int value) {
    std::lock_guard lock(mtx[index]);
    fields[index] = value;
}

DataRow::operator std::string() const {
    std::lock_guard lock0(mtx[0]);
    std::lock_guard lock1(mtx[1]);
    return std::format("[{}, {}]", fields[0], fields[1]);
}
