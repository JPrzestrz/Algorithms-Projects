#include <iostream>
#include <cstdlib>
#include <string.h>

using namespace std;

struct people {
        int id_number;
        int ship_number;
};

struct ships {
        char name[100000];
        int crew_members;
};

void change_ship(ships* ship, int size, int act_num)
{
        char name[100000];
        cin >> name;
        strcpy_s(ship[act_num].name, name);
        ship[act_num].crew_members = 0;
}

void add_member(people* member, ships* ship, int size, int number, int act_num)
{
        int applied = 0;
        for (int i = 0; i < size; i++)
        {
                if (member[i].id_number == number)
                {
                        applied = 1;
                        member[i].ship_number = act_num;
                        ship[act_num].crew_members += 1;
                }
        }
        if (applied == 0)
        {
                cout << "Wrong Id\n";
        }
}

int main()
{
        int size, quit=0, act_num=-1,tmp;
        cin >> size;
        people* member = (people*)malloc(size * sizeof(people));
        ships* ship = (ships*)malloc(size * sizeof(ships));
        for (int i = 0; i < size; i++)
        {
                int id;
                cin >> id;
                member[i].id_number = id;
                member[i].ship_number = -1;
        }

        char operation;
        while (quit != 1)
        {
                cin >> operation;
                switch (operation)
                {
                case 'D':
                        act_num += 1;
                        change_ship(ship, size, act_num);
                        break;
                case 'B':
                        cin >> tmp;
                        add_member(member, ship, size, tmp, act_num);
                        
                        break;
                case 'P':
                        cout << "Log:" << endl;
                        for (int i = 0; i < size; i++)
                        {
                                if (member[i].ship_number == -1)
                                {
                                        cout << "Person " << member[i].id_number << ": -" << endl;
                                }
                                else
                                {
                                        cout << "Person " << member[i].id_number << ": ";
                                        cout << ship[member[i].ship_number].name << ", crew: " << ship[member[i].ship_number].crew_members << endl;
                                }
                        }
                        break;
                case 'Q':
                        quit = 1;
                        break;
                default:
                        break;
                }
        }
}