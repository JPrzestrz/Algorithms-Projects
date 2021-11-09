#include <iostream>
#include <string>
// hash table 

#define BUCKETS 10

using namespace std;

struct TableItem {
    long long key;
    int value;
    struct TableItem* next;
};

struct HashTable {
    struct TableItem** items;
};

long long Hash_funct(string A, string B)
{
    string text = A + B;
    int p = 31;
    int m = 1e9 + 9;
    long long power_p = 1;
    long long hash_num = 0;
    for (int i = 0; i < text.length(); i++)
    {
        hash_num = (hash_num + (text[i] - 'a' + 1) * power_p) % m;
        power_p = (power_p * p) % m;
    }
    return hash_num;
}

HashTable* create_table()
{
    // allocate memory for all the buckets
    // creating table of items 
    HashTable* hashtable = (HashTable*)malloc(sizeof(HashTable));
    hashtable->items = (TableItem**)malloc(sizeof(TableItem) * BUCKETS);
    for (int i = 0; i < BUCKETS; i++)
    {
        hashtable->items[i] = NULL;
    }
    return hashtable;
}

TableItem* add_item(int value, long long key, HashTable* h_table)
{
    int bucket = key % BUCKETS;
    struct TableItem* temp = NULL;
    // check if the bucket is empty 
    if (h_table->items[bucket] == NULL)
    {
        temp = (struct TableItem*)malloc(sizeof(struct TableItem));
        temp->key = key;
        temp->value = value;
        temp->next = NULL;
        return temp;
    }
    TableItem* head = h_table->items[bucket];
    // check if element with this key already exists 
    while (h_table->items[bucket]->next != NULL)
    {
        
        // element exists - just add value
        if (h_table->items[bucket]->key == key)
        {
            //cout << "\nthis key exists!\n";
            // add value to the existing one
            h_table->items[bucket]->value += value;
            // set item back to head
            // to be able to traverse
            h_table->items[bucket] = head;
            return h_table->items[bucket];
        }
        // switch elements to next 
        h_table->items[bucket] = h_table->items[bucket]->next;
    }
    // element exists - just add value
    if (h_table->items[bucket]->key == key)
    {
        //cout << "this key exists!\n";
        // add value to the existing one
        h_table->items[bucket]->value += value;
        // set item back to head
        h_table->items[bucket] = head;
        return h_table->items[bucket];
    }
    // element doesn't exist add new element 
    temp = (struct TableItem*)malloc(sizeof(struct TableItem));
    temp->key = key;
    temp->value = value;
    temp->next = NULL;
    h_table->items[bucket]->next = temp;
    // set item back to head
    h_table->items[bucket] = head;
    return h_table->items[bucket];
}

void print_table(HashTable* h_table)
{
    // test function for printing 
    // all the buckets line by line
    for (int i = 0; i < BUCKETS; i++)
    {
        cout << "Bucket " << i << " is ";
        if (h_table->items[i] == NULL) cout << "NULL" << endl;
        else
        {
            TableItem* head = h_table->items[i];
            while (h_table->items[i]->next != NULL)
            {
                cout << h_table->items[i]->value << " -> ";
                h_table->items[i] = h_table->items[i]->next;
            }
            cout << h_table->items[i]->value << "\n";
            h_table->items[i] = head;
        }
    }
}

int find_item(HashTable* h_table, int bucket, long long key)
{
    TableItem* head = h_table->items[bucket];
    // xxx
    while (h_table->items[bucket]->next != NULL)
    {
        if (h_table->items[bucket]->key == key)
        {
            int found = h_table->items[bucket]->value;
            h_table->items[bucket] = head;
            return found;
        }
        h_table->items[bucket] = h_table->items[bucket]->next;
    }

    // last item
    if (h_table->items[bucket]->key == key)
    {
        int found = h_table->items[bucket]->value;
        h_table->items[bucket] = head;
        return found;
    }
    else
    {
        h_table->items[bucket] = head;
        return 0;
    }
}

int main()
{
    HashTable* h_table = create_table();
    while (true) {
        string command = "";
        cin >> command;
        if (command == "+")
        {
            // adding new element
            string A, B;
            //cout << "A: ";
            cin >> A;
            //cout << "B: ";
            cin >> B;
            //cout << "value: ";
            int data;
            cin >> data;
            long long key = Hash_funct(A, B);
            //cout << "this is key: " << key << endl;
            if (key < 0)
                key = key * -1;
            if (h_table->items[key % BUCKETS] == NULL)
                h_table->items[key % BUCKETS] = add_item(data, key, h_table);
            else
                add_item(data, key, h_table);
        }
        else if (command == "p")
        {
            // for tests printing
            print_table(h_table);
            cout << "\ntestt!!!!\n";
            for (int i = 0; i < BUCKETS; i++)
            {
                if (h_table->items[i] != NULL)
                    cout << i << " " << h_table->items[i]->value << endl;
                else
                    cout << i << " NULL\n";
            }
            cout << "testt!!!!\n\n";
        }
        else if (command == "?")
        {
            // serching element 
            string A, B;
            //cout << "A: ";
            cin >> A;
            //cout << "B: ";
            cin >> B;
            long long key = Hash_funct(A, B);
            if (key < 0)
                key = key * -1;
            int bucket = key % BUCKETS;
            // no element in this bucket
            if (h_table->items[bucket] == NULL)
                cout << "0\n";
            // looking for the element
            else
            {
                cout << find_item(h_table, bucket, key) << endl;
            }
        }
        else if (command == "q" || command =="")
            break;
        else
            break;
    }
}
