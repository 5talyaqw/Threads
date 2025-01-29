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

void writePrimesToFile(int begin, int end, std::ofstream& file)
{
	for (int i = begin; i <= end; ++i)
	{
		if (isPrime(i)) //if the number is prime
		{
			file << i << std::endl; //write it to the file
		}
	}
}


void callWritePrimesMultipleThreads(int begin, int end, std::string filePath, int N)
{
	int i;
	int threadBegin;
	int threadEnd;
	int range;

	//opening file in write mode
	std::ofstream file(filePath);

	if (!file.is_open())
	{
		std::cerr << "error opening file";
		return;
	}
	//start timing
	auto start = std::chrono::high_resolution_clock::now();

	range = (end - begin + 1) / N; //calc range
	std::vector<std::thread> threads; //creating vector of threads

	//creating N threads
	for (i = 0; i < N; ++i)
	{
		threadBegin = begin + i * range;
		if (i == N - 1)
		{
			threadEnd = end;
		}
		else
		{
			threadEnd = threadBegin + range - 1;
		}

		//creating thread to wrtite primes in sub range
		threads.emplace_back(writePrimesToFile, threadBegin, threadEnd, std::ref(file));
	}

	// Wait for all threads to finish
	for (int i = 0; i < threads.size(); ++i)
	{
		threads[i].join();
	}

	//stop timing
	auto end_time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end_time - start;

	//closing file
	file.close();

	//printing total time
	std::cout << "Execution time: " << elapsed.count() << " seconds" << std::endl;
}

