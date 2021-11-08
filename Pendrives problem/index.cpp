#include <iostream>
using namespace std;

void Sort2(int tab[], int id[], int left, int right)
{
	int i = left;
	int j = right;
	int x = tab[(left + right) / 2];
	do
	{
		while (tab[i] < x)
			i++;

		while (tab[j] > x)
			j--;

		if (i <= j)
		{
			swap(tab[i], tab[j]);
			swap(id[i], id[j]);
			i++;
			j--;
		}
	} while (i <= j);

	if (left < j) Sort2(tab, id, left, j);

	if (right > i) Sort2(tab, id, i, right);

}

int main()
{

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	//project 1 pendrive ---
	int n, target;
	cin >> n >> target;

	//reserve space for array of files
	//from pendrive
	int* id= (int*)malloc(n * sizeof(int));
	int* r= (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
	{
		cin >> id[i] >> r[i];
	}

	Sort2(r, id, 0, n - 1);

	//finding number of files that we 
	//are able to copy to 
	//and assigning
	bool quit = false;
	int size = 0;
	int count = 0;
	int switch_point = 0;
	for (int i = 0; i < 2; i++) {
		size = 0;
		quit = false;
		while (quit != true)
		{
			if ((size + r[count] > target) || count >= n)
			{
				quit = true;
				if (i == 0)
					switch_point = count;
			}
			else {
				size += r[count];
				count++;
			}
		}
	}
	Sort2(id, r, 0, switch_point - 1);
	Sort2(id, r, switch_point, count - 1);

	//output pendrives answer
	cout << count << endl;
	cout << "1: ";
	for (int i = switch_point - 1; i >= 0; i--)
	{
		cout << id[i] << " ";
	}
	cout << "\n2: ";
	for (int i = count - 1; i >= switch_point; i--)
	{
		cout << id[i] << " ";
	}

	free(id);
	free(r);
}