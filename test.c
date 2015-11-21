
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	int i = 0, j = 0;
	short **nums;

	if (NULL == (nums = malloc(2*sizeof(short)))) {
		printf("error\n");
		exit(EXIT_FAILURE);
	}
	if (NULL == (nums[0] = malloc(2*sizeof(short)))) {
		printf("error\n");
		exit(EXIT_FAILURE);
	}
	if (NULL == (nums[1] = malloc(2*sizeof(short)))) {
		printf("error\n");
		exit(EXIT_FAILURE);
	}
	
	//printf("%x %x\n", nums, nums++);
	/*scanf("%d", &nums);
	scanf("%d %d", nums, nums++);
	printf("nums0: %d\n", nums[0]);
	printf("nums1: %d\n", nums[-1]);
	*/

	printf("nums: %x\n", nums);
	printf("nums0: %x\n", nums[0]);
	printf("nums1: %x\n", nums[1]);
	printf("\n\nprinting addresses...\n");
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 2; j++) {
			printf("& num[%d][%d]: %x\n", i, j, &(nums[i][j]));
		}
	}

	/*
	for (i = 0; i < 2; i++) {
		printf("row %d: ", i);
		scanf("%d %d", &(nums[i][0]), &(nums[i][1]));
	}
	*/

	/*
	scanf("%d %d %d %d %d %d %d %d %d", &nums[0], &nums[1], &nums[2], &nums[3], &nums[4],
 										&nums[5], &nums[6],  &nums[7], &nums[8]);
										*/
	
	printf("\n\nprinting...\n");
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 2; j++) {
			printf("num[%d][%d]: %d\n", i, j,  nums[i][j]);
		}
	}

	free(nums);
	return 1;
}

