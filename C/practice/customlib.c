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

// Custom strstr
const char* my_strstr(const char* haystack, const char* needle) {
        if(*needle == '\0') return haystack;
        while(*haystack) {
                const char* h = haystack;
                const char* n = needle;

                while(*h && *n && *h == *n) {
                        ++h;
                        ++n;
                }

                if(*n == '\0') return haystack;
                ++haystack;
        }
        return NULL;
}


int main(void) {
        const char* str = my_strstr("Riddle me this, Riddle me that", "this");
        if(str != NULL) printf("%s", str);

	return 0;
}
