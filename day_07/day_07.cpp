#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "../common/string.cpp"

using std::map;
using std::string;
using std::vector;

struct File {
    string name;
    string parent;
    uint64_t size;
};

struct Dir {
    string name;
    vector<File> files;
    map<string, Dir*> sub_dirs;
    Dir *parent = nullptr;

    uint64_t size_of_files() {
        uint64_t s = 0;
        for (auto f: this->files) {
            s += f.size;
        }
        return s;
    }

    uint64_t size_of_all(uint64_t limit = (uint64_t)-1) {
        uint64_t my_size = this->size_of_files();
        uint64_t s = my_size <= limit ? my_size : 0;

        for (auto d: this->sub_dirs) {
            if (limit == (uint64_t)-1) {
                s += d.second->size_of_all();
            } else {
                uint64_t tot_size = d.second->size_of_all(limit);
                if (tot_size <= limit) {
                    s += tot_size;
                }
            }
        }
        return s;
    }

    void matching_dirs(vector<Dir*> *dirs, uint64_t limit) {
        for (auto d: this->sub_dirs) {
            if (d.second->size_of_all() <= limit) {
                dirs->push_back(d.second);
            }
            d.second->matching_dirs(dirs, limit);
        }

    }
};

int main () {
    uint64_t drive = 70'000'000;
    uint64_t update = 30'000'000;

    Dir *curr = new Dir();
    curr->name = "~";

    Dir *head = curr;

    string input;
    while(std::getline(std::cin, input)) {
        vector<string> parts = split(input, ' ');
        // cmd
        if (parts[0] == "$") {
            if (parts[0] == "ls") { // do nothing?

            } else if(parts[1] == "cd") {
                if (parts[2] == "..") {
                    curr = curr->parent;
                } else if (parts[2] == "/") {
                    curr = head;
                } else {
                    curr = curr->sub_dirs[parts[2]];
                }
            }
        // files and dirs
        } else {
            // directory
            if (parts[0] == "dir") {
                Dir *n_dir = new Dir();
                n_dir->name = parts[1];
                n_dir->parent = curr;
                curr->sub_dirs[n_dir->name] = n_dir;
            // file
            } else {
                File n_file = File();
                n_file.name = parts[1];
                n_file.size = std::stoull(parts[0]);
                n_file.parent = curr->name;
                curr->files.push_back(n_file);
            }
        }
    }
    uint64_t t_size = 0;
    vector<Dir*> matching;
    head->matching_dirs(&matching, 100'000);
    for (auto d: matching) {
        t_size += d->size_of_all();
    }
    std::cout << "Total Size w/ Limit: " << t_size << std::endl;
    std::cout << "Total Size All: " << head->size_of_all() << std::endl;

    uint64_t free = drive - head->size_of_all();
    uint64_t needed = update - free;
    std::cout << "Free: " << free << "\tNeeded: " << needed << std::endl;
    vector<Dir*> all_dirs;
    head->matching_dirs(&all_dirs, (uint64_t)-1);
    
    std::sort(
        all_dirs.begin(), 
        all_dirs.end(), 
        [](Dir *a, Dir *b) {
            return a->size_of_all() < b->size_of_all();
        }
    );
    for (auto d: all_dirs) {
        if (d->size_of_all() >= needed) {
            std::cout << "Dir: " << d->name << "\tSize: " << d->size_of_all() <<std::endl;
            break;
        }
    }
}