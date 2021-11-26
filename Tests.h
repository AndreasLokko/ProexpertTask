
#ifndef QTHOMEWORK_TESTS_H
#define QTHOMEWORK_TESTS_H

#include <QtTest/QtTest>

class Tests : public QObject
{
Q_OBJECT
private slots:
    void single_word();
    void multiple_words();
    void short_word();
    void word_with_three_combinations();
    void multiple_words_with_punctuations();
    void empty_string();
    void very_large_string();
    void no_more_then_ten_combinations();
};

#endif //QTHOMEWORK_TESTS_H
