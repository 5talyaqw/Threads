#include <string>
#include <fstream>
#include <iostream>
#include<vector>


void I_Love_Threads();
void call_I_Love_Threads();

void printVector(std::vector<int>& primes);

//helper
bool isPrime(int num);
void getPrimes(int begin, int end, std::vector<int>& primes);
std::vector<int> callGetPrimes(int begin, int end);


void writePrimesToFile(int begin, int end, std::ofstream file);
void callWritePrimesMultipleThreads(int begin, int end, std::string filePath, int N);