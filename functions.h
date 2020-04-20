#pragma once

#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

#define PRINT_VAL(value) PRINT_VAL_MSG(value,"")
#define PRINT_VAL_MSG(value, message) cout << #value" : " << value <<", " message << endl;

void test_fork();


