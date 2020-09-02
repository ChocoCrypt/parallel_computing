#ifndef __GENERATE_RANDOM_HPP
#define __GENERATE_RANDOM_HPP

#include <fstream>
#include <cstdio>
#include <random>
#include <set>
#include <string>
#include <iostream>

using namespace std;

void print_vector(int size, const int* a);

void write_vector(int size, const int* a);

void read_vector(int size, int* a);

void generate_vector(int size, int* a, unsigned seed);

void generate_norepeat_vector(int size, int* a, unsigned seed);

void write_size(int size, string name);

#endif
