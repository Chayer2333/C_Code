#include <stdio.h>
#include <math.h>

int main() {
    double x, y, dx = 1.0 / 32, dy = 1.0 / 16;
    for (y = 1.0; y >= -1.0; y -= dy, putchar('\n'))
        for (x = -1.5; x < 1.5; x += dx)
            putchar(" *"[fabs(0.4 * (2 - y) * pow(fabs(x) - 0.65, 4) + pow(fabs(y), 3) - 0.1) < 0.04]);
}
