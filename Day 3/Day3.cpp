#include <iostream>
#include "Day3.h"

Day3::Engine::Engine(const std::string &filename) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        schematic.emplace_back(line.begin(), line.end());
    }
}

std::regex pattern("\\.|\\d");

int Day3::Engine::solvePt1() const {
    int sum = 0;
    for (int i = 0; i < schematic.size(); i++) {
        for (int j = 0; j < schematic[i].size(); ++j) {
            if (isdigit(schematic[i][j])) {
                int start = j;
                while (isdigit(schematic[i][j])) {
                    j++;
                }

                int end = j;
                std::string partString(schematic[i].begin() + start, schematic[i].begin() + end);
                int partNum = std::stoi(partString);
                end = end == schematic[i].size() ? end : end + 1;
                start = 0 == start ? 0 : start - 1;

                if (i > 0) {
                    std::string topString(schematic[i - 1].begin() + start, schematic[i - 1].begin() + end);
                    topString = std::regex_replace(topString, pattern, "");
                    if (!std::regex_replace(topString, pattern, "").empty()) {
                        sum += partNum;
                        continue;
                    }
                }

                if (i < schematic.size() - 1) {
                    std::string bottomString(schematic[i + 1].begin() + start, schematic[i + 1].begin() + end);
                    bottomString = std::regex_replace(bottomString, pattern, "");
                    if (!bottomString.empty()) {
                        sum += partNum;
                        continue;
                    }
                }

                std::string leftString(schematic[i].begin() + start, schematic[i].begin() + end);
                leftString = std::regex_replace(leftString, pattern, "");
                if (!leftString.empty()) {
                    sum += partNum;
                }
            }
        }
    }
    return sum;
}

int Day3::Engine::solvePt2() const {
    int sum = 0;
    for (int i = 0; i < schematic.size(); ++i) {
        for (int j = 0; j < schematic[i].size(); ++j) {
            if (schematic[i][j] == '*') {
                int num1 = 0;
                int num2 = 0;
                //search top row for a number
                // start above and search left and right for a number
                for (int k = j - 1; i > 0 && k >= 0 && k <= j + 1 && k < schematic[i].size(); ++k) {
                    // if digit is found search left and right
                    if (isdigit(schematic[i - 1][k])) {
                        // search left
                        int leftBound = k;
                        while (leftBound > 0 && isdigit(schematic[i - 1][leftBound])) {
                            leftBound--;
                        }
                        leftBound = isdigit(schematic[i - 1][leftBound]) ? leftBound : leftBound +1;
                        // search right
                        int rightBound = k;
                        while (rightBound < schematic[i].size() && isdigit(schematic[i - 1][rightBound])) {
                            rightBound++;
                        }
                        k = rightBound;
                        // parse number
                        std::string numString(schematic[i - 1].begin() + leftBound,
                                              schematic[i - 1].begin() + rightBound);
                        if (num1 == 0){
                            num1 = std::stoi(numString);
                        } else {
                            num2 = std::stoi(numString);
                            sum += num1 * num2;
                            break;
                        }
                    }
                }
                // search left and right for a number
                for (int k = j - 1; k >= 0 && k <= j + 1 && k < schematic[i].size(); ++k) {
                    // if digit is found search left and right
                    if (isdigit(schematic[i][k])) {
                        // search left
                        int leftBound = k;
                        while (leftBound > 0 && isdigit(schematic[i][leftBound])) {
                            leftBound--;
                        }
                        leftBound = isdigit(schematic[i][leftBound]) ? leftBound : leftBound + 1;
                        // search right
                        int rightBound = k;
                        while (rightBound < schematic[i].size() && isdigit(schematic[i][rightBound])) {
                            rightBound++;
                        }
                        k = rightBound;
                        // parse number
                        std::string numString(schematic[i].begin() + leftBound, schematic[i].begin() + rightBound);
                        if (num1 == 0) {
                            num1 = std::stoi(numString);
                        } else {
                            num2 = std::stoi(numString);
                            sum += num1 * num2;
                            break;
                        }
                    }
                }
                // search bottom row for a number
                // start below and search left and right for a number
                for (int k = j - 1; i < schematic.size() - 1 && k >= 0 && k <= j + 1 && k < schematic[i].size(); ++k) {
                    // if digit is found search left and right
                    if (isdigit(schematic[i + 1][k])) {
                        // search left
                        int leftBound = k;
                        while (leftBound > 0 && isdigit(schematic[i + 1][leftBound])) {
                            leftBound--;
                        }
                        leftBound = isdigit(schematic[i + 1][leftBound]) ? leftBound : leftBound + 1;
                        // search right
                        int rightBound = k;
                        while (rightBound < schematic[i].size() && isdigit(schematic[i + 1][rightBound])) {
                            rightBound++;
                        }
                        k = rightBound;
                        // parse number
                        std::string numString(schematic[i + 1].begin() + leftBound,
                                              schematic[i + 1].begin() + rightBound);
                        if (num1 == 0) {
                            num1 = std::stoi(numString);
                        } else {
                            num2 = std::stoi(numString);
                            sum += num1 * num2;
                            break;
                        }
                    }
                }
            }
        }
    }
    return sum;
}


int main(int argc, char **argv) {
    Day3::Engine engine("input.txt");
    std::cout << engine.solvePt1() << std::endl;
    std::cout << engine.solvePt2() << std::endl;
    return 0;
}

