
#include "combination_counter.h"
#include <map>
#include <algorithm>
#include <queue>

std::pair<std::map<std::string_view, size_t>, size_t> count_combinations(std::string_view data){

    std::map<std::string_view , size_t> table;
    size_t total{0};
    const auto end_sentinel(std::cend(data));
    auto begin_char{std::cbegin(data)};

    if(std::distance(begin_char, end_sentinel) < 4){
        return {table, 0};
    }

    while(begin_char < end_sentinel){

        auto word_end{std::find_if_not(begin_char, end_sentinel, ::isalpha)};
        auto word_length = std::distance(begin_char, word_end);

        if(word_length < 4){
            begin_char = std::find_if(word_end, end_sentinel, ::isalpha);
            continue;
        }

        for (auto combination_end = word_end; word_length >= 4; ){
            table[std::string_view(begin_char, combination_end)]++;
            total++;
            word_length = std::distance(begin_char, --combination_end);
        }

        begin_char++;
    }

    return {table, total};
}

std::vector<std::pair<std::string, size_t>> get_combination_statistics(std::string_view input){
    const auto [frequencies, total] = count_combinations(input);
    using datatype = std::pair<std::string_view, size_t>;
    auto compare = [](datatype left, datatype right) { return left.second > right.second; };
    std::priority_queue<datatype, std::vector<datatype>, decltype(compare)> most_common{compare};

    for(auto combination : frequencies){
        if(most_common.size() == 10 && most_common.top().second < combination.second){
            most_common.pop();
            most_common.emplace(combination);
        } else if(most_common.size() < 10){
            most_common.emplace(combination);
        }
    }

    std::vector<std::pair<std::string, size_t>> ret;

    while(!most_common.empty()){
        auto& elem = most_common.top();
        ret.emplace_back(elem.first, 10000 * elem.second / total);
        most_common.pop();
    }

    return ret;
}