// Brooks Stouffer
// CSCI 362
// 10/22/2024
// The Sieve Of Eratosthens

#include <iostream>

#include <vector>

#include <set>

#include <cmath>

#include "Timer.hpp"

//Adds all prime values from 2 to N to a set.

std::set<unsigned>
sieveSet(unsigned N)
{
    std::set<unsigned> prime;
    unsigned x = 2;
    unsigned rootN = std::sqrt(N);
    while(x <= N) // inserts all numbers from 2 to N into a set.
    {
        prime.insert(x);
        ++x;
    }
    for(unsigned i = 2; i <= rootN; ++i) // Starts from 2 to the square root of N 
    {
        if(prime.find(i) != prime.end())// if the number is still in the set it goes to the loop and deletes all multiples of said number from x * x to N * N.
        {
            for(unsigned j = i * i; j <= N; j += i)
            {
                prime.erase(j); //erases all multiples of the current value in the loop.
            }
        }
    }
    
    return prime;// retunrs the set of all prime numbers from 2 to N.
}

//places all prime values from 2 to N inside of the vector.
std::set<unsigned>
sieveVector(unsigned N)
{
    std::vector<bool> isPrime(N + 1, true); //implements a boolean vector to which N values are set to true "1" 
    
    if(N >= 1) // sets position 1 to false.
    {
        isPrime[1] = false;;
    }
    if (N >= 0) // sets position 2 to false.
    {
        isPrime[0] = false;
    }
    unsigned x = 2;
    unsigned rootN = std::sqrt(N);

    for(unsigned i = 2; i <= rootN; ++i) //iterates through all values to of the array from 2 to the square root of n.
    {
        if(isPrime[i])
        {
            for(unsigned j = i * i; j <= N; j += i){ // multiplies values together starting at 2 through the root of N, N times to find all prime numbers and sets them to false.
                isPrime[j] = false;
            }
        }
    }
    std::set<unsigned> mySet; // creates the set
    for(unsigned i = 2; i <= N; ++i) //loopes through all positions of the vector from 2 to N.
    {

    if(isPrime[i])
    {
        mySet.insert(i); //if there is a prime number in said position it is inserted into the set.
    }

    }
    return mySet; // returns the set of all prime numbers from 2 to N.
}

/*
N        10,000,000     20,000,000    40,000,000
================================================
set       13316 ms      28639.6 ms    61134.3 ms

Vector   249.763 ms     508.215 ms    1055.19 ms
*/
/*
    The use of vector is significantly faster than set due to its memory allocation which allows for better preformance
    when you are both finding and inserting elements. Inserting elements into a vector is O(1) time complexiy, while inserting elements
    into a set uses O(log n). Additionally accessing elements inside of a vector remains at O(1) time complexity, while accessing elements
    inside of a set remains at O(log n). 
*/
int
main(int argc, char* argv[])
{
    std::string version{argv[1]};
    unsigned int number = std::stoul (std::string{argv[2]});
    auto sieveVersion = (version == "set" ? &sieveSet : &sieveVector);
    Timer<> t;
    unsigned int answer = sieveVersion (number).size();
    t.stop();
    std::cout << "Pi[" << number << "] = " << answer << " (using a " << version
    << ")\n"
    << "Time: " << t.getElapsedMs() << " ms" << std::endl;
    return 0;
}
