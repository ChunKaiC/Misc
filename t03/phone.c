#include <stdio.h>

int main(int argc, char **argv) {
	char phone[11];
	int index;
	while (scanf("%10s %1d", phone, &index) != EOF) {
		if (index == 0) {
			printf("%s\n", phone);
		} else {
			printf("%c\n", phone[index]);
		}
	}
	return 0;	
}
