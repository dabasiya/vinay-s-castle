#include "include/PerlinNoise.h"

const int PerlinNoise::grad2[8][2] = {
    {1,1}, {-1,1}, {1,-1}, {-1,-1},
    {1,0}, {-1,0}, {0,1}, {0,-1}
};

int PerlinNoise::p[256] = { 151,160,137,91,90,15,
131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
};

double PerlinNoise::noise(double x, double y) {
    int X = (int)fastfloor(x) & 255;
    int Y = (int)fastfloor(y) & 255;

    x -= fastfloor(x);
    y -= fastfloor(y);

    double u = fade(x);
    double v = fade(y);

    int aa = p[p[X] + Y];
    int ab = p[p[X] + Y + 1];
    int ba = p[p[X + 1] + Y];
    int bb = p[p[X + 1] + Y + 1];

    float res = lerp(v, lerp(u, grad(aa, x, y), grad(ba, x - 1, y)),
        lerp(u, grad(ab, x, y - 1), grad(bb, x - 1, y - 1)));

    return (res + 1.0) / 2.0;
}

double PerlinNoise::noise(double x, double y, unsigned int octaves) {
    double X = x;
    double Y = y;
    double result = 0;
    double a = 1;
    for (int i = 0; i < octaves; i++) {
        result += a * noise(X, Y);
        X *= 2;
        Y *= 2;
        a /= 2;
    }
    return result / octaves;
}

double PerlinNoise::grad(int hash, double x, double y) {
    int h = hash & 7;
    return x * grad2[h][0] + y * grad2[h][1];
}

double PerlinNoise::fade(double t) {
    return t * t * t * (t * (6 * t - 15) + 10);
}

int PerlinNoise::fastfloor(double value) {
    return value >= 0 ? (int)value : (int)value - 1;
}

double PerlinNoise::lerp(double t, double a, double b) {
    return a + t * (b - a);
}