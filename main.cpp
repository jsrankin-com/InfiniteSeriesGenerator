#include <iostream>
#include <optional>
#include <vector>
#include "generator.h"


bool CheckIfPrime(std::vector<long long>& primes, long long n)
{
    bool isPrime = true;

    for (int i = 0; (primes[i] * primes[i]) <= n; ++i) {
        if (n % primes[i] == 0) {
            isPrime = false;
            break;
        }
    }
    return isPrime;
}


Generator<long long> GetInfinitePrimes() {
    std::vector<long long> primes;
    primes.push_back(2);
    co_yield 2;
    for (long long i = 3;; i += 2) {
        if (CheckIfPrime(primes, i)) {
            co_yield i;
            primes.push_back(i);
        }
    }
}

int main() {
    auto gen = GetInfinitePrimes();

    for (const auto i : gen) {
        std::cout << i << std::endl;
    }

}
/*
References:
https://en.cppreference.com/w/cpp/coroutine/coroutine_handle

Author:
	Jeffrey S. Rankin
	http://jsrankin.com
	admin@jsrankin.com
*/
