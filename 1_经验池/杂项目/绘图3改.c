#include <stdio.h>
#include <math.h>

int main() {
    double x, y, dx = 1.0 / 32, dy = 1.0 / 16;
    for (y = 1.5; y >= -1.5; y -= dy, putchar('\n'))
        for (x = -2.0; x < 1.0; x += dx) 
		{
            
            putchar(" *"[1 - cos(x) > y]);
        }
}
