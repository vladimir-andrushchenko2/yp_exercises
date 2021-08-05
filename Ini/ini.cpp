#include "ini.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

const std::string WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string& s) {
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string& s) {
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string& s) { return rtrim(ltrim(s)); }

namespace ini {

Section& Document::AddSection(std::string name) {
    auto [it, is_inserted] = sections_.insert({name, {}});
    assert(is_inserted);
    return it->second;
}

const Section& Document::GetSection(const std::string& name) const {
    const static Section empty_section;
    if (sections_.count(name) == 0) {
        return empty_section;
    }

    return sections_.at(name);
}

std::size_t Document::GetSectionCount() const { return sections_.size(); }

Document Load(std::istream& input) {
    Document document;
    std::string line;
    Section* current_section = nullptr;

    while (std::getline(input, line)) {
        if (line.empty()) {
            continue;
        }

        if (line[0] == '[') {
            std::string section_name;
            for (int i = 1; i < line.size(); ++i) {
                if (line[i] == ']') {
                    current_section = &document.AddSection(section_name);
                    continue;
                }

                section_name += line[i];
            }

            continue;
        }

        std::string value;
        std::string key;
        std::istringstream line_stream{line};

        std::getline(line_stream, key, '=');
        std::getline(line_stream, value);

        key = trim(key);
        value = trim(value);

        current_section->insert({key, value});  // word contains value
    }

    return document;
}

}  // namespace ini
