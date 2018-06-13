# Ассемблер ИТМО

## Домашнее задание № 3

Условие:
  
Написать программу, выполняющую подсчет слов в строке (`char*`):
  * `word_count_simple` выполняет наивный подсчет числа слов
  * `fast_count` выполняет быстрый подсчет числа слов с помощью **SSE** регистров

Операционная система: *linux*

Компилятор: *g++*

Решение:
  * [код](word_count/word_count.cpp)
  * [тесты](word_count/word_count_test.cpp)

## Домашнее задание № 2

Условие:
	
Написать программу, выполняющую [memcpy](http://en.cppreference.com/w/cpp/string/byte/memcpy):
  * `memcpy1` выполняет копирование по **1** байту
  * `memcpy8` выполняет копирование по **8** байт
  * `memcpy16` выполняет копирование по **16** байт
  * `memcpy16_aligned` выполняет **выравнивание**, затем копирование по **16** байт

Операционная система: *linux*
Компилятор: *g++*

Решение:
  * [код](memcpy/memcpy.cpp)
  * [тесты](memcpy/memcpy_test.cpp)

## Домашнее задание № 1.2
Условие:
	
Написать программу, выполняющую **умножение** беззнаковых длинных чисел.

Ассемблер: *nasm x86-64*

Операционная система: *linux*

Решение:
  * [код](mul/mul.asm)
  * [тесты](mul/tester.py)

## Домашнее задание № 1.1

Условие:
	
Написать программу, выполняющую **вычитание** беззнаковых длинных чисел.

Ассемблер: *nasm x86-64*

Операционная система: *linux*

Решение:
  * [код](sub/sub.asm)
  * [тесты](sub/tester.py)