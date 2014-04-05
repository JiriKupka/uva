#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

using namespace std;

int max_elephants = 1001;

struct elephant {
	int index;
	int weight;
	int iq;
};

int compare_weight(const void *a, const void *b) {
	elephant e1 = *(elephant*)a;
	elephant e2 = *(elephant*)b;

	if(e1.weight>e2.weight) return -1;
	if(e1.weight==e2.weight) return e1.iq<e2.iq?1:-1;

	return 1;
}

int main(void) {
	int index = 0;
	elephant *elephants = new elephant[max_elephants];

	while(scanf("%d %d",&elephants[index].weight,&elephants[index].iq)==2) {
		elephants[index].index = index++;
	}

	// Seřazení od nejnižšího iq, abychom mohli vybrat rostoucí posloupnost váhy
	qsort(elephants, index, sizeof(elephant), compare_weight);


	// Řešení pomocí http://en.wikipedia.org/wiki/Longest_increasing_subsequence
	// http://stackoverflow.com/questions/2631726/how-to-determine-the-longest-increasing-subsequence-using-dynamic-programming
	// http://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/
	int *lists_length = new int[index];
	int *prev = new int[index];

	int max_length = 1, best_end = 0;
	// Délka seznamů
	lists_length[0] = 1;
	// Seznam, narůstající posloupnost
	prev[0] = -1;

	for(int i = 1; i < index; i++) {
		lists_length[i] = 1;
		prev[i] = -1;

		for (int j = i - 1; j >= 0; j--) {
			if (lists_length[j] + 1 > lists_length[i] && elephants[j].iq < elephants[i].iq) {
				lists_length[i] = lists_length[j] + 1;
				prev[i] = j;
			}
		}

		if (lists_length[i] > max_length) {
			best_end = i;
			max_length = lists_length[i];
		}

	}

	cout << max_length << endl;

	while(best_end!=-1) {
		cout << elephants[best_end].index+1 << endl;
		best_end = prev[best_end];
	}

	return 0;
}