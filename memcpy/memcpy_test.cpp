#include "memcpy.cpp"
#include <gtest/gtest.h>
#include <iostream>

#define size 4000000

void print_time(double start_time, double end_time) {
    printf("%.1lf microseconds\n", (end_time - start_time) * 1000 * 1000 / CLOCKS_PER_SEC);
}

TEST(memcpy, memcpy1_simple_Test) {
    char src[] = "mama mila ramu";
    char dist[30];
    memcpy1(dist, src, sizeof src);

    for (int i = 0; i < sizeof src; ++i) {
        ASSERT_EQ(src[i], dist[i]);
    }
}

TEST(memcpy, memcpy1_rand_Test) {
    srand(time(0));
    char src[size + 1];
    for (int i = 0; i < size; ++i) {
        src[i] = char(rand() % ('z' - 'a') + 'a');
    }
    src[size] = '\0';

    char dist[size + 1];

    double start_time = clock();
    memcpy1(dist, src, sizeof src);
    double end_time = clock();

    for (int i = 0; i < sizeof src; ++i) {
        ASSERT_EQ(src[i], dist[i]);
    }

    print_time(start_time, end_time);
}

TEST(memcpy, memcpy8_simple_Test) {
    char src[] = "mama mila ramu i tut tozhe mila";
    char dist[100];
    memcpy8(dist, src, sizeof src);

    for (int i = 0; i < sizeof src; ++i) {
        ASSERT_EQ(src[i], dist[i]);
    }
}

TEST(memcpy, memcpy8_rand_Test) {
    srand(static_cast<unsigned int>(time(0)));
    char src[size + 1];
    for (int i = 0; i < size; ++i) {
        src[i] = char(rand() % ('z' - 'a') + 'a');
    }
    src[size] = '\0';

    char dist[size + 1];

    double start_time = clock();
    memcpy8(dist, src, sizeof src);
    double end_time = clock();

    for (int i = 0; i < sizeof src; ++i) {
        ASSERT_EQ(src[i], dist[i]);
    }

    print_time(start_time, end_time);
}

TEST(memcpy, memcpy16_rand_Test) {
    srand(time(0));
    char src[size + 1];
    for (int i = 0; i < size; ++i) {
        src[i] = char(rand() % 20 + 'a');
    }
    src[size] = '\0';

    char dist[size + 1];
    double start_time = clock();
    memcpy16(dist, src, sizeof src);
    double end_time = clock();

    for (int i = 0; i < sizeof src; ++i) {
        ASSERT_EQ(src[i], dist[i]);
    }

    print_time(start_time, end_time);
}


TEST(memcpy, memcpy16_aligned_rand_Test) {
    srand(time(0));
    char src[size + 1];
    for (int i = 0; i < size; ++i) {
        src[i] = char(rand() % 20 + 'a');
    }
    src[size] = '\0';

    char dist[size + 1];

    double start_time = clock();
    memcpy16_aligned(dist, src + 1, sizeof src - 1);
    double end_time = clock();

    for (int i = 1; i < sizeof src; ++i) {
        ASSERT_EQ(src[i], dist[i - 1]);
    }
    print_time(start_time, end_time);
}

TEST(memcpy, memcpy16_aligned_with_shifted_rand_Test) {
    srand(time(0));
    char src[size + 1];
    for (int i = 0; i < size; ++i) {
        src[i] = char(rand() % 20 + 'a');
    }
    src[size] = '\0';

    char dist[size + 1];

    double start_time = clock();
    memcpy16_aligned(dist, src, sizeof src);
    double end_time = clock();

    for (int i = 0; i < sizeof src; ++i) {
        ASSERT_EQ(src[i], dist[i]);
    }
    print_time(start_time, end_time);
}