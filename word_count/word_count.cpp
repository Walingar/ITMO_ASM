#include <emmintrin.h>
#include <tmmintrin.h>
#include <cassert>
#include <cstdint>
#include <utility>

const char SPACE = ' ';
const char CONTAINS = 1;

const auto SPACE_128 = _mm_set1_epi8(SPACE);
const auto CONTAINS_128 = _mm_set1_epi8(CONTAINS);


size_t word_count_simple(const char *str, size_t len) {
    size_t count = 0;
    char current = str[0];
    if (current != ' ')
        count = 1;

    for (int i = 1; i < len && str[i] != '\0'; ++i) {
        if (current == ' ' && str[i] != ' ')
            count++;
        current = str[i];
    }

    return count;
}


std::pair<size_t, size_t> align(const char *str) {
    size_t remaining = 16 + (size_t) str % 16;
    size_t count = word_count_simple(str, remaining);

    return {remaining, count};
}

size_t fast_count(const char *str, size_t len) {
    if (len < 48)
        return word_count_simple(str, len);

    size_t count = 0;
    auto aligned = align(str);

    auto str_aligned = (char *) (str + aligned.first);
    len -= aligned.first;
    count += aligned.second;

    for (size_t chunk = 0; chunk < len; chunk += 16) {
        auto current_str = _mm_loadu_si128((__m128i *) (str_aligned + chunk));
        auto current_str_one_back = _mm_loadu_si128((__m128i *) (str_aligned + chunk - 1));

        auto spaces = _mm_cmpeq_epi8(current_str, SPACE_128);
        auto spaces_in_one_back = _mm_cmpeq_epi8(current_str_one_back, SPACE_128);

        auto words = _mm_andnot_si128(spaces, spaces_in_one_back);
        auto fixed_words = _mm_and_si128(words, CONTAINS_128);

        auto parts = reinterpret_cast<unsigned long long *>(&fixed_words);
        auto part_left = __builtin_popcountll(parts[0]);
        auto part_right = __builtin_popcountll(parts[1]);
        count += part_left + part_right;
    }

    if (str_aligned[len - 2] == ' ')
        count--;

    return count;
}