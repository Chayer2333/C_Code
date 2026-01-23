#include <stdio.h>
#include <math.h>

int main() {
    double x, y, dx = 1.0 / 16, dy = 1.0 / 16;
    for (y = 1.0; y >= -1.0; y -= dy, putchar('\n'))
        for (x = 0.0; x < 6.28; x += dx)
            putchar(" *"[y > 0 != sin(x) < y]);
}
