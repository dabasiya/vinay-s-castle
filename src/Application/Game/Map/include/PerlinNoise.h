#pragma once


class PerlinNoise {
public:
    static int p[256];
    static int fastfloor(double value);
    static double noise(double x, double y, unsigned int octaves);
    static double noise(double x, double y);
    static double fade(double t);
    static double lerp(double t, double a, double b);
    static double grad(int hash, double x, double y);
    static const int grad2[8][2];
};