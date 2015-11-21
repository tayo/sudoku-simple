
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 9	/* the puzzle is NxN */

void print_puzzle(void);
void read_in(void);
void alloc_puzzle(void);
void alloc_cand(void);
void cand(void);
int add_no_dup(short*, short, short);
int solved(void);
void reset(void);
void free_mem(void);
int restr(int, int, int);
int col_find(int, int);
int row_find(int, int);

short **puz;
short ***puz_can;

int main(int argc, char **argv) {
	int i = 0, j = 0, k = 0;

	alloc_puzzle();
	read_in();
	printf("\n\nPuzzle as read in:\n");
	print_puzzle();
	alloc_cand();

	while (!solved()) {
		if (i == 2) {
			printf("\nno luck after 20 iterations...\nis the puzzle solvable?\nexiting...\n");
			free_mem();
			exit(EXIT_SUCCESS);
		}
		i++;
		cand();
		printf("\nPuzzle after iteration #%d\n", i);
		print_puzzle();
		/*
		if (i == 50) {
			printf("num candidates\n");
			for (j = 0; j < N; j++) 
				for (k = 0; k < N; k++) 
					printf("%d_%d: %d\n", j, k, puz_can[j][k][0]);
		}
		*/
		reset();
	}

	/*
	cand();
	printf("\nPuzzle after one candidacy:\n");
	print_puzzle();
	reset();
	cand();
	printf("\nPuzzle after two candidacies:\n");
	print_puzzle();
	reset();
	cand();
	printf("\nPuzzle after three candidacies:\n");
	print_puzzle();
	*/

	return EXIT_SUCCESS;
}

/* free memory allocated for puzzle and candidacies */
void free_mem(void) {
	int i = 0, j = 0;

	for (i = 0; i < N; i++) {
		free(puz[i]);
		for (j = 0; j < N; j++) {
			free(puz_can[i][j]);
		}
		free(puz_can[i]);
	}
	free(puz);
	free(puz_can);
}

/* reset candidacy by setting number of candidates to zero */
void reset(void) {
	int i = 0, j = 0;

	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			puz_can[i][j][0] = 0;
}

/* returns 1 if the puzzle is solved, 0 otherwise */
int solved(void) {
	int i = 0, j = 0;

	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			if (puz[i][j] == 0)
				return 0;
	return 1;
}

/* add short to an array without duplication */
int add_no_dup(short *list, short num, short len) {
	int i = 0;
	for (i = 0; i < len; i++) {
		if (list[i] == num)
			return 0;
	}
	list[len] = num;
	return 1;
}

int contains(short *arr, short num, short len) {
	short i = 0;
	for (i = 0; i < len; i++)
		if (arr[i] == num)
			return 1;
	return 0;
}
/* calculate candidates for each square */
void cand(void) {
	int i = 0, j = 0, k = 0, m = 0;
	short list[N];  short len = 0;	/* list of already taken numbers */
	short root = (short)(sqrt((double)N));

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			/* if the square is empty, compile a candidate list */
			if (puz[i][j] == 0) {
				//printf("working on empty square %d,%d\n", i, j);
				/* traverse row */
				//printf("before row traversal\n");
				for (m = 0; m < N; m++) 
					if (puz[i][m] > 0)
						list[len++] = puz[i][m];
				/* traverse column */
				//printf("after row, before col traversal\n");
				for (k = 0; k < N; k++) 
					if (puz[k][j] > 0)
						len += add_no_dup(list, puz[k][j], len);
				/* traverse current small square */
				//printf("after col, before sqr traversal\n");
				for (k = (i/root)*root; k < ((i/root)*root + root); k++)
					for (m = (j/root)*root; m < ((j/root)*root + root); m++) {
						if (puz[k][m] > 0)
							len += add_no_dup(list, puz[k][m], len);
					}
				/* create candidate list and store in 3-d structure */
				//printf("after sqr, creating cand list\n");
				for (k = 1; k <= N; k++)	
					if (!contains(list, k, len)) {
						puz_can[i][j][puz_can[i][j][0]+1] = k;
						puz_can[i][j][0]++;
					}
				/* fill in space if value is trivial (only one candidate) */
				if (puz_can[i][j][0] == 1)
					puz[i][j] = puz_can[i][j][1];
				/* fill in space if restricted by neighboring rows/cols */
				else if (puz_can[i][j][0] > 1) {
					for (k = 1; k <= puz_can[i][j][0]; k++) {
						if (restr(i, j, puz_can[i][j][k])) {
							puz[i][j] = puz_can[i][j][k];
							break;
						}
					}
				}

				len = 0; /* clear list of already taken numbers*/
			}
		}
	}
}

int row_find(int row, int num) {
	int i = 0;

	for (i = 0; i < N; i++)
		if (puz[row][i] == num)
			return 1;
	return 0;
}

int col_find(int col, int num) {
	int i = 0;

	for (i = 0; i < N; i++)
		if (puz[i][col] == num)
			return 1;
	return 0;
}

int restr(int i, int j, int num) {
	short root = (short)(sqrt((double)N));
	int k = 0, m = 0;

	/* neighboring cols in sqr */
	for (k = (j/root)*root; k < ((j/root)*root + root); k++) {
		//if ((k != j) && (puz[i][k] == 0))
		if ((k != j))
			if (!(col_find(k, num)))
				return 0;
	}

	/* neighboring rows in sqr */
	for (k = (i/root)*root; k < ((i/root)*root + root); k++) {
		//if ((k != i) && (puz[k][j] == 0))
		if ((k != i))
			if (!(row_find(k, num)))
				return 0;
	}

	return 1;
}

/* allocate memory for the candidates (9 shorts per square) */
void alloc_cand(void) {
	int i = 0, j = 0;

	if (NULL == (puz_can = malloc(N*sizeof(short**)))) {
		fprintf(stderr, "could not malloc memory for puzzle candidates.\nexiting...\n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < N; i++) {
		if (NULL == (puz_can[i] = malloc(N*sizeof(short*)))) {
			fprintf(stderr, "could not malloc memory for puzzle candidates.\nexiting...\n");
			exit(EXIT_FAILURE);
		}
		for (j = 0; j < N; j++) {
			if (NULL == (puz_can[i][j] = malloc(N*sizeof(short)))) {
				fprintf(stderr, "could not malloc memory for puzzle candidates.\nexiting...\n");
				exit(EXIT_FAILURE);
			}
			puz_can[i][j][0] = 0;	/* length of candidate list */
		}
	}
}

/* allocate memory space for the puzzle itself */
void alloc_puzzle(void) {
	int i = 0;

	if (NULL == (puz = malloc(N*sizeof(short*)))) {
		fprintf(stderr, "could not malloc memory for puzzle.\nexiting...\n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < N; i++) {
		if (NULL == (puz[i] = malloc(N*sizeof(short)))) {
			fprintf(stderr, "could not malloc memory for puzzle.\nexiting...\n");
			exit(EXIT_FAILURE);
		}
	}
}

/* read in the puzzle from the user through stdin */
void read_in(void) {
	int i = 0, j = 0;

	printf("Dimensions:  N = %d (length of one side of the puzzle)\n", N);
	printf("\nWe will now read the puzzle into the program.  Enter in numbers row by row.\n");
	printf("Separate each number by a space.  Unknown numbers should be entered\n");
	printf("as zeros.  Example:  Row <num>:  0 0 6 0 1 3 0 0 4\n\n");

	for (i = 0; i < N; i++) {
		printf("Row %d:  ", i+1);
		for (j = 0; j < N; j++) {
			scanf("%d", &puz[i][j]);
		}
	}
}

/* print the puzzle as it stands */
void print_puzzle(void) {
	int i = 0, j = 0, k = 0;
	short root = (short)(sqrt((double)N));

	for (i = 0; i < N; i++) {
		if (i%root == 0) {
			for (k = 0; k < (2*N + 2*root + 1); k++)
				printf("-");
			printf("\n| ");
		}
		else
			printf("| ");

		for (j = 0; j < N; j++) {
			if ((j+1)%root == 0)
				printf("%d | ", puz[i][j]);
			else
				printf("%d ", puz[i][j]);
		}
		printf("\n");
	}
	for (k = 0; k < (2*N + 2*root + 1); k++)
		printf("-");
	printf("\n");
}

