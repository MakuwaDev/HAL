//My implementation of the extended Euclidean algorithm
//Author: Krzysztof Hałubek
void euclid(long long a, long long b, long long& x, long long& y)
{
    if (b != 0)
    {
        euclid(b, a % b, x, y);
        long long h = y;
        y = x - a / b * y;
        x = h;
    }
}
