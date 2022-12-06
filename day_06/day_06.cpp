#include <iostream>
#include <set>
#include <string>


using std::string;
using std::set;

struct Window {
    string section;

    bool all_unique() {
        set<char> chars;
        for (auto c: this->section) { chars.insert(c); };
        return chars.size() == this->section.length();
    }
};

int main() {

    size_t marker_needed = 0;
    size_t message_needed = 0;

    size_t marker_len = 4;
    size_t message_len = 14;
    string input;
    Window win = Window();
    while(std::getline(std::cin, input)) {
        for (size_t i=0; i<input.length(); i++) {
            // marker
            if(i > marker_len) {
                win.section = input.substr(i - marker_len, marker_len);
                if (win.all_unique()) {
                    marker_needed = i;
                    break;
                }
            }
        }

        for (size_t i=0; i<input.length(); i++) {
                    // message
            if (i > message_len) {
                win.section = input.substr(i - message_len, message_len);
                if (win.all_unique()) {
                    message_needed = i;
                    std::cout << i << '\n';
                    break;
                }
            }
        }
        std::cout << "Marker Needed: " << marker_needed << std::endl;
        std::cout << "Message Needed: " << message_needed << std::endl;
    }
}