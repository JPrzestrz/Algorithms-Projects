#include <iostream>
#include <string>
#include <stdint.h>
using namespace std;

//declaration of stack
struct Node
{
    int data;
    Node* xnp;
};

Node* XOR(Node* a, Node* b)
{
    return (Node*)((uintptr_t)a ^ (uintptr_t)b);
}

void add_front(struct Node** head_addr, int data)
{
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = data;

    new_node->xnp = *head_addr;

    if (*head_addr != NULL)
    {
        (*head_addr)->xnp = XOR(new_node, (*head_addr)->xnp);
    }

    *head_addr = new_node;
}

void add_end(struct Node** end_addr, int data)
{
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->xnp = *end_addr;
    if (*end_addr != NULL)
    {
        (*end_addr)->xnp = XOR((*end_addr)->xnp, new_node);
    }

    *end_addr = new_node;
}

struct Node* add_act(struct Node** head, int value, int position)
{
    // If list is empty
    if (*head == NULL) {

        struct Node* node = (struct Node*)malloc(sizeof(struct Node));
        node->data = value;
        node->xnp = XOR(NULL, NULL);

        *head = node;
    }
    else {

        int Pos = 1;

        struct Node* actual = *head;
        struct Node* prev = NULL;
        struct Node* next = XOR(prev, actual->xnp);

        // Traverse the XOR linked list
        while (next != NULL && Pos < position - 1) {

            prev = actual;
            actual = next;
            next = XOR(prev, actual->xnp);

            // 
            Pos++;
        }
        if (Pos == position - 1) {

            struct Node* node = (struct Node*)malloc(sizeof(struct Node));
            struct Node* temp = XOR(actual->xnp, next);

            actual->xnp = XOR(temp, node);

            if (next != NULL) {

                next->xnp = XOR(node,
                    XOR(next->xnp, actual));
            }
            node->xnp = XOR(actual, next);
            node->data = value;
        }
        else if (position == 1) {
            struct Node* node = (struct Node*)malloc(sizeof(struct Node));

            actual->xnp = XOR(node, XOR(NULL, actual->xnp));
            node->xnp = XOR(NULL, actual);

            *head = node;
            node->data = value;
        }
        else {

        }
    }
    return *head;
}

struct Node* del_beg(struct Node** head)
{
    // If list is not empty
    if (*head != NULL)
    {
        struct Node* temp = *head;

        *head = XOR(NULL, temp->xnp);

        if (*head != NULL) {

            (*head)->xnp = XOR(NULL, XOR(temp, (*head)->xnp));
        }
        free(temp);
    }
    return *head;
}

void del_act(struct Node** head, int position)
{
    if (*head != NULL)
    {
        struct Node* temp = *head;
        struct Node* prev = NULL;
        struct Node* next = NULL;
        for (int i = 0; i < position - 1; i++)
        {
            next = XOR(prev, temp->xnp);
            prev = temp;
            temp = next;
        }
        next = XOR(prev, temp->xnp);
        prev->xnp = XOR(XOR(prev->xnp, temp), next);
        next->xnp = XOR(XOR(next->xnp, temp), prev);

        free(temp);
    }
}

void del_val(struct Node** head, int n, int* actual_pos)
{
    struct Node* temp = *head;
    struct Node* prev = NULL;
    struct Node* next = NULL;
    int i = 1;
    while (temp != NULL)
    {
        next = XOR(prev, temp->xnp);
        prev = temp;
        temp = next;
        i++;
        if (temp->data == n)
        {
            next = XOR(prev, temp->xnp);
            prev->xnp = XOR(XOR(prev->xnp, temp), next);
            next->xnp = XOR(XOR(next->xnp, temp), prev);
            if (*actual_pos >= i)
                *actual_pos--;
            free(temp);
            break;
        }
    }

}

int count_val(struct Node** head, int n)
{
    struct Node* temp = *head;
    struct Node* prev = NULL;
    struct Node* next = NULL;
    int ile = 0;
    while (temp != NULL)
    {
        if (temp->data == n)
        {
            ile++;
        }
        next = XOR(prev, temp->xnp);
        prev = temp;
        temp = next;
    }
    return ile;
}

// to print backward just start form tail 
void print_forward(struct Node* head)
{
    struct Node* actual = head;
    struct Node* prev = NULL;
    struct Node* next;

    if (actual == NULL)
    {
        cout << "NULL";
    }
    while (actual != NULL)
    {
        cout << actual->data << " ";
        next = XOR(prev, actual->xnp);
        prev = actual;
        actual = next;
    }
    cout << endl;
}

void print_position(struct Node* head, int position)
{
    struct Node* actual = head;
    struct Node* prev = NULL;
    struct Node* next;
    if (actual == NULL)
    {
        cout << "NULL\n";
    }
    else {
        for (int i = 0; i < position - 1; i++)
        {
            next = XOR(prev, actual->xnp);
            prev = actual;
            actual = next;
        }
        cout << actual->data << endl;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    struct Node* tail = NULL;
    struct Node* head = NULL;
    //struct Node* actual = NULL, * next = NULL, * prev = NULL;
    int actual_pos = -1, num = 0;
    int quit = 0;
    while (quit != 1)
    {
        if (num < 0)
            num = 0;
        if (num == 0)
            actual_pos = -1;
        if (head == NULL && tail != NULL)
        {
            tail = NULL;
            num = 0;
        }
        else if (tail == NULL && head != NULL)
        {
            head = NULL;
            num = 0;
        }

        string command = "";
        cin >> command;
        if (command == "")
        {
            quit = 1;
        }
        if (command == "ADD_BEG")
        {
            // check if there is no other
            // possibility that head and tail will 
            // be empty or sth
            int data;
            cin >> data;
            if (head == nullptr)
            {
                //cout << "it was empty here!\n";

                add_front(&head, data);
                tail = head;
            }
            else {
                add_front(&head, data);
            }
            if (actual_pos == -1)
                actual_pos = 1;
            else
                actual_pos++;
            num++;

        }
        else if (command == "ADD_END")
        {
            int data;
            cin >> data;
            if (head == nullptr)
            {
                add_end(&tail, data);
                head = tail;
            }
            else {
                add_end(&tail, data);
            }
            num++;
            if (actual_pos == -1)
                actual_pos = num;
        }
        else if (command == "ADD_ACT")
        {
            int data;
            int where;
            cin >> data;
            if (actual_pos == 1)
                where = 1;
            else
                where = actual_pos;
            add_act(&head, data, where);
            actual_pos++;
            num++;
        }
        else if (command == "DEL_BEG")
        {
            head = del_beg(&head);

            num--;
            if (actual_pos == 1)
                actual_pos = num;
            else
                actual_pos--;
            if (num == 0)
                tail = head;
        }
        else if (command == "DEL_END")
        {
            tail = del_beg(&tail);
            if (actual_pos == num)
                actual_pos--;
            num--;
            if (num == 0)
                head = tail;
        }
        else if (command == "DEL_ACT")
        {
            if (actual_pos == 1)
            {
                del_beg(&head);
                num--;
                actual_pos = num;
            }
            else if (actual_pos == num)
            {
                del_beg(&tail);
                num--;
                actual_pos--;
            }
            else
            {
                del_act(&head, actual_pos);
                num--;
                actual_pos--;
            }
        }
        else if (command == "DEL_VAL")
        {
            int data;
            cin >> data;
            if (num == 1 && head->data == data)
            {
                del_beg(&head);
                tail = NULL;
                num = 0;
                actual_pos = -1;
            }
            else {
                // delete first nodes if it is equal to data
                while (head->data == data)
                {
                    head = del_beg(&head);
                    num--;
                    if (actual_pos == 1)
                        actual_pos = num;
                    else
                        actual_pos--;
                    if (num == 0)
                        tail = head;
                }

                // delete last nodes if it is equal to data
                while (tail->data == data)
                {
                    tail = del_beg(&tail);
                    if (actual_pos == num)
                        actual_pos--;
                    num--;
                    if (num == 0)
                        head = tail;
                }
            }
            // delete middle nodes that are equal to data
            int ile = count_val(&head, data);
            for (int i = 0; i < ile; i++)
            {
                del_val(&head, data, &actual_pos);
                num--;
            }
        }
        else if (command == "ACTUAL")
        {
            print_position(head, actual_pos);
        }
        else if (command == "NEXT")
        {
            if (actual_pos == num)
                actual_pos = 1;
            else
                actual_pos++;
            print_position(head, actual_pos);
        }
        else if (command == "PREV")
        {
            if (actual_pos == 1)
                actual_pos = num;
            else
                actual_pos--;
            print_position(head, actual_pos);
        }
        else if (command == "PRINT_FORWARD")
            print_forward(head);
        else if (command == "PRINT_BACKWARD")
            print_forward(tail);
        // quit just for tests 
        else if (command == "QUIT")
            quit = 1;

    }
}