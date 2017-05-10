#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;

int main()
{
    const int SIZE = 20;
    int array[SIZE];
    generate_n (array, SIZE,
                [] () { return rand() % 30 + 1; });

    for_each (array, array + SIZE, 
              [] (int a){ cout << a << " "; });
    
    cout << endl;
    return 0;
}
