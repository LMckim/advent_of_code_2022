#include <iostream>
#include <string>
#include <vector>

#include "../common/crate_ops.cpp"

using std::string;
using std::vector;

size_t max_column(string line) {
    size_t max = 0;
    for (auto c: line) {
        if (c != ' ') {
            if (std::stoi(string(1, c)) > max) {max = std::stoi(string(1,c)); }
        }
    }
    return max;
}

int main() {
    bool _9001 = true;
    vector<vector<Crate>> crates; // 2d array
    vector<string> crate_lines;
    CrateHandler ch = CrateHandler(crates);

    size_t max_col = 0;

    string input;
    bool loading = true;

    auto get_top = [crates](size_t col) {
        size_t height = 0;
        while(crates[col][height].id != '!') {
            height++;
        }
        return crates[col][height];
    };

    auto place_top = [crates](size_t col, Crate crate) {

    };


    while(std::getline(std::cin, input)) {
        if (input.length() == 0) {
            loading = false;
            max_col = max_column(crate_lines[crate_lines.size()-1]);
            crate_lines.pop_back();
            std::reverse(crate_lines.begin(), crate_lines.end());

            // build the empty 2D array
            auto height_line = [](){
                vector<Crate> line;
                for (size_t i=0; i<100; i++) {
                    line.push_back(Crate());
                }
                return line;
            };
            for(size_t col=0; col<max_col; col++) {
                ch.crates.push_back(height_line());
            }

            size_t height = 0, column = 0;
            for (string crate_line: crate_lines) {
                size_t char_idx = 0;
                while(char_idx < crate_line.length()) {
                    string section = crate_line.substr(char_idx, 3);
                    if (section != "   ") {
                        ch.crates[column][height].id = section[1];
                    }
                    char_idx += 4;
                    column++;
                }
                column = 0;
                height++;
            }

            continue;
        }

        if (loading) {
            crate_lines.push_back(input);
        } else {
            // real work
            Instruction inst = parse_instruction(input);
            _9001 ? ch.handle_instruction_9001(inst) : ch.handle_instruction_9000(inst);         
            ch.print_stack();

        }
    }
    std::cout << "Top Line:\t" << ch.top_col_ids() << '\n';
}