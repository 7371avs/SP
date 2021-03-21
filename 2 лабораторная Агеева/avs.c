#include "stdint.h"
#include "stdio.h"
#include "time.h"

//#define CLOCKS_PER_SEC 1000

uint16_t invertHighBits(uint16_t tmp)
{
    uint16_t low = 0x00ff & tmp;
    uint16_t high = 0xff00 & tmp;
    high = ~high;
    high = high / 256 * 256;
    high += low;
    return high;
}

int main()
{
    double start = clock();
    double finish;
    uint16_t array[10] = {0x8000, 0x4000, 0x801, 0x1, 0x2, 0x5, 0x6, 0x7, 0x9, 0xa};
    uint32_t sum = 0;
    for (uint8_t i = 0; i < 10; i++)
    {
        array[i] = invertHighBits(array[i]);
        if ((array[i] % 2) == 0)
        {
            printf("%x\n", array[i]);
            sum += array[i];
        }
    }
    printf("%x", sum);
    printf("\n");
    finish = (clock() - start) / CLOCKS_PER_SEC;
    printf("%f", finish);
    printf("\n");
    return 0;
}