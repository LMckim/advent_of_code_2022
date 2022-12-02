#include <algorithm>
#include <numeric>
#include <iostream>
#include <string>
#include <vector>

struct Elf {
    int elf_id;
    std::vector<int> _items = std::vector<int>();

    Elf(int my_id) {this->elf_id = my_id;}

    void add_item(int item) {
        this->_items.push_back(item);
    }

    int total_calories() {
        return std::accumulate(this->_items.begin(), this->_items.end(), 0);
    }
};

int main() {
    int elf_id = 0;
    std::string input;
    std::vector<Elf> elves = std::vector<Elf>();
    Elf new_elf = Elf(elf_id);
    while (std::getline(std::cin, input)) {
        if (input.length() == 0) {
            elves.push_back(new_elf);
            new_elf = Elf(++elf_id);
            continue;
        }
        new_elf.add_item(std::stoi(input));

    }

    // part 01
    int max_cal = 0;
    int cur_cal = 0;
    for (auto x : elves) {
        cur_cal = x.total_calories();
        max_cal = cur_cal > max_cal ? cur_cal : max_cal;
    }
    std::cout << "Max Calories: " << max_cal << std::endl;

    // part 2
    std::sort(
        elves.begin(), 
        elves.end(),
        [](Elf a, Elf b) -> bool { 
            return a.total_calories() > b.total_calories();
        }
    );
    if (elves.size() >= 3) {
        std::cout << "Top 3 Elves Calories: " <<
            elves[0].total_calories() 
            + elves[1].total_calories() 
            + elves[2].total_calories() 
            << std::endl;
    }
    return 0;
}