#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include "../common/string.cpp"

using std::string;
using std::vector;

struct Crate {
    char id = '!';
    uint16_t offset = 0;
    uint16_t height = 0;
};

struct Instruction {
    size_t amt;
    size_t src_col;
    size_t dest_col;
};

Instruction parse_instruction(string line) {
    vector<string> bits = split(line, ' ');
    Instruction inst;
    inst.amt = std::stoi(bits[1]);
    inst.src_col = std::stoi(bits[3]) - 1;  // not 0 indexed in text
    inst.dest_col = std::stoi(bits[5]) - 1; // not 0 indexed in text
    return inst;
}

struct CrateHandler {
    vector<vector<Crate>> crates;
    CrateHandler(vector<vector<Crate>> _crates) : crates(_crates) {}

    void handle_instruction_9000(Instruction inst) {
        for (size_t i=0; i<inst.amt; i++) {
            size_t top_src = this->get_top_of_col(inst.src_col);
            size_t top_dest = this->get_top_of_col(inst.dest_col);
            // move
            char new_id = this->crates[inst.src_col][top_src].id;
            this->crates[inst.dest_col][top_dest+1].id = new_id;
            // clear old
            this->crates[inst.src_col][top_src].id = '!';
            
        }
    }

    void handle_instruction_9001(Instruction inst) {
        size_t top_src = this->get_top_of_col(inst.src_col);
        size_t top_dest = this->get_top_of_col(inst.dest_col);

        vector<char> to_move;
        // // pick em' up
        std::cout << "TOP: " << top_src << "\tAMT: " << inst.amt << "\t\n";
        for(size_t i=0; i<inst.amt; i++) {
            to_move.push_back(this->crates[inst.src_col][top_src - i].id);
            this->crates[inst.src_col][top_src - i].id = '!';
            std::cout << "clear:\t" << top_src - i << '\n';

        }
        std::reverse(to_move.begin(), to_move.end());
        // // put em' down
        for (size_t i=0; i<to_move.size(); i++) {
            this->crates[inst.dest_col][top_dest+i+1].id = to_move[i];
        }
        to_move.clear();
    }

    size_t get_top_of_col(size_t col) {
        size_t i = 0;
        while (i < this->crates[col].size()) {
            if (this->crates[col][i+1].id == '!') {
                return i;
            }
            i++;
        }
        return 0;
    }

    string top_col_ids() {
        string top = "";
        for (size_t i=0; i<this->crates.size(); i++) {
            top += this->crates[i][this->get_top_of_col(i)].id;
            // top += " ";
        }
        return top;
    }

    void print_stack() {

    }
};