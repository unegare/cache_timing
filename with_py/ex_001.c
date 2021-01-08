#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#define ARR_LEN 1048576

int arr[(ARR_LEN>>2)] = {0, };

int main() {
	clock_t t1,t2,t3,t4,t5,t6;
	int i = 0, j = 0;
	int temp = 0;
	srand(time(NULL));
	while(i < ((ARR_LEN>>2)>>4)) {
//		printf("%u\n", i);
		int j = (rand() % ((ARR_LEN>>2)>>4))<<4;
		while (arr[j] != 0) {
			j += 16;
			if (j >= (ARR_LEN>>2)) {
//				int z = 0;
				j -= (ARR_LEN>>2);
//				while(z < (ARR_LEN>>2)) {
//					printf("%u ", arr[z]);
//					z += 16;
//				}
//				printf("\n-----------------------------------------------\n");
			}
		}
		arr[j] = (i<<4);
		i++;
	}

	//printf("GO INSIDE\n");

	i = 0;
	t1 = clock();
	while(i < 1000) {
		j = 0;
		while (j < ((ARR_LEN>>2)>>4)) {
			temp += arr[(j<<4)];
			j++;
		}
		i++;
	}
	t2 = clock();

	i = 0;
	t3 = clock();
	while(i < 1000) {
		j = ((ARR_LEN>>2)>>4) -1;
		while (j >= 0) {
			temp += arr[(j<<4)];
			j--;
		}
		i++;
	}
	t4 = clock();

	i = 0;
	t5 = clock();
	while(i < 1000) {
		int k = 0;
		temp = 0;
		while(k < ((ARR_LEN>>2)>>4)) {
			temp = arr[temp];
			k++;
		}
		i++;
	}
	t6 = clock();

	printf("%Lu %u %u %u\n", (unsigned long long)(ARR_LEN),
			(unsigned)(((long double)(t2-t1)*1000000000)/(((ARR_LEN>>2)>>4)*1000*CLOCKS_PER_SEC)),
			(unsigned)(((long double)(t4-t3)*1000000000)/(((ARR_LEN>>2)>>4)*1000*CLOCKS_PER_SEC)),
			(unsigned)(((long double)(t6-t5)*1000000000)/(((ARR_LEN>>2)>>4)*1000*CLOCKS_PER_SEC)));
	return 0;
}
