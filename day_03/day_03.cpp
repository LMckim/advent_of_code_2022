
#include <iostream>
#include <set>
#include <string>
#include <vector>

int priority_values(int char_val) {
    if (char_val >= 65 && char_val <= 90) {
        return char_val - 64 + 26;
    // lowercase
    } else if (char_val >= 97 && char_val <= 122) {
        return char_val - 96;
    }
    return -1;
}

int main() {
    using std::string;

    string input;
    string comp_a, comp_b;
    std::set<char> comp_a_items;
    std::set<char> visited;
    std::vector<string> elf_group;

    int sum_prior = 0;
    int sum_badges = 0;
    int char_val = 0;
    int line = 0;
    int group = 1;

    while (std::getline(std::cin, input)) {
        // part 1
        comp_a = input.substr(0, input.length()/2);
        for (auto c : comp_a) {
            comp_a_items.insert(c);
        }
        comp_b = input.substr((input.length()/2), input.length()-1);
        for (auto c : comp_b) {
            if (comp_a_items.find(c) != comp_a_items.end() && visited.find(c) == visited.end()) {
                char_val = static_cast<int>(c);
                // uppercase
                sum_prior += priority_values(char_val);
                visited.insert(c);
            }
        }
        comp_a_items.clear();
        visited.clear();
        // part 2
        elf_group.push_back(input);
        if (elf_group.size() == 3) {
            for (auto c : "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") {
                if (
                    elf_group[0].find(c) != string::npos 
                    && elf_group[1].find(c) != string::npos
                    && elf_group[2].find(c) != string::npos
                ) {
                    // std::cout << "Group: " << group << "\tCommon: " << c << "\tValue:" << priority_values(c) << "\n";
                    sum_badges += priority_values(c);
                }
            }

            elf_group.clear();
            group++;
        }
        // std::cout << line << std::endl;
        line++;
    }

    std::cout << "Summed Priorities:\t" << sum_prior << std::endl;
    std::cout << "Summed Badges:\t" << sum_badges << std::endl;
    return 0;
}