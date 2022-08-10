//A class implementing a matrix supporting these operations: initialize with specific dimensions and given value to fill every field (0 by default), fill a rectangle between two given pairs of coordinates with a specified value, return a pair of unsigned ints with the size of the matrix, make the whole matrix neutral (only if the matrix is a square), random access operator [] to return a vector to hold a column (or maybe a row idk tbh), multiplying operator *, operator ^ to raise the matrix to a certain power (only for square matrices), and operator = to assign the whole matrix to another 
//The class doesn't support error reports, so if you pass inadequate parameters to the class methods it'll be on you and you won't recieve any feedback from the body of the class
//author: Krzysztof Hałubek
#include <iostream>
#include <vector>
#include <algorithm>

class matrix
{
private:
    std::vector<std::vector<long long>> t;
    static constexpr long long MOD = (long long)1e9 + 7;
    void resizeM(size_t a, size_t b, long long val)
    {
        t.resize(a);
        for (size_t i = 0; i < a; i++)
        {
            t[i].resize(b);
            for (size_t j = 0; j < b; j++)
                t[i][j] = val;
        }
    }
public:
    matrix(size_t a, size_t b, long long val = 0)
    {
        resizeM(a, b, val);
    }
    void fill(std::pair<size_t, size_t> a, std::pair<size_t, size_t> b, long long val)
    {
        for (size_t i = a.first; i < b.first; i++)
            for (size_t j = a.second; j < b.second; j++)
                t[i][j] = val;
    }
    std::pair<size_t, size_t> size()
    {
        return { t.size(), t[0].size() };
    }
    void makeNeutral()
    {
        for (size_t i = 0; i < t.size(); i++)
        {
            for (size_t j = 0; j < t.size(); j++)
            {
                if (i == j) t[i][j] = 1;
                else t[i][j] = 0;
            }
        }
    }
    std::vector<long long>& operator [](size_t index)
    {
        return t[index];
    }
    matrix operator *(const matrix& B)
    {

        size_t l = t.size(), m = B.t.size(), n = B.t[0].size();
        matrix C(l, n);
        for (size_t i = 0; i < l; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                C.t[i][j] = 0;
                for (size_t k = 0; k < m; k++)
                    C.t[i][j] = (C.t[i][j] + t[i][k] * B.t[k][j]) % MOD;
            }
        }
        return C;
    }
    matrix operator ^(long long& k)
    {
        int n = t.size();
        long long b = k;
        matrix W(n, n), A = *this;
        W.makeNeutral();
        while (b)
        {
            if (b & 1)
                W = W * A;
            A = A * A;
            b /= 2;
        }
        return W;
    }
    matrix& operator =(const matrix& A)
    {
        this->t = A.t;
        return *this;
    }
};
