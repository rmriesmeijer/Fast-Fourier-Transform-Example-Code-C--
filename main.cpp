// Made By Rik Riesmeijer, 2024 - No rights reserved (CC0).
// Fast Fourier Transform Example C++ Code.
// Implementation adapted from: https://www.youtube.com/watch?v=h7apO7q16V0&t=304s
#include <iostream>
#include <vector>
#include <cmath>

// Complex numbers implemented like vec2 in GLM.
struct vec2 {
    public: float x;
            float y;
};

// Defining complex multiplication on our vec2 data structure.
vec2 cmul(vec2 x, vec2 y) {
    vec2 res;
    res.x = x.x * y.x - x.y * y.y;
    res.y = x.x * y.y + y.x * x.y;
    return res;
}

// Defining complex summation on our vec2 data structure.
vec2 cadd(vec2 x, vec2 y) {
    vec2 res;
    res.x = x.x + y.x;
    res.y = x.y + y.y;
    return res;
}

// Defining complex negation on our vec2 data structure.
vec2 neg(vec2 x) {
    x.x = -x.x;
    x.y = -x.y;
    return x;
}

// Randomized vec2 generator for a little test.
vec2 randv() {
    vec2 result;
    float r = float(rand());
    float l = float(rand() % 100) / 50.0f;
    result.x = cos(r);
    result.y = sin(r);
    return result;
}

// Fast Fourier Transform.
// Implementation adapted from: https://www.youtube.com/watch?v=h7apO7q16V0&t=304s
std::vector<vec2> FFT(std::vector<vec2> P) {
    int n = P.size();
    float argom = M_PI * 2.0f / float(n);

    if(n == 1)
        return P;
    else {
        std::vector<vec2> Pe = std::vector<vec2>();
        for(int i = 0; i < n; i += 2) {
            Pe.push_back(P[i]);
        }
        std::vector<vec2> ye = FFT(Pe);

        std::vector<vec2> Po = std::vector<vec2>();
        for(int i = 1; i < n; i += 2) {
            Po.push_back(P[i]);
        }
        std::vector<vec2> yo = FFT(Po);

        std::vector<vec2> y = std::vector<vec2>();
        for(int i = 0; i < n; i++) {
            vec2 v;
            y.push_back(v);
        }

        for(int j = 0; j < n / 2; j++) {
            vec2 omega;
            omega.x = cos(argom * float(j));
            omega.y = sin(argom * float(j));
            y[j]         = cadd(ye[j], cmul(omega, yo[j]));
            y[j + n / 2] = cadd(ye[j], neg(cmul(omega, yo[j])));
        }

        return y;
    }
}

// Unnormalized Inverse Fast Fourier Transform.
// Implementation adapted from: https://www.youtube.com/watch?v=h7apO7q16V0&t=304s
std::vector<vec2> iFFT(std::vector<vec2> P) {
    int n = P.size();
    float argom = -M_PI * 2.0f / float(n);

    if(n == 1)
        return P;
    else {
        std::vector<vec2> Pe = std::vector<vec2>();
        for(int i = 0; i < n; i += 2) {
            Pe.push_back(P[i]);
        }
        std::vector<vec2> ye = iFFT(Pe);

        std::vector<vec2> Po = std::vector<vec2>();
        for(int i = 1; i < n; i += 2) {
            Po.push_back(P[i]);
        }
        std::vector<vec2> yo = iFFT(Po);

        std::vector<vec2> y = std::vector<vec2>();
        for(int i = 0; i < n; i++) {
            vec2 v;
            y.push_back(v);
        }

        for(int j = 0; j < n / 2; j++) {
            vec2 omega;
            omega.x = cos(argom * float(j));
            omega.y = sin(argom * float(j));
            y[j]         = cadd(ye[j], cmul(omega, yo[j]));
            y[j + n / 2] = cadd(ye[j], neg(cmul(omega, yo[j])));
        }

        return y;
    }
}

// Inverse Fast Fourier Transform.
// Implementation adapted from: https://www.youtube.com/watch?v=h7apO7q16V0&t=304s
std::vector<vec2> IFFT(std::vector<vec2> P) {
    std::vector<vec2> y = iFFT(P);
    for(int k = 0; k < y.size(); k++) {
        y[k].x /= float(y.size());
        y[k].y /= float(y.size());
    }
    return y;
}

// A printing function for our list of complex numbers.
void printvs(std::vector<vec2> P) {
    std::cout << "vec2(" << P[0].x << ", " << P[0].y << ")";
    for(int i = 1; i < P.size(); i++) {
        std::cout << ", vec2(" << P[i].x << ", " << P[i].y << ")";
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
}

// Randomized complex number data array generator.
std::vector<vec2> generateP(int m = 32) {
    std::vector<vec2> P = std::vector<vec2>();
    for(int i = 0; i < m; i++)
        P.push_back(randv());
    return P;
}

// Demo of FFT and IFFT.
int main() {
    // Generate a test array.
    std::vector<vec2> P = generateP(16);

    // Print test data.
    printvs(P);

    // Do Fast Fourier Transform on the data.
    std::vector<vec2> y = FFT(P);

    // Print transformed data.
    printvs(y);

    // Do Inverse Fast Fourier Transform on the data.
    std::vector<vec2> z = IFFT(y);

    // Print recovered data.
    printvs(z);

    // Succesful run code.
    return 0;
}
