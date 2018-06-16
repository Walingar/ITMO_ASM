#include "word_count.cpp"
#include <gtest/gtest.h>
#include <iostream>

#define size 1000000

void print_time(double start_time, double end_time) {
    printf("%.1lf microseconds\n", (end_time - start_time) * 1000 * 1000 / CLOCKS_PER_SEC);
}

TEST(word_count, simple_Test) {
    char src[] = "mama mila ramu";
    size_t counted = word_count_simple(src, sizeof src);
    ASSERT_EQ(counted, 3);
}

TEST(word_count, simple_a_lot_of_spaces_Test) {
    char src[] = "        mama          mila       ramu               ";
    size_t counted = word_count_simple(src, sizeof src);
    ASSERT_EQ(counted, 3);
}

TEST(word_count, fast_Test) {
    char src[] = "mama mila ramu";
    size_t counted = fast_count(src, sizeof src);
    ASSERT_EQ(counted, 3);
}

TEST(word_count, fast_a_lot_of_spaces_Test) {
    char src[] = "                              baq  mq  pmq papp  e           lxdakix p q iwa   mtwi  gcdvvv s   p f  rae g ma pu q g clviu r  kv ntf  sc       ";
    size_t counted = fast_count(src, sizeof src);
    ASSERT_EQ(counted, word_count_simple(src, sizeof src));
}

TEST(word_count, fast_a_with_lot_of_spaces_Test) {
    char src[] = "               aaaaaaaaaaaaaaa                ";
    size_t counted = fast_count(src, sizeof src);
    ASSERT_EQ(counted, 1);
}

TEST(word_count, fast_a_with_lot_of_spaces_and_shifted_Test) {
    char src[] = "               aaaaaaaaaaaaaaa                ";
    size_t counted = fast_count(src + 1, sizeof src - 1);
    ASSERT_EQ(counted, 1);
}

TEST(word_count, fast_18_a_with_lot_of_spaces_Test) {
    char src[] = "              aaaaaaaaaaaaaaaaa               ";
    size_t counted = fast_count(src, sizeof src);
    ASSERT_EQ(counted, 1);
}

TEST(word_count, fast_rand_Test) {
    srand(time(0));
    char src[size + 1];
    for (int i = 0; i < size; ++i) {
        int space = rand() % 100;
        if (space < 60) {
            src[i] = char(rand() % ('z' - 'a') + 'a');
        } else {
            src[i] = ' ';
        }

    }
    src[size] = '\0';

    size_t counted = fast_count(src, sizeof src);

    ASSERT_EQ(counted, word_count_simple(src, sizeof src));
}

TEST(word_count, fast_burn_Test) {
    srand(time(0));
    double full_time_fast_end = 0;
    double full_time_fast_start = 0;
    double full_time_simple_end = 0;
    double full_time_simple_start = 0;

    for (int i = 0; i < 100; ++i) {
        char src[size + 1];
        for (int i = 0; i < size; ++i) {
            int space = rand() % 100;
            if (space < 60) {
                src[i] = char(rand() % ('z' - 'a') + 'a');
            } else {
                src[i] = ' ';
            }

        }
        src[size] = '\0';
        // printf("%s\n", src);
        double start_time_fast = clock();
        size_t counted_fast = fast_count(src, sizeof src);
        double end_time_fast = clock();

        double start_time_simple = clock();
        size_t counted_simple = word_count_simple(src, sizeof src);
        double end_time_simple = clock();

        ASSERT_EQ(counted_fast, counted_simple);

        printf("%10s", "Fast: ");
        full_time_fast_end += end_time_fast;
        full_time_fast_start += start_time_fast;
        print_time(start_time_fast, end_time_fast);

        printf("%10s", "Simple: ");
        full_time_simple_end += end_time_simple;
        full_time_simple_start += start_time_simple;
        print_time(start_time_simple, end_time_simple);
    }

    printf("\nFinish.\n");
    printf("%10s", "Fast: ");
    print_time(full_time_fast_start, full_time_fast_end);

    printf("%10s", "Simple: ");
    print_time(full_time_simple_start, full_time_simple_end);
}