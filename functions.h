#pragma once

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <stdlib.h>
#include <string.h>

using namespace std;

#define PRINT_VAL(value) PRINT_VAL_MSG(value,"")
#define PRINT_VAL_MSG(value, message) cout << #value" : " << value <<", " message << endl;

// test for fork
void ForkTest();

// test for mutex
void MutexTest();

// test for pipe
void PipeTest();



