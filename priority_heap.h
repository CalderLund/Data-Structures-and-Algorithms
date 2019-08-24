//
// Created by Calder Lund on 2019-08-13.
//

#ifndef HEAP_PRIORITY_HEAP_H
#define HEAP_PRIORITY_HEAP_H


#include <vector>
#include <utility>
#include <functional>


template <typename T>
class Heap {
private:
    std::function<bool(T,T)> priority;
    std::vector<T> array;

    // returns index of node i's parent/left/right
    int parent(int i) {
        if (i % 2 == 1) {
            return i/2;
        }
        return i/2 - 1;
    }

    int left(int i) {
        return 2 * i + 1;
    }

    int right(int i) {
        return 2 * i + 2;
    }

    bool leaf(int i, int n) {
        return left(i) >= n;
    }

    /* "bubbles up" until new node is in correct place on heap
     * Time Complexity: O(log n)
     */
    void fix_up(int i) {
        while (i < array.size() && i > 0 &&
               priority(array[parent(i)], array[i])) { // A[parent] < A[i]
            // swap A[i] & A[parent]
            iter_swap(array.begin()+parent(i),
                      array.begin()+i);
            i = parent(i);
        }
    }

    /* heapify converts and array into a heap
     * Time Complexity: O(n)
     */
    void heapify() {
        int n = array.size();

        for (int i = parent(n-1); i >= 0; i--) {
            fix_down(i, n);
        }
    }



public:
    /* Empty heap with comparison function
     * Time Complexity: O(1)
     */
    explicit Heap(std::function<bool(T,T)> f): priority(f) {}

    /* Heapify's array anf gives comparison function
     * Time Complexity: O(n)
     */
    Heap(std::vector<T> arr, std::function<bool(T,T)> f):
            priority(f), array(arr) {
        heapify();
    }


    /* Preserves heap order through fixing downwards
     * Time Complexity: O(log n)
     */
    void fix_down(int i, int n) {
        int j;

        while (!leaf(i, n)) {
            j = left(i);
            if (j < n - 1 && priority(array[j], array[j+1])) // A[j] < A[j+1]
                j++;
            if (!priority(array[i], array[j])) // A[i] >= A[j]
                break;

            // swap A[i] and A[j]
            iter_swap(array.begin()+i, array.begin()+j);
            i = j;
        }
    }


    /* Inserts new element in the heap
     * O(log n)
     */
    void insert(T value) {
        array.emplace_back(value);
        fix_up(array.size()-1);
    }


    void print() {
        for (auto &x: array) {
            std::cout << x << std::endl;
        }
    }
    /* Pops element of highest priority
     * O(log n)
     */
    T pop() {
        T highest_priority = array[0];
        iter_swap(array.begin(), array.begin()+array.size()-1);
        array.pop_back();
        fix_down(0, array.size());
        return highest_priority;
    }

    /* Moves highest priority element to the back
     * O(log n)
     */
    T deleteMax(int n) {
        T highest_priority = array[0];
        iter_swap(array.begin(), array.begin()+n-1);
        fix_down(0, n-1);
        return highest_priority;
    }


    /* Returns a reference to the array
     * O(1)
     */
    std::vector<T> &get_array() {return array;}
};


/* Sorts array using heap
 * Time Complexity: O(n log n)
 * Space Complexity: O(n)
 *
 * NOTE: space can be reduced to O(1) by making
 *       functions outside of class. Current set
 *       up requires building a Heap object, but
 *       we could easily do this in-place.
 */
template <typename T>
std::vector<T> heapsort(std::vector<T> array,
        std::function<bool(T, T)> priority) {

    Heap<T> heap(array, priority);
    int n = array.size();

    while (n > 1) {
        heap.deleteMax(n);
        heap.fix_down(0, --n);
    }

    return heap.get_array();
}

#endif //HEAP_PRIORITY_HEAP_H
