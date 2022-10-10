#!/usr/bin/python3

import sys

def factorial(n):
    return 1 if n == 0 \
           else n * factorial(n - 1)

if __name__ == '__main__':
    big_number = int(sys.argv[1])

    for i in range(1, big_number + 1):
        print('factorial(%d) = ' % i)
        factorial(i)
