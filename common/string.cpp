#include <string>
#include <vector>

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
    if (buf.length() > 0) {
        result.push_back(buf);
    }
    return result;
}