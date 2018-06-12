#include <cstdio>
#include <cstdint>

void memcpy1(void *dist, const void *src, size_t count) {
    if (count > 0) {
        asm volatile
        (R"(
            clc
        loop_1:
            mov (%[src]), %%al
            mov %%al, (%[dist])
            inc %[src]
            inc %[dist]
            dec %[count]
            jnz loop_1
        )"
        :[dist]"+r"(dist), [src]"+r"(src), [count]"+r"(count)
        :
        :"cc", "memory", "al");
    }
}

void memcpy8(void *dist, const void *src, size_t count) {
    size_t current_count = count / 8;
    size_t remaining = count % 8;
    if (current_count > 0) {
        asm volatile
        (R"(
            clc
        loop_8:
            mov (%[src]), %%rdi
            mov %%rdi, (%[dist])
            add $8, %[src]
            add $8, %[dist]
            dec %[count]
            jnz loop_8
        )"
        :[dist]"+r"(dist), [src]"+r"(src), [count]"+r"(current_count)
        :
        :"cc", "memory", "rdi");
    }
    memcpy1(dist, src, remaining);
}

void memcpy16(void *dist, const void *src, size_t count) {
    size_t current_count = count / 16;
    size_t remaining = count % 16;
    if (current_count > 0) {
        asm volatile
        (R"(
            clc
        loop_16:
            xorps %%xmm0, %%xmm0
            movups (%[src]), %%xmm0
            movups %%xmm0, (%[dist])
            add $16, %[src]
            add $16, %[dist]
            dec %[count]
            jnz loop_16
        )"
        :[dist]"+r"(dist), [src]"+r"(src), [count]"+r"(current_count)
        :
        :"cc", "memory", "xmm0");
    }
    memcpy8(dist, src, remaining);
}

void memcpy16_aligned(void *dist, const void *src, size_t count) {
    size_t remaining = count % 16;
    memcpy8(dist, src, remaining);
    auto new_dist = (void *) ((size_t) dist + remaining);
    auto new_src = (void *) ((size_t) src + remaining);
    memcpy16(new_dist, new_src, count - remaining);
}