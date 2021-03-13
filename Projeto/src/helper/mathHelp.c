#include "mathHelp.h"

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

double dmax(double a, double b) {
    return a > b ? a : b;
}

double dmin(double a, double b) {
    return a < b ? a : b;
}

int charToNum(char num) {
    if (num < '0' || num > '9') return -1;
    return num - '0';
}

int stringToInt(char *num) {
    int result = 0;
    int negative = *num == '-';
    num += negative;
    
    for (; *num >= '0' && *num <= '9'; ++num) {
        result *= 10;
        result += charToNum(*num);
    }
    return negative ? result * -1 : result;
}

double stringToDouble(char *num) {
    double result = 0;
    int negative = *num == '-';
    num += negative;

    for (; *num >= '0' && *num <= '9'; ++num) {
        result *= 10;
        result += charToNum(*num);
    }

    if (*(num++) != '.') {
        return negative ? result * -1 : result;
    }

    for (double decPow = 0.1; *num >= '0' && *num <= '9'; decPow /= 10) {
        result += charToNum(*num++) * decPow;
    }

    return negative ? result * -1 : result;
}

double dpow(double base, double exp) {
    int result;

    while (exp-- > 0) {
        result *= base;
    }

    while (exp++ < 0) {
        result /= base;
    }

    return result;
}