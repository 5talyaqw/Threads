#include "Threads.h"
#include <iostream>
#include <thread>
#include <cmath>

void I_Love_Threads()
{
	std::cout << "I Love Threads" << std::endl;
}

void call_I_Love_Threads()
{
	std::thread t1(I_Love_Threads);
	t1.detach();
}

//helper function to check if its prime number
bool isPrime(int num)
{
	if (num <= 1)
	{
		return false;
	}
	for (int i = 2; i <= std::sqrt(num); ++i)
	{
		if (num % i == 0)
		{
			return false;
		}
	}
	return true;
}

void printVector(std::vector<int>& primes)
{
	for (int i = 0; i < primes.size(); ++i)
	{
		std::cout << primes[i] << std::endl;
	}
}

void getPrimes(int begin, int end, std::vector<int>& primes)
{
	//going on all the numbers
	for (int i = begin; i <= end; ++i)
	{
		if (isPrime(i)) //sending to check if prime or not
		{
			primes.push_back(i); //if it is prime adding to the vector
		}
	}
}

std::vector<int> callGetPrimes(int begin, int end)
{
	//creating vector for the prime numbers to storage
	std::vector<int> primes;
	
	//creating thread
	std::thread primeThread(getPrimes, begin, end, std::ref(primes));
	
	primeThread.join();

	return primes;
}

void writePrimesToFile(int begin, int end, std::ofstream file)
{
}

void callWritePrimesMultipleThreads(int begin, int end, std::string filePath, int N)
{
}

