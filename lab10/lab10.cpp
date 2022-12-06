#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void swap(int* a, int index1, int index2) {
    int temp = a[index1];
    a[index1] = a[index2];
    a[index2] = temp;
}

void maxheapify(int *a,int arraysize,int index) {
    if (index * 2 <= arraysize && a[index] < a[index * 2]) {
        swap(a, index, index * 2);
        /*cout << index << " " << index * 2 << endl;
        for (int i = 1; i < arraysize; i++) {
            cout << a[i] << " ";
        }
        cout << endl;*/
    }
    if (index * 2 + 1 <= arraysize && a[index] < a[index * 2 + 1]) {
        swap(a, index, index * 2 + 1);
        /*cout << index << " " << index * 2+1 << endl;
        for (int i = 1; i < arraysize; i++) {
            cout << a[i] << " ";
        }
        cout << endl;*/
    }
}

void build(int* a, int arraysize) {
    for (int i = arraysize-1; i >=1; i--) {
        maxheapify(a, arraysize-1, i);
    }
}

void sort(int* a, int arraysize,int level) {
    swap(a[1], a[level]);
    build(a, level);
    /*for (int i = 1; i < arraysize; i++) {
        cout << a[i] << " ";
    }
    cout << endl;*/
}



int main()
{
    int n;
    ifstream f;
    f.open("input.txt");
    f >> n;
    int size = n + 1;
    int* a = new int[size] {0};
    for (int i = 1; i < size; i++) {
        int number;
        f >> number;
        a[i] = number;
    }
    build(a, size);
    for (int i = n; i >= 1; i--) {
        sort(a, size, i);
    }
    for (int i = 1; i < size; i++) {
        cout << a[i] << " ";
    }

}
