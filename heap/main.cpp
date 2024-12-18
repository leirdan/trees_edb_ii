#include "max-heap.hpp"
#include "min-heap.hpp"
#include "heap.hpp"

int main(int argc, char **argv)
{
    int n = 0, aux = 0;
    bool choice = 0;
    Heap *heap = nullptr;

    std::cout << "Insert the amount of elements: ";
    std::cin >> n;

    std::cout << "min or max heap? (0 = min, 1 = max)\n";
    std::cin >> choice;

    if (choice == 0)
        heap = new MinHeap(n);
    else
        heap = new MaxHeap(n);

    node data[n];

    std::cout << "Insert each element: ";
    for (int i = 0; i < n; i++)
    {
        std::cin >> aux;
        data[i] = node(aux);
    }

    heap->heapify(data);
    heap->print();

    std::cout << "Now, insert a new element: ";
    std::cin >> aux;
    heap->insert(aux);
    heap->print();

    std::cout << "Using heap sort... \n";
    heap->sort();
    heap->print();

    return EXIT_SUCCESS;
}