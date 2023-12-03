#include <vector>
#include <string>
#include <memory>
#include <regex>
#include <fstream>

namespace Day3 {
    class Engine {
    public:
        explicit Engine(const std::string& filename);

        int solvePt1() const;
        int solvePt2() const;

    private:
        std::vector<std::vector<char>> schematic;
    };
}