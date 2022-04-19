#include <iostream>

struct TPair {
	unsigned short key;
	char value[65];
	TPair();
	TPair(int i, char* str);
	void Reset(char ch = '\0');
};

TPair::TPair() {
	key = 0;
	Reset();
}

TPair::TPair(int i, char* str) {
	key = i;
	Reset();
	for (unsigned int j = 0; j < sizeof(str) / sizeof(char); ++j) {
		value[j] = str[j];
	}
}

void TPair::Reset(char ch) {
	for (unsigned int i = 0; i < sizeof(value) / sizeof(char); i++) {
		value[i] = ch;
	}
}

std::ostream& operator<<(std::ostream& output, TPair& pair) {
	if (pair.value[0] == '\0') {
		return output;
	}
	output << pair.key << '\t' << pair.value;
	return output;
}