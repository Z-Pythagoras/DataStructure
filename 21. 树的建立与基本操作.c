#include <stdio.h>
#include<string.h>

int main() {
	char str[1005], tab[] = "    ";
	int left = 0, degree = 0, deep = -1, nnde[105] = { 0 }, cnt[105] = { 0 };

	scanf("%s", str);
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] == ',')
			continue;
		else if (str[i] == '(') {
			left = 1;
			continue;
		}
		else if (str[i] == ')') {
			if (deep > -1) {
				if (!left)
					cnt[nnde[deep]]++;
				degree = nnde[deep] > degree ? nnde[deep] : degree;
				nnde[deep--] = 0;
				continue;
			}
			else 
				break;
		}
		else {
			if (left == 1) {
				if (deep != -1)
					nnde[deep]++;
				deep++;
				left = 0;
			}
			for (int j = 0; j < deep; j++)
				printf("%s", tab);
			printf("%c\n", str[i]);
		}
	}

	printf("Degree of tree: %d\n", degree);
	for (int i = 0; i <= degree; i++)
		printf("Number of nodes of degree %d: %d\n", i, cnt[i]);

	return 0;
}