#include "client.h"

char *mx_strrchr(const char *str, int ch) {
	char *last_occurrence = NULL;
	
	while (*str != '\0') {
		if (*str == (char)ch) {
			last_occurrence = (char *)str;
		}
		
		str++;
	}

	if (ch == '\0') {
		return (char *)str;
	}

	return last_occurrence;
}

char *mx_strstr(const char *haystack, const char *needle) {
	if (needle == NULL || haystack == NULL) {
		return NULL;
	}
	
	if (*needle == '\0') {
		return (char *)haystack;	
	}

	while (*haystack) {
		const char *h = haystack;
		const char *n = needle;

		while (*h && *n && *h == *n) {
			n++;
			h++;
		}

		if (*n == '\0') {
			return (char *)haystack;
		}
		
		haystack++;
	}

	return NULL;
}

char *mx_strcpy(char *dst, const char *src) {
	char *orig = dst;
	
	while (*src) {
		*dst = *src;
		src++;
		dst++;
	}

	*dst = '\0';
	return orig;
}

bool mx_isalpha(int c) {
	if ((c >= 65 && c<= 90) || (c >= 97 && c <= 122)) {
		return true;
	}
	else {
		return false;
	}
}

bool mx_isdigit(int c) {
	if (c >= 47 && c <= 57) {
		return true;
	}
	else {
		return false;
	}
}

bool mx_isspace(char c) {
	if ((c == 32) || (c >= 9 && c <= 13)) {
		return true;
	}
	else {
		return false;
	}
}

bool mx_ispunct(int ch) {
	if ((ch >= '!' && ch <= '/') ||
        	(ch >= ':' && ch <= '@') ||
		(ch >= '[' && ch <= '`') ||
        	(ch >= '{' && ch <= '~'))
	{
        	return true;
	}

	return false;
}

bool mx_isupper(int c) {
	if (c >= 65 && c <= 90) {
		return 1;
	}
	else {
		return 0;
	}
}

bool mx_islower(int c) {
	if (c >= 97 && c <= 122) {
		return true;
	}
	else {
		return false;
	}
}

int mx_strlen(const char *s) {
	int length = 0;
	
	while (s[length] != '\0') {
		length += 1;
	}

	return length;
}

