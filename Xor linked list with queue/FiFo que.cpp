#include <iostream>
#include <string>
#include <stdint.h>
using namespace std;

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

void add_inside(struct Node** LAST, struct Node** prevl, int data)
{
	struct Node* actual = *LAST;
	struct Node* next = XOR(*prevl, actual->xnp);
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));
	struct Node* temp = XOR(actual->xnp, next);
	actual->xnp = XOR(temp, node);
	if (next != NULL)
		next->xnp = XOR(node, XOR(next->xnp, actual));
	node->xnp = XOR(actual, next);
	node->data = data;
}

struct Node* del(struct Node** head)
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

void print(struct Node* head)
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

void print_queue(struct Node* FIRST, struct Node* prev, struct Node* LAST, struct Node* tail, struct Node* head)
{
	// printing nodes that are between BACK and FRONT
	// including those two 

	while (FIRST != LAST)
	{
		if (FIRST == tail)
			prev = NULL;
		struct Node* temp = FIRST;
		cout << FIRST->data << " ";
		if (FIRST == head)
		{
			FIRST = tail;
			prev = NULL;
		}
		else {
			FIRST = XOR(prev, FIRST->xnp);
			prev = temp;
		}
	}
	cout << FIRST->data << endl;
}

void garbage_soft(struct Node* head, struct Node* tail, struct Node* FIRST, struct Node* LAST, struct Node* prevf)
{
	// we change values of element that are in the list
	// but not in the queue to 0 
	// we go from last to the first element of queue
	struct Node* actual = prevf;
	struct Node* prev = FIRST;
	struct Node* temp;
	while (actual != LAST) {
		actual->data = 0;
		// moving to the end of the list
		if (actual == tail)
		{
			actual = head;
			prev = NULL;
		}
		else
		{
			temp = actual;
			actual = XOR(prev, actual->xnp);
			prev = temp;
		}
	}
}

void garbage_softlist(struct Node* head)
{
	struct Node* actual = head;
	struct Node* prev = NULL;
	struct Node* next;

	while (actual != NULL)
	{
		actual->data = 0;
		next = XOR(prev, actual->xnp);
		prev = actual;
		actual = next;
	}
}

void garbage_hard(struct Node** head, struct Node** tail, struct Node** FIRST, struct Node** LAST, struct Node** prevf, int* size)
{
	struct Node* actual = *prevf;
	struct Node* prev = *FIRST;
	struct Node* next = XOR(prev, actual->xnp);
	while (actual != *LAST) {
		// if actual is last element of list we have to change address to
		// tail to prev
		if (actual == *tail)
		{
			*tail = XOR(NULL, actual->xnp);
			if (*tail != NULL)
				(*tail)->xnp = XOR(NULL, XOR(actual, (*tail)->xnp));
			free(actual);
			actual = *head;
			prev = NULL;
			next = XOR(prev, actual->xnp);
		}
		// if actual is head of the list we have to change address of 
		// head to next 
		else if (actual == *head)
		{
			*head = XOR(NULL, actual->xnp);
			if (*head != NULL)
				(*head)->xnp = XOR(NULL, XOR(actual, (*head)->xnp));
			free(actual);
			actual = *head;
			prev = NULL;
			next = XOR(prev, actual->xnp);
		}
		// if actual is inside of the list we have to change xor 
		// values of prev and next 
		else if (actual != *head && actual != *tail)
		{
			// changing xors of values next to actual 
			// that we will delete 
			prev->xnp = XOR(XOR(prev->xnp, actual), next);
			next->xnp = XOR(XOR(next->xnp, actual), prev);

			free(actual);

			// set new elements
			actual = next;
			next = XOR(prev, actual->xnp);
		}
		(*size)--;
	}
}

void garbage_all(struct Node** head)
{
	while (*head != NULL) {
		struct Node* temp = *head;
		*head = XOR(NULL, temp->xnp);
		if (*head != NULL)
			(*head)->xnp = XOR(NULL, XOR(temp, (*head)->xnp));
		free(temp);
	}
}

int count_que(struct Node* FIRST, struct Node* prev, struct Node* LAST, struct Node* tail, struct Node* head)
{
	// printing nodes that are between BACK and FRONT
	// including those two 
	int ile = 0;
	while (FIRST != LAST)
	{
		ile++;
		if (FIRST == tail)
			prev = NULL;
		struct Node* temp = FIRST;
		if (FIRST == head)
		{
			FIRST = tail;
			prev = NULL;
		}
		else {
			FIRST = XOR(prev, FIRST->xnp);
			prev = temp;
		}
	}
	ile++;
	return ile;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	struct Node* tail = NULL;
	struct Node* head = NULL;
	struct Node* LAST = NULL;
	struct Node* FIRST = NULL;
	struct Node* prev_first = NULL;
	struct Node* prev_last = NULL;
	int quit = 0;
	int size = 0;
	int count = 0;
	while (quit != 1)
	{
		if (count == 0)
		{
			LAST = NULL;
			FIRST = NULL;
		}
		if (size == 0)
		{
			tail = NULL;
			head = NULL;
			LAST = NULL;
			FIRST = NULL;
		}

		string command = "";
		cin >> command;
		if (command == "" || command == "QUIT")
			quit = 1;
		else if (command == "ADD_BEG") {
			int data;
			cin >> data;
			if (size == 0) {
				add_front(&head, data);
				tail = head;
			}
			else {
				add_front(&head, data);
			}
			size++;
		}
		else if (command == "ADD_END") {
			int data;
			int changel = 0;
			int changef = 0;
			cin >> data;
			if (size == 0) {
				add_end(&tail, data);
				head = tail;
			}
			else {
				if (FIRST == tail)
					changef = 1;
				if (LAST == tail)
					changel = 1;
				add_end(&tail, data);
				if (changef == 1)
					prev_first = tail;
				if (changel == 1)
					prev_last = tail;
			}
			size++;
		}
		// #repair counting queue elements 
		// check if size works perfect for all 
		// situations !!!
		else if (command == "DEL_BEG") {
			if (size == 0)
			{

			}
			else if (LAST == head && FIRST == head)
			{
				count = 0;
				size--;
				del(&head);
				FIRST = NULL;
				LAST = NULL;
				prev_first = NULL;
				prev_last = NULL;
			}
			else if (LAST == head)
			{
				count--;
				size--;
				del(&head);
				LAST = head;
				prev_last = XOR(NULL, LAST->xnp);
			}
			else if (FIRST == head)
			{
				count--;
				size--;
				del(&head);
				FIRST = tail;
				prev_first = NULL;
			}
			else
			{
				if (size == 1)
				{
					del(&head);
					size = 0;
					tail = NULL;
				}
				else
				{
					del(&head);
					size--;
				}
			}
		}
		else if (command == "DEL_END") {
			if (size == 0)
				cout << "";
			else if (LAST == tail && FIRST == tail)
			{
				del(&tail);
				LAST = NULL;
				FIRST = NULL;
				prev_first = NULL;
				prev_last = NULL;
				count = 0;
				size--;
			}
			else if (LAST == tail)
			{
				del(&tail);
				LAST = head;
				prev_last = XOR(NULL, LAST->xnp);
				count--;
				size--;
			}
			else if (FIRST == tail)
			{
				del(&tail);
				FIRST = tail;
				prev_first = NULL;
				size--;
				count--;
			}
			else
			{
				if (size == 1)
				{
					del(&tail);
					head = NULL;
					size = 0;
				}
				else
				{
					del(&tail);
					size--;
				}
			}
		}
		else if (command == "PUSH") {
			int data;
			cin >> data;
			// we have to add element because there is no 
			// element in the list but only the queue
			if (size == count)
			{
				//LAST is inside the queue 
				if (LAST != head)
				{
					add_inside(&LAST, &prev_last, data);
					struct Node* temp = LAST;
					LAST = XOR(prev_last, LAST->xnp);
					prev_last = temp;
					count++;
					size++;
					prev_first = LAST;
				}
				//LAST is on the front 
				else {
					prev_last = LAST;
					add_front(&head, data);
					LAST = head;
					count++;
					size++;
					if (count == 1)
					{
						tail = head;
						FIRST = head;
					}
				}
			}
			else {
				// we have to check where this element will go 
				//

				// there is no queue and the list already exist
				if (FIRST == NULL && size > 0)
				{
					tail->data = data;
					FIRST = tail;
					LAST = tail;
					count++;
				}
				// Last element belongs to List so we change it to queue
				else if (prev_first == tail && FIRST != tail && LAST != tail)
				{
					LAST = tail;
					prev_last = NULL;
					LAST->data = data;
					count++;
				}
				// Last element of queue is first element in list and 
				// last element of list is not in a queue so we change it
				// it is the same as above ? ^^
				else if (FIRST != tail && LAST != tail && LAST == head)
				{
					LAST = tail;
					LAST->data = data;
					count++;
					prev_last = NULL;
				}
				else if (size > 0)
				{
					struct Node* temp = LAST;
					LAST = XOR(prev_last, LAST->xnp);
					// test 
					//cout << "changing element: " << LAST->data << " to: " << data << endl;
					LAST->data = data;
					prev_last = temp;
					count++;
				}


			}
		}
		else if (command == "SIZE")
			cout << size << endl;
		else if (command == "COUNT")
		{
			if (count == 0)
				cout << "0\n";
			else
				cout << count_que(FIRST, prev_first, LAST, tail, head) << endl;
		}
		else if (command == "POP") {
			// when we pop element from queue it becomes element of list
			// so we don't remove it 

			if (count == 0)
				cout << "NULL\n";
			else if (count == 1 && size == 1)
			{
				// there is only one element in the list that is 
				// a queue element 
				head = FIRST;
				tail = FIRST;
				cout << FIRST->data << endl;
				FIRST = NULL;
				LAST = NULL;
				prev_last = NULL;
				prev_first = NULL;
				count--;
			}
			else if (count == 1)
			{
				// there is only one element of queue 
				// so we have to clear the queue
				cout << FIRST->data << endl;
				FIRST = NULL;
				LAST = NULL;
				prev_first = NULL;
				prev_last = NULL;
				count = 0;
			}
			else {
				// we just change the FIRST element to the next one  
				// that is in the queue
				cout << FIRST->data << endl;

				// if first element of queue is first element
				// of list we have to cheange it to the tail of
				// the whole list 
				if (FIRST == head)
				{
					FIRST = tail;
					prev_first = NULL;
				}
				else
				{
					struct Node* temp = FIRST;
					FIRST = XOR(prev_first, FIRST->xnp);
					prev_first = temp;
				}
				count--;
			}
		}
		else if (command == "GARBAGE_SOFT") {
			if (count == 0)
				garbage_softlist(head);
			else if (count != size)
				garbage_soft(head, tail, FIRST, LAST, prev_first);
		}
		else if (command == "GARBAGE_HARD") {
			if (count == 0)
			{
				garbage_all(&head);
				tail = NULL;
				size = 0;

			}
			else if (count != size)
			{
				garbage_hard(&head, &tail, &FIRST, &LAST, &prev_first, &size);
				if (LAST != head)
					prev_first = LAST;
				else
					prev_first = NULL;
			}
		}
		else if (command == "PRINT_FORWARD") {
			print(head);
		}
		else if (command == "PRINT_BACKWARD") {
			print(tail);
		}
		else if (command == "PRINT_QUEUE") {
			if (count == 0)
				cout << "NULL\n";
			else
				print_queue(FIRST, prev_first, LAST, tail, head);
		}
		// TEST COMMANDS
		else if (command == "LAST") {
			cout << LAST->data << endl;
		}
		else if (command == "FIRST") {
			cout << FIRST->data << endl;
		}
		else if (command == "prevf") {
			if (prev_first == NULL)
				cout << "NULL\n";
			else
				cout << prev_first->data << endl;
		}
		else if (command == "prevl") {
			if (prev_last == NULL)
				cout << "NULL\n";
			else
				cout << prev_last->data << endl;
		}
		else if (command == "tail") {
			cout << tail->data << endl;
		}
		else if (command == "head") {
			cout << head->data << endl;
		}
	}
	// here remember to add removing of all elements from the list 
	// that left
	while (head) {
		del(&head);
	}
	free(head);
}