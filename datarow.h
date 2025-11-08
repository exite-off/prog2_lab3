#pragma once

#include <mutex>
#include <string>

class DataRow {
private:
    int fields[2]{};
    mutable std::mutex mtx[2];
public:
    DataRow();
    int get(int index) const;
    void set(int index, int value);
    operator std::string() const;
};


