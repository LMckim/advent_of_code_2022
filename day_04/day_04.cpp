#include <iostream>
#include <string>
#include <vector>

struct CleanPair {
    int start;
    int end;

    CleanPair(int _start, int _end) : start(_start), end(_end) {}

    bool encompasses(CleanPair other) {
        return this->start <= other.start && this->end >= other.end;
    }

    bool overlaps(CleanPair other) {
        return (
            // left overlap
            (this->start <= other.start && this->end >= other.start)
            || (this->start <= other.end && this->end >= other.end)
        );
    }
};

std::vector<std::string> split(std::string str, char delim) {
    std::vector<std::string> result;
    std::string buf;
    for (auto c: str) {
        if (c == delim) {
            std::string push = buf;
            result.push_back(push);
            buf.clear();
            continue;
        }
        buf += c;
    }
    result.push_back(buf);
    return result;
}

int main() {
    int encompassed = 0;
    int overlaps = 0;

    std::vector<std::string> line_split;
    std::vector<std::string> elf_split;

    std::string input;
    while(std::getline(std::cin, input)) {
        line_split = split(input, ',');
        std::vector<std::string> elf_split_01 = split(line_split[0], '-');
        std::vector<std::string> elf_split_02 = split(line_split[1], '-');

        CleanPair elf_01 = CleanPair(std::stoi(elf_split_01[0]), std::stoi(elf_split_01[1])); 
        CleanPair elf_02 = CleanPair(std::stoi(elf_split_02[0]), std::stoi(elf_split_02[1]));

        if (elf_01.encompasses(elf_02) || elf_02.encompasses(elf_01)) {
            encompassed++;
        }
        if (elf_01.overlaps(elf_02) || elf_02.overlaps(elf_01)) {
            overlaps++;
        }
    }

    std::cout << "Encompassed:\t" << encompassed << std::endl;
    std::cout << "Overlaps:\t" << overlaps << std::endl;
    return 0;
}