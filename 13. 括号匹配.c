#include <stdio.h>

char str[1005], stack[1005];

int match(char *s) {
	int flag = 0, top = -1, i = 0;
	while (s[i] != '\0' && !flag) {
		switch (s[i]) {
		case '(':
		case '[':
		case '{':
			stack[++top] = s[i];
			break;
		case ')':
			if (stack[top] == '(')
				top--;
			else
				flag = 1;
			break;
		case ']':
			if (stack[top] == '[')
				top--;
			else
				flag = 1;
			break;
		case '}':
			if (stack[top] == '{')
				top--;
			else
				flag = 1;
			break;
		}
		i++;
	}
	if (!flag && top == -1)
		return 1;
	else
		return 0;
}

int main() {
	gets(str);
	if (match(str))
		printf("Match succeed!\n");
	else
		printf("Match false!\n");
	return 0;
}