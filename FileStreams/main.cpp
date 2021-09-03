#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

using namespace std;

// реализуйте эту функцию:
void CreateFiles(const string& config_file) {
    ifstream in_file(config_file);

    std::string line;
    std::getline(in_file, line);

    ofstream out_file(line);

    while (std::getline(in_file, line)) {
        if (std::string_view sv = line; line.at(0) == '>') {
            sv.remove_prefix(1);

            out_file << sv << '\n';
        } else {
            out_file.close();
            out_file.open(line);
        }
    }
}

string GetLine(istream& in) {
    string s;
    getline(in, s);
    return s;
}

int main() {
    ofstream("test_config.txt"s) << "a.txt\n"
                                    ">10\n"
                                    ">abc\n"
                                    "b.txt\n"
                                    ">123"sv;

    CreateFiles("test_config.txt"s);
    ifstream in_a("a.txt"s);
    assert(GetLine(in_a) == "10"s && GetLine(in_a) == "abc"s);

    ifstream in_b("b.txt"s);
    assert(GetLine(in_b) == "123"s);
}
