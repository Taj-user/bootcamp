#include <stdio.h>
#include <string.h>
// #include <sys/time.h>

// TODO: write custom strcmp, and strstr

// #define RUNS 1000000

// Custom strlen
size_t my_strlen(const char* str) {
	const char* start = str;

	while(*str) {
		str++;
	}
	return str - start;
}

// Custom strcpy
char* my_strcpy(char* dest, char* src) {
	if(src == NULL) { return NULL; }

	size_t len = my_strlen(src);
	for(size_t i = 0; i <= len; i++) { *(dest + i) = *(src + i); }

	return dest;
}

// Custom strcat
char* my_strcat(char* dest, char* src) {
	if(src == NULL) { return NULL; }

	size_t src_len = my_strlen(src);
	size_t index;
	for(size_t i = 0; i < src_len; i++) {
		if(*(dest + i) == '\0') { index = i; }
	}
	for(size_t i = index, j = 0; i <= src_len || j <= src_len; i++, j++) { *(dest + i) = *(src + j); }

	return dest;
}

// Custom strcmp
int my_strcmp(const char* str1, const char* str2) {
	if(str1 && str2 == NULL) return -1;
	int str1_ascii = 0;
	int str2_ascii = 0;
	size_t str1_len = my_strlen(str1);
	size_t str2_len = my_strlen(str2);
	for(size_t i = 0; i < str1_len; i++) {
		str1_ascii += (int)(*(str1 + i));
	}
	for(size_t i = 0; i < str2_len; i++) {
		str2_ascii += (int)(*(str2 + i));
	}
	return str1_ascii - str2_ascii;
}

// // Timer
// long long now_microseconds() {
// 	struct timeval tv;
// 	gettimeofday(&tv, NULL);
//
// 	return (long long)tv.tv_sec * 1000000LL + tv.tv_usec;
// }
//
// // Benchmark
// void benchmark(const char* name, size_t (*func)(const char*), const char* arg) {
// 	long long start = now_microseconds();
// 	volatile size_t sink = 0;
//
// 	for(int i = 0; i < RUNS; i++) {
// 		sink += func(arg);
// 	}
//
// 	long long end = now_microseconds();
//
// 	printf("%s: %lld us\n", name, end - start);
// }


int main(void) {
	// const char* test = "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Donec quam felis, ultricies nec, pellentesque eu, pretium quis, sem. Nulla consequat massa quis enim. Donec pede justo, fringilla vel, aliquet nec, vulputate eget, arcu. In enim justo, rhoncus ut, imperdiet a, venenatis vitae, justo. Nullam dictum felis eu pede mollis pretium. Integer tincidunt. Cras dapibus. Vivamus elementum semper nisi. Aenean vulputate eleifend tellus. Aenean leo ligula, porttitor eu, consequat vitae, eleifend ac, enim. Aliquam lorem ante, dapibus in, viverra quis, feugiat a, tellus. Phasellus viverra nulla ut metus varius laoreet. Quisque rutrum. Aenean imperdiet. Etiam ultricies nisi vel augue. Curabitur ullamcorper ultricies nisi. Nam eget dui. Etiam rhoncus. Maecenas tempus, tellus eget condimentum rhoncus, sem quam semper libero, sit amet adipiscing sem neque sed ipsum. Nam quam nunc, blandit vel, luctus pulvinar, hendrerit id, lorem. Maecenas nec odio et ante tincidunt tempus. Donec vitae sapien ut libero venenatis faucibus. Nullam quis ante. Etiam sit amet orci eget eros faucibus tincidunt. Duis leo. Sed fringilla mauris sit amet nibh. Donec sodales sagittis magna. Sed consequat, leo eget bibendum sodales, augue velit cursus nunc,";
	char bread[] = "Bread";
	char butter[] = " Butter";

	int cmp = my_strcmp(bread, butter);
	if(cmp > 0) printf("%s", bread);
	else if(cmp < 0) printf("%s", butter);
	else printf("Both strings equal\n");

	return 0;
}
