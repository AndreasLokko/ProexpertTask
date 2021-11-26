
#ifndef QTHOMEWORK_COMBINATION_COUNTER_H
#define QTHOMEWORK_COMBINATION_COUNTER_H

#include <string_view>
#include <vector>

//returns the character combination and frequency per 10'000 samples
std::vector<std::pair<std::string, size_t>> get_combination_statistics(std::string_view input);

#endif //QTHOMEWORK_COMBINATION_COUNTER_H
