#include<stdio.h>
#include<string.h>
int cmp(char a, char b) {
	if (a == '(')
		return -1;
	if ((a == '*' || a == '/') && (b == '+' || b == '-'))
		return 1;
	if ((a == '+' || a == '-') && (b == '*' || b == '/'))
		return -1;
	if ((a == '+' || a == '-') && (b == '+' || b == '-') || (a == '*' || a == '/') && (b == '*' || b == '/'))
		return 1;
	if (a != '^' && b == '^' || a == b && a == '^')
		return -1;
	if (a == '^' && b != '^')
		return 1;
}
int main() {
	int N, top, len;
	char stack[1000], map[1000];
	scanf("%d", &N);
	while (N--) {
		memset(stack, 0, sizeof(stack)); memset(map, 0, sizeof(map));
		stack[0] = '\0'; top = 1;
		scanf("%s", map);
		len = strlen(map);
		for (int i = 0; i < len - 1; i++) {
			if ((map[i] >= 'a' && map[i] <= 'z') || (map[i] >= 'A' && map[i] <= 'Z'))
				printf("%c", map[i]);
			else {
				if (map[i] == '(')
					stack[top++] = map[i];
				else if (map[i] == ')')
					while (1) {
						if (stack[top - 1] == '(') {
							top--;
							break;
						}
						else
							printf("%c", stack[--top]);
					}
				else {
					if (cmp(stack[top - 1], map[i]) < 0)
						stack[top++] = map[i];
					else
						while (1) {
							if (cmp(stack[top - 1], map[i]) > 0)
								printf("%c", stack[--top]);
							else {
								stack[top++] = map[i];
								break;
							}
						}
				}
			}
		}
		while (1) {
			if (stack[top - 1] != '\0')
				printf("%c", stack[--top]);
			else
				break;
		}
		printf("\n");
	}
	return 0;
}