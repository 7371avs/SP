#include <cstdio>
#include <cstdint>
#include <cstddef>

extern "C"
{
int foo(int *arr1, int *arr2, size_t size);
}


int main(void) {

    int arr1[] = {1, 2, 3};
    int arr2[] = {1, 2, 3};

    size_t size = sizeof(arr1) / sizeof(int);

    printf("%d\n", foo(arr1, arr2, size));

    return 0;
}
