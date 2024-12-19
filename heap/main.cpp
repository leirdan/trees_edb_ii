#include "max-heap.hpp"
#include "min-heap.hpp"
#include "heap.hpp"
#include "../utils.h"
#include <chrono>
#include <exception>

void execute();

int main(int argc, char **argv)
{
    execute();
    return EXIT_SUCCESS;
}

void execute()
{
    const std::string prefix = "./data/random_list_";
    const std::string sorted_prefix = "./data/sorted_random_list_";

    random_list lists[] = {random_list(prefix + "10000.txt", sorted_prefix + "10000_", 10000),
                           random_list(prefix + "100000.txt", sorted_prefix + "100000_", 100000),
                           random_list(prefix + "1000000.txt", sorted_prefix + "1000000_", 1000000)};

    try
    {
        // First, create a max heap and sort it
        for (int i = 0; i < 3; i++)
        {
            std::cout << "Iteration Max Heap:" << i << "\n";
            // 1. Create a dynamic numbers list and save in a file
            generate_random_list(lists[i].filename, lists[i].size);

            // 2. Get all numbers, convert to node-type and create a new heap.
            std::vector<int> data = load_list(lists[i].filename);
            node *array = new node[data.size()];

            for (int i = 0; i < data.size(); i++)
            {
                array[i] = node(data[i]);
            }

            // 3. Using heapsort on MaxHeap
            MaxHeap *max_heap = new MaxHeap(data.size());

            auto start_max = std::chrono::high_resolution_clock::now();

            max_heap->sort(array); // Since heapify compose heapsort algorithm, we pass the array to ensure that heapify will be executed

            auto stop_max = std::chrono::high_resolution_clock::now();

            // 4. Save the ordered list on file
            save_list(lists[i].sorted_filename + "max-heap.txt", max_heap->get_data(), max_heap->get_size());

            // 5. Compute time
            auto duration_max = std::chrono::duration_cast<std::chrono::microseconds>(stop_max - start_max);

            std::cout << "max heap was ordered in " << duration_max.count() << " us.\n";

            delete max_heap;
        }

        // Now, create a min heap and sort
        for (int i = 0; i < 3; i++)
        {
            std::cout << "Iteration Min Heap: " << i << "\n";

            // 1. Get all numbers, convert to node-type and create a new heap.
            std::vector<int> data = load_list(lists[i].filename);
            node *array = new node[data.size()];

            for (int i = 0; i < data.size(); i++)
            {
                array[i] = node(data[i]);
            }

            // 2. Using heapsort on MinHeap
            MinHeap *min_heap = new MinHeap(data.size());

            auto start_min = std::chrono::high_resolution_clock::now();

            min_heap->sort(array);

            auto stop_min = std::chrono::high_resolution_clock::now();

            // 3. Save the ordered list on file
            save_list(lists[i].sorted_filename + "min-heap.txt", min_heap->get_data(), min_heap->get_size());

            // 4. Compute time
            auto duration_min = std::chrono::duration_cast<std::chrono::microseconds>(stop_min - start_min);

            std::cout << "min heap was ordered in " << duration_min.count() << " us.\n";
            delete min_heap;
        }
    }
    catch (const std::exception &ex)
    {
        std::cout << ex.what() << "\n";
    }
}