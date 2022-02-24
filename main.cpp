#include <coroutine>
#include <iostream>
#include <optional>
#include <vector>
#include "generator.h"


bool isPrime(std::vector<long long>& primes, long long n)
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
        if (isPrime(primes, i)) {
            co_yield i;
            primes.push_back(i);
        }
    }
}

int charToInt(char c)
{
    return c - '0';
}
char intToChar(int i)
{
    return i + '0';
}
std::string infiniteSum(std::string low, std::string high)
{
    std::vector<char> vec;

    size_t lowLength = low.length();
    size_t highLength = high.length();
    size_t diff = highLength - lowLength;

    int carry = 0;

    for (int i = lowLength - 1; 0 <= i; --i)
    {

        int sum = charToInt(low[i]) +
            charToInt(high[i + diff]) +
            carry;
        vec.emplace_back(intToChar(sum % 10));
        carry = sum / 10;
    }

    for (int i = diff - 1; 0 <= i; --i)
    {
        int sum = (charToInt(high[i]) + carry);
        vec.emplace_back(intToChar(sum % 10));
        carry = sum / 10;
    }

    if (carry)
        vec.emplace_back(intToChar(carry));

    std::reverse(vec.begin(), vec.end());
    
    return std::string(vec.begin(), vec.end());
}

Generator<std::string> GetInfiniteFibonacci() {
    co_yield "0";
    co_yield "1";
    co_yield "1";
    std::string low = "1";
    std::string high = "1";
    std::string sum = "2";

    for (;;) {
        co_yield sum;
        low = high;
        high = sum;
        sum = infiniteSum(low, high);
    }
}

int main() {

    std::cout << "Primes under 10:" << std::endl;
    for (const auto i : GetInfinitePrimes()) {
        if (i > 10)
            break;
        std::cout << i << std::endl;
    }

    std::cout << "First 10 Fibonacci numbers:" << std::endl;
    long long count = 1;
    for (const auto i : GetInfiniteFibonacci()) {
        if (10 == count)
            break;
        std::cout << i << std::endl;
        ++count;
    }

    system("pause");
    return 0;
}
