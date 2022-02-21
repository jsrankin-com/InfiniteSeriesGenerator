Generator<long long> GetInfinitePrimes() noexcept {
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
