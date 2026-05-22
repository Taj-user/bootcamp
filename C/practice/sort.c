#include <stdio.h>
#include <string.h>

// Defining a struct
typedef struct Person {
	char name[50];
	int age;
} Person;

// Helper Functions
static char* get_element(void* base, size_t index, size_t elem_size) { return (char*)base + (index * elem_size); }
static void swap_element(void* base, size_t a, size_t b, size_t elem_size) {
	char* i = get_element(base, a, elem_size);
	char* j = get_element(base, b, elem_size);

	if(i == j){ return; }

	for(size_t k = 0; k < elem_size; k++) {
		char temp = *(i + k);
		*(i + k) = *(j + k);
		*(j + k) = temp;
	}
}

// Pivot calculation
static void pivot(void* base, size_t n, size_t elem_size, int (*comparator)(const void*, const void*)) {
	size_t first = 0;
	size_t mid = n / 2;
	size_t last = n - 1;

	// Sort first and mid
	if(comparator(get_element(base, first, elem_size), get_element(base, mid, elem_size)) > 0){ swap_element(base, first, mid, elem_size); }
	// Sort first and last
	if(comparator(get_element(base, first, elem_size), get_element(base, last, elem_size)) > 0){ swap_element(base, first, last, elem_size); }
	// Sort mid and last
	if(comparator(get_element(base, mid, elem_size), get_element(base, last, elem_size)) > 0){ swap_element(base, mid, last, elem_size); }
	// Move median to last
	swap_element(base, mid, last, elem_size);
}

// Partition calculation
static size_t partition(void* base, size_t n, size_t elem_size, int (*comparator)(const void*, const void*)) {
	// Put pivot at last element
	char* pivot = get_element(base, n - 1, elem_size);
	size_t boundary = 0;

	for(size_t i = 0; i < n - 1; i++) {
		if(comparator(get_element(base, i, elem_size), pivot) <= 0) {
			swap_element(base, boundary, i, elem_size);
			boundary++;
		}
	}

	swap_element(base, boundary, n - 1, elem_size);
	return boundary;
}

// Sorting Functions

// Sort ints in ascending order
int compare_int_asc(const void* a, const void* b) { return *(const int*)a - *(const int*)b; }

// Sort ints in descending order
int compare_int_desc(const void* a, const void* b) { return *(const int*)b - *(const int*)a; }

// Sort floats in ascending order
float compare_float_asc(const void* a, const void* b) { return *(const float*)a - *(const float*)b; }

// Sort floats in descending order
float compare_float_desc(const void* a, const void* b) { return *(const float*)b - *(const float*)a; }

// Sort strings in ascending order
int compare_string_asc(const void* a, const void* b) {
	const char* sa = *(const char**)a;
	const char* sb = *(const char**)b;
	return strcmp(sa, sb);
}

// Sort strings in descending order
int compare_string_desc(const void* a, const void* b) {
	const char* sa = *(const char**)a;
	const char* sb = *(const char**)b;
	return strcmp(sb, sa);
}

// Sort string field in struct in ascending order
int compare_struct_string_asc(const void* a, const void* b) {
	const char* sa = ((const Person*)a)->name;
	const char* sb = ((const Person*)b)->name;
	return strcmp(sa, sb);
}

// Sort string field in struct in descending order
int compare_struct_string_desc(const void* a, const void* b) {
	const char* sa = ((const Person*)a)->name;
	const char* sb = ((const Person*)b)->name;
	return strcmp(sb, sa);
}

// qsort from scratch
void my_qsort(void* array, size_t n, size_t elem_size, int (*comparator)(const void*, const void*)) {
	while(n > 1) {
		pivot(array, n, elem_size, comparator);

		size_t pivot_index = partition(array, n, elem_size, comparator);
		size_t left_size = pivot_index;
		size_t right_size = n - pivot_index - 1;

		if(left_size <= right_size) {
			// recurse to left side
			my_qsort(array, left_size, elem_size, comparator);

			array = get_element(array, pivot_index + 1, elem_size);
			n = right_size;
		}
		else {
			// recurse to right side
			my_qsort(get_element(array, pivot_index + 1, elem_size), right_size, elem_size, comparator);

			n = left_size;
		}
	}
}

int main(void) {
	// Testing
	Person persons[] = { {"Bread", 12}, {"Taj", 19}, {"Ryan", 23}, {"John Brown", 99} };

	size_t size = sizeof(persons) / sizeof(persons[0]);

	my_qsort(persons, size, sizeof(Person), compare_struct_string_asc);

	for(size_t i = 0; i < size; i++) {
		printf("%s\t%d\n", persons[i].name, persons[i].age);
	}
	printf("\n");

	return 0;
}
