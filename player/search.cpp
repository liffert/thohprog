#include <iostream>
#include "search.h"
#include <cctype>

bool search(const char *str, std::string array, int str_len, int idx) {
	bool flag = 0;
	int k = array.length();
	k = _path(k, idx);
	int j = 0;

	while (k != array.length() - 3) {
		if (tolower(array[k]) == tolower(str[j])) {
			for (j; j < str_len; j++) {
				if (array[k] == '.' || tolower(str[j]) != tolower(array[k])) {
					flag = 0;
					break;
				}
				k++;
			}
			if (j == str_len) {
				flag = 1;
			}
			j = 0;
			k--;
		}
		if (flag == 1) {
			return true;
		}
		k++;
	}
	return false;
}