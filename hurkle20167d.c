#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int tx[7];

int tx_check()
{
	int ii, cf = 0;
	for (ii = 0; ii < 7; ii++) {
		if (tx[ii] < 0){
			cf = 1;
			break;
		}
		if (tx[ii] > 15) {
			cf = 1;
			break;
		}
	}
	return cf;
}

int main()
{
	int hx[7], lx[7], rx[7], i, tc, w = -1, wf;
	char clbl[] = { 'X', 'Y', 'Z', 'T', 'U', 'V', 'W' };
	char trash;
	srand(time(0));
	for (i = 0; i < 7; i++) {
		hx[i] = (int)(16.0 * rand() / (RAND_MAX + 1.0));
		lx[i] = -1;
		rx[i] = 16;
	}
	printf("Hurkle 2016 7D\nVS CPU edition\n2016 (c) Kurashov A.K.\n\n");
	printf("Hurkle hiding somewhere in 16x16x16x16x16x16x16 space.\n");
	printf("You have 3 guess chances from 5. Good luck!\n\n");
	for (tc = 5; tc > 0; tc--) {
		if ((tc % 2) == 1) {
			// player
			printf("Guess (X,Y,Z,T,U,V,W): ");
			do {
				scanf("%d,%d,%d,%d,%d,%d,%d", &tx[0], &tx[1],
				      &tx[2], &tx[3], &tx[4], &tx[5], &tx[6]);
				scanf("%c", &trash);
			} while (tx_check());
		} else {
			// CPU
			for (i = 0; i < 7; i++) {
				if ((rx[i] - lx[i]) != 2)
					tx[i] =
					    (int)lx[i] + 1.0 +
					    ((rx[i] - lx[i] -
					      1.0) * rand() / (RAND_MAX + 1.0));
				else
					tx[i] = lx[i] + 1;
			}
			printf
			    ("CPU guessing (%d,%d,%d,%d,%d,%d,%d)...\n",
			     tx[0], tx[1], tx[2], tx[3], tx[4], tx[5], tx[6]);
		}
		wf = 1;
		for (i = 0; i < 7; i++)
			if (tx[i] != hx[i]) {
				wf = 0;
				break;
			}
		if (wf) {
			w = tc % 2;
			break;
		}
		for (i = 0; i < 7; i++) {
			if (hx[i] < tx[i] && hx[i] < rx[i]) {
				rx[i] = tx[i];
				printf("%c < %d; ", clbl[i], tx[i]);
			}
			if (hx[i] > tx[i] && hx[i] > lx[i]) {
				lx[i] = tx[i];
				printf("%c > %d; ", clbl[i], tx[i]);
			}
			if (hx[i] == tx[i]) {
				printf("%c = %d; ", clbl[i], tx[i]);
				lx[i] = tx[i] - 1;
				rx[i] = tx[i] + 1;
			}
		}
		putchar(10);
	}
	if (w == -1)
		printf
		    ("No winner. Hurkle was here: (%d,%d,%d,%d,%d,%d,%d).\n",
		     hx[0], hx[1], hx[2], hx[3], hx[4], hx[5], hx[6]);
	if (w == 0)
		printf("CPU win.\n");
	if (w == 1)
		printf("Player win.\n");
	return 0;
}
