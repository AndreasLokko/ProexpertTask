
#include "Tests.h"
#include "combination_counter.h"
#include <algorithm>

int main(int argc, char *argv[])
{
    Tests tests;
    QTest::qExec(&tests, argc, argv);

    return 0;
}

void Tests::single_word() {
    auto word = "word";
    auto res = get_combination_statistics(word);
    QVERIFY2(res.size() == 1, "test case should return exactly one combination");
    QVERIFY2(res.front().first == word, "the combination should match the input exactly");
    QVERIFY2(res.front().second == 10000, "combination should appear 10000 times out of 10000 samples");
}

void Tests::multiple_words() {
    auto word = "word test";
    auto res = get_combination_statistics(word);
    QVERIFY2(res.size() == 2, "test case should return exactly two combinations");
    QVERIFY2(std::all_of(res.begin(), res.end(), [](decltype(res)::value_type a){ return a.second == 5000; }), "each combination should appear 5000 times out of 10000 samples");
}

void Tests::multiple_words_with_punctuations() {
    auto word = "word, test!??";
    auto res = get_combination_statistics(word);
    QVERIFY2(res.size() == 2, "test case should return exactly two combinations");
    QVERIFY2(std::all_of(res.begin(), res.end(), [](decltype(res)::value_type a){ return a.second == 5000; }), "each combination should appear 5000 times out of 10000 samples");
}

void Tests::short_word() {
    auto word = "lil";
    auto res = get_combination_statistics(word);
    QVERIFY2(res.empty(), "test case should return no combinations");
}

void Tests::word_with_three_combinations() {
    auto word = "green";
    auto res = get_combination_statistics(word);
    QVERIFY2(res.size() == 3, "test case should return exactly three combinations");
    QVERIFY2(std::all_of(res.begin(), res.end(), [](decltype(res)::value_type a){ return a.second == 3333; }), "each combination should appear approximately 3333 times out of 10000 samples");
}

void Tests::empty_string() {
    auto word = "";
    auto res = get_combination_statistics(word);
    QVERIFY2(res.empty(), "test case should return no combinations");
}

void Tests::very_large_string() {
    auto words = std::string("word");
    auto appendix = std::string(" word");
    for(int i = 9999; i > 0; i--)
        words += appendix;
    auto res = get_combination_statistics(words);
    QVERIFY2(res.size() == 1, "test case should return exactly one combinations");
    QVERIFY2(res.front().first == "word", "the combination should match the input exactly");
    QVERIFY2(res.front().second == 10000, "combination should appear 10000 times out of 10000 samples");}

void Tests::no_more_then_ten_combinations() {
    auto word = R"(On the first day of Christmas, my true love gave to me,
A partridge in a pear tree.
On the second day of Christmas, my true love gave to me,
Two turtle doves and a partridge in a pear tree.
On the fourth day of Christ
On the third day of Christmas my true love gave to me, five golden rings
Four calling birds, three french hens,
Two turtle doves and a partridge in a pear tree )";
    auto res = get_combination_statistics(word);
    QVERIFY2(res.size() == 10, "test case should return no more than ten combinations");
    QVERIFY2(std::accumulate(res.begin(), res.end(), 0, [](size_t sum, decltype(res)::value_type b) -> size_t { return sum + b.second; }) < 9999, "The total frequency of the ten combinations should be less than 10000");
}



