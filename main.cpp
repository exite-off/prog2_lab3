// Author: Vitalii Fedin, K-26. Variant - 2. Compiler - MSVC.

#include <iostream>
#include <format>
#include <fstream>
#include <thread>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>
#include "datarow.h"

void generateFile(const std::string &filename, int n, const std::vector<int> &freqs);

struct Command {
    std::string type;
    int index = -1;
    int val = 0;
};

std::vector<Command> parseCommands(const std::string& filename) {
    std::vector<Command> commands;
    std::string line;
    std::ifstream file(filename);

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Command command;
        iss >> command.type;

        if (command.type == "read") {
            iss >> command.index;
        } else if (command.type == "write") {
            iss >> command.index >> command.val;
        }
        if (!command.type.empty()) {
            commands.push_back(command);
        }
    }
    return commands;
}

void execute(const std::vector<Command>& commands, DataRow& data) {
    for (const auto& command : commands) {
        if  (command.type == "write") {
            data.set(command.index, command.val);
        } else if (command.type == "read") {
            int j = data.get(command.index);
        }
        else {
            std::string str = std::string(data);
        }
    }
}

void testLaunch(const std::string& title, const std::string& filename) {
    std::vector <Command> commands0 = parseCommands(std::format("{}0.txt", filename));
    DataRow data;
    auto start = std::chrono::steady_clock::now();
    execute(commands0, data);
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << title << " took " << duration.count() << " ms for 1 thread." << std::endl;

    std::vector <Command> commands1 = parseCommands(std::format("{}1.txt", filename));
    start = std::chrono::steady_clock::now();
    std::thread thread1(execute, commands0, std::ref(data));
    std::thread thread2(execute, commands1, std::ref(data));
    thread1.join();
    thread2.join();
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << title << " took " <<  duration.count() << " ms for 2 threads." << std::endl;

    std::vector  <Command> commands2 =  parseCommands(std::format("{}2.txt", filename));
    start = std::chrono::steady_clock::now();
    std::thread t1(execute, commands2, std::ref(data));
    std::thread t2(execute, commands1, std::ref(data));
    std::thread t3(execute, commands2, std::ref(data));
    t1.join();
    t2.join();
    t3.join();
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << title <<  " took " <<  duration.count() << " ms for 3 threads." << std::endl;
}

int main() {
    constexpr int commandsAmount = 200000;
    for (int i = 0; i < 3; ++i) {
        generateFile(std::format("good{}.txt", i), commandsAmount, {40, 5, 5, 5, 45});
        generateFile(std::format("medium{}.txt", i), commandsAmount, {20,20,20,20,20});
        generateFile(std::format("bad{}.txt", i), commandsAmount, {5,30,40,10,15});
    }

    try {
        testLaunch("Test according to the variant", "good");
        testLaunch("Test with equal frequencies", "medium");
        testLaunch("Test with totally different frequencies",  "bad");
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}