#include <iostream>
int *createArray(int size)
{
    int *arr = new int[size];
    return arr;
}

int main()
{
    int size = 5;
    int *myArray = createArray(size);

    // Access and modify elements of the array
    for (int i = 0; i < size; i++)
    {
        myArray[i] = i + 1;
    }

    // Print the elements of the array
    for (int i = 0; i < size; i++)
    {
        std::cout << myArray[i] << " ";
    }
    std::cout << std::endl;

    // Don't forget to delete the dynamically allocated memory
    delete[] myArray;

    return 0;
}