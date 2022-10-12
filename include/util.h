long long get_length_of_int(long long value) {
    long long base = 1;
    int iteration = 1;

    while (value < base) {
        ++iteration;
        base *= 10;
    }

    return iteration;
}