#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binsearch.h"

int binarySearchRecursive(int value[], int start, int end, int key) {
	int ret = -1;
	int middle = 0;

	if (start <= end) {
		middle = (start + end) / 2;
		if (key == value[middle]) {
			ret = middle;
		}
		else if (key < value[middle]) {
			ret = binarySearchRecursive(value, start, middle - 1, key);
		}
		else {
			ret = binarySearchRecursive(value, middle + 1, end, key);
		}
	}
	return ret;
}