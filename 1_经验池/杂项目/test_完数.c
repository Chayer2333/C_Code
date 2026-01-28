#include <stdio.h>
#include <assert.h>

// 声明被测函数
int factorsum(int num);
int Prime(int num);
int getPrimes(int primes[], int max);

// 测试Prime函数
void test_Prime() {
    assert(Prime(2) == 1);
    assert(Prime(3) == 1);
    assert(Prime(4) == 0);
    assert(Prime(17) == 1);
    assert(Prime(1) == 0);
    assert(Prime(0) == 0);
    assert(Prime(97) == 1);
    printf("test_Prime passed.\n");
}

// 测试getPrimes函数
void test_getPrimes() {
    int primes[20];
    int count = getPrimes(primes, 20);
    int expected[] = {2, 3, 5, 7, 11, 13, 17, 19};
    assert(count == 8);
    for(int i = 0; i < count; i++) {
        assert(primes[i] == expected[i]);
    }
    printf("test_getPrimes passed.\n");
}

// 测试factorsum函数
void test_factorsum() {
    // 完数
    assert(factorsum(6) == 6);
    assert(factorsum(28) == 28);
    assert(factorsum(496) == 496);
    // 非完数
    assert(factorsum(12) == 16);
    assert(factorsum(15) == 9);
    assert(factorsum(1) == 0);
    printf("test_factorsum passed.\n");
}

int main() {
    test_Prime();
    test_getPrimes();
    test_factorsum();
    printf("All tests passed.\n");
    return 0;
}