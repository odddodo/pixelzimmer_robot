#ifndef fuzzyLogic_h
#define fuzzyLogic_h
#include <math.h>

float fuzzyGrade(float val, float x0, float x1)
{
    float result = 0;
    float x = val;
    if (x <= x0)
    {
        result = 0;
    }
    else if (x > x1)
    {
        result = 1;
    }
    else
    {
        result = (x / (x1 - x0)) - (x0 / (x1 - x0));
    }
    return result;
}

float fuzzyRevGrade(float val, float x0, float x1)
{
    float result = 0;
    float x = val;
    if (x <= 0)
    {
        result = 1;
    }
    else if (x >= x1)
    {
        result = 0;
    }
    else
    {
        result = (-x / (x1 - x0)) + (x1 / (x1 - x0));
    }
    return result;
}

float fuzzyTriangle(float val, float x0, float x1, float x2)
{
    float result = 0;
    float x = val;
    if (x <= x0||x>=x2)
    {
        result = 0;
    }
    else if (x == x1)
    {
        result = 1;
    }
    else if ((x > x0) && (x < x1))
    {
        result = (x / (x1 - x0)) - (x0 / (x1 - x0));
    }
    else
    {
        result = (-x / (x2 - x1)) + (x2 / (x2 - x1));
    }
    return result;
}

float fuzzyAND(float a, float b)
{
    return fmin(a, b);
}
float fuzzyOR(float a, float b)
{
    return fmax(a, b);
}
float fuzzyNOT(float a)
{
    return 1.0 - a;
}

#endif