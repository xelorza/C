#include <stdio.h>
#include <stdlib.h>
/**
 * Observations: each pile can be viewed individually - meaning maximum can be found
 * on a pile-for-pile basis.
 * Maintain a hash of "number of pruls to get max profit"
 * 	Example: 1
 *		 6 12 3 10 7 16 5
 * Algorithm: For each pile create a "profit" table (10-value):
 *	[ -2 7 0 3 -6 5 ]
 * then add up
 *	[ -2 5 5 8 2 7 ],	whilst keeping track of max (=8)
 * then for all i where pile[i] = max, step thru hash, remove that key and add key+i+1 to hash.
 * 
 * if hash is empty, just add i+1	=> { 4 }
 *
 *
 * Another example:
 *	2
 *	5 7 3 11 9 10
 *	9 1 2 3 4 10 16 10 4 16
 *
 *	=> [ 3 7 -1 1 0]	(1)
 *	=> [ 3 10 9 10 10]	max = 10
 *	=> { 2 4 5 } U+ {}
 *	and 	totalMax += max (= 10)
 *
 *	=> [ 9 8 7 6 0 -6 0 6 -6 ]
 *	=> [ 9 17 24 30 30 24 24 30 24 ]	max = 30
 *	=> { 4 5 8 } U+ { 2 4 5 } = { 6 8 9 7 (9) 10 (10) 12 13 } = { 6 7 8 9 10 12 13 }
 *	and 	totalMax += max (= 40)
 *
 *	print totalMax and SORTED numbers in hash (all or the 10 first)
 *
 * TODO: Make sure an example like this:
 *	2
 *	2 10 9
 *	5 10 10 10 10 10
 *
 *	Gives:
 *
 *	Workyards 2
 *	Maximum profit is 1.
 *	Number of pruls to buy: 2 3 4 5 6 7
 *
 *	In other words - if max == 0 it is ALSO part of the solution
 */

int
main(int argc, char **argv)
{
	/* Input format:
	 * w
	 * b n1 n2 .. nb (w lines of this format)
	 * input ends on w=0
	 */
	int w, b, i, j, k, _,
		*pile,
		totalMax, max, maxCount,
		*res, *ip;

	_ = scanf("%d\n", &w);
	for (;;) {
		totalMax = maxCount = 0;
		res = NULL;
		for (i=0; i<w; i++) {			/* Get w lines */
			_ = scanf("%d", &b);		/* lines start with b */
			pile = (int*)calloc(b, sizeof(int));

			for (j=0; j<b; j++) {		/* Get the rest of the numbers */
				_ = scanf(" %d", pile+j);
				*(pile+j) = 10 - *(pile+j);
			}
/* TODO Remove: */	printf("[ %d ", *pile);
			max = 0;
			for (j=1; j<b; j++) {
				*(pile+j) = *(pile+j-1) + *(pile+j);
/* TODO Remove: */		printf("%d ", *(pile+j));
				if (max < *(pile+j)) {	/* New max found - set */
					max = *(pile+j);
					maxCount = 1;
				}
				else if (max == *(pile+j))
					maxCount++;
			}
/* TODO Remove: */	printf("] (max=%d, maxCount=%d)\n", max, maxCount);

			/* Merge two lists... */
			if (res) {	/* merge into res */
				if (max <= 0)
					goto L;
				int sz=0, *newRes;
				for (ip=res; *ip; ip++, sz++)
					;
				if (!sz) {
					printf("Init res (again)... ");
					res = (int*)calloc(maxCount+1, sizeof(int));
					for (k=j=0; k<b; k++)
						if (*(pile+k) == max)
							*(res+ j++) = k+1;
					goto L;

				}
				printf("sizeof(res) = %d\n", sz);
				newRes = (int*)calloc(sz*maxCount+1, sizeof(int));
				
				/* Step thru matches */
				for (k=j=0; k<b; k++)
					if (*(pile+k) == max) {
						for (ip=res; *ip; ip++) {	/* step thru res */
							_ = *ip+k+1;
							int *newRes_p = newRes;
							for ( ; *newRes_p; newRes_p++)
								if (*newRes_p == _)
									_ = 0;
							if (_)
								*newRes_p = _;
							/* Add *ip+*(pile+k)+1 to newRes
								<=> *ip+*(pile+k)+1 NOT in newRes */
						}
					}

				free(res);
				res = newRes;
			}
			else {	/* init */
/* TODO Remove: */		printf("Init res... ");
				res = (int*)calloc(maxCount+1, sizeof(int));
				for (k=j=0; k<b; k++)
					if (*(pile+k) == max)
					 	res[j++] = k+1;
			}
			L:
/* TODO Remove: */	printf("{ ");
			for (ip = res; *ip; ip++)
				printf("%d ", *ip);
			printf("}\n");

			totalMax += max;
		}
		printf("Workyards %d\n", w);

		printf("Maximum profit is %d.\n", totalMax);
		printf("Number of pruls to buy: ");
		
		/* TODO sort res and print all OR 10 smallest solutions */
		for (ip=res; *ip; ip++, printf(" "))
			printf("%d", *ip);
		printf("\n");

		free(pile);
		_ = scanf("%d\n", &w);

		/* Display a blank line between test cases. */
		if (w) printf("\n");
		else break;
	}
	exit(0);
}
/*
static void
init_res(int **res, int b, int max, int sz, int *pile)
{
	int k,j;
	printf("Init res... ");
	free(res);
	*res = (int*)calloc(sz+1, sizeof(int));
	for (k=j=0; k<b; k++)
		if (*(pile+k) == max)
			*(*res+j++) = k+1;
}*/
