#include <iostream>
#include <vector>
#include <functional>
#include "priority_heap.h"

using namespace std;

int main() {

    // Ascending Sort
    vector<int> array {2,5,1,8,4,3,9,5};
    function<bool(int,int)> fn = [](int a, int b){return a < b;};
    array = heapsort(array, fn);
    for (auto &x: array) {
        cout << x << ' ';
    }
    cout << endl;

    // Descending Sort
    function<bool(int,int)> fn2 = [](int a, int b){return a > b;};
    vector<int> array2 = heapsort(array, fn2);
    for (auto &x: array2) {
        cout << x << ' ';
    }
    cout << endl;

    // Sort Characters
    vector<char> array3 {'h','e','a','p','i','f','y'};
    function<bool(char,char)> fn3 = [](char a, char b){return a < b;};
    array3 = heapsort(array3, fn3);
    for (auto &x: array3) {
        cout << x << ' ';
    }
    cout << endl;
}

