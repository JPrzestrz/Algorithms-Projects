#include <iostream>
#include <string>

using namespace std;

void swap(int* a, int* b)
{
        int temp = *a;
        *a = *b;
        *b = temp;
}

int parent(int i) { return (i - 1) / 2; }
int left(int i) { return (2 * i + 1); }
int right(int i) { return (2 * i + 2); }

void add(int* heap, int x, int* size)
{
        (*size)++;
        int i = *size - 1;
        heap[i] = x;

        while (i != 0 && heap[parent(i)] < heap[i])
        {
                swap(&heap[i], &heap[parent(i)]);
                i = parent(i);
        }
}

void add_min(int* heap, int x, int* size)
{
        (*size)++;
        int i = *size - 1;
        heap[i] = x;

        while (i != 0 && heap[parent(i)] > heap[i])
        {
                swap(&heap[i], &heap[parent(i)]);
                i = parent(i);
        }
}

void heapify(int* heap, int i, int size, int order)
{
        int l = left(i);
        int r = right(i);
        int max = i;
        if (order == 1)
        {
                if (l < size && heap[l] > heap[i])
                        max = l;
                if (r < size && heap[r] > heap[max])
                        max = r;
        }
        else if (order == -1)
        {
                if (l < size && heap[l] < heap[i])
                        max = l;
                if (r < size && heap[r] < heap[max])
                        max = r;
        }
        if (max != i)
        {
                swap(&heap[i], &heap[max]);
                heapify(heap, max, size, order);
        }
}

int del(int* heap, int* size, int order)
{
        if (*size == 1)
        {
                (*size)--;
                return heap[0];
        }

        int head = heap[0];
        heap[0] = heap[*size - 1];
        (*size)--;
        heapify(heap, 0, *size, order);

        return head;
}

int main()
{
        // 1 = max | -1 = min
        int quit = 0;
        int heap[65536];
        int size = 0;
        int order = 1;
        while (quit != 1)
        {
                string command;
                cin >> command;
                if (command == "q")
                        quit = 1;
                else if (command == "+")
                {
                        int data;
                        cin >> data;
                        if (order == 1)
                                add(heap, data, &size);
                        else
                                add_min(heap, data, &size);
                }
                else if (command == "-")
                {
                        if (size > 0)
                        {
                                cout << del(heap, &size, order) << endl;
                        }
                }
                else if (command == "r")
                {
                        for (int i = 0; i < size; i++)
                        {
                                del(heap, &size, order);
                        }
                        size = 0;
                        int n;
                        cin >> n;
                        size = n;
                        for (int i = 0; i < n; i++)
                        {
                                int data;
                                cin >> data;
                                heap[i] = data;
                        }
                        for (int i = size; i >= 0; i--)
                        {
                                heapify(heap, i, size, order);
                        }
                }
                else if (command == "s")
                {
                        order *= -1;
                        for (int i = size; i >= 0; i--)
                        {
                                heapify(heap, i, size, order);
                        }
                }
                else if (command == "p")
                {
                        if (size == 0)
                                cout << endl;
                        else {
                                for (int i = 0; i < size; i++)
                                {
                                        cout << heap[i] << " ";
                                }
                                cout << endl;
                        }
                }
        }
}