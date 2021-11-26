
#include "read_file.h"
#include <fstream>

std::string file_to_string(const std::string_view filename) {
    std::ifstream in(filename.data(), std::ios::in | std::ios::binary);
    if (in){
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return contents;
    }
    else
        return  {};
}