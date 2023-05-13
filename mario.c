#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Get size of gris
    int n = get_size();

    // Print grid of bricks
    print_grid(n);
}

int get_size(void)
{
    int n;
    do
    {
        n = get_int("Size: ");
    }
    while (n < 1);
    return n;
}
void print_grid(int)