#include<stdio.h>
#include<string.h>
#include<math.h>

int check(char s) {
	if (s == '+' || s == '-' || s == '*' || s == '/' || s == '^' || s == '%')
		return 1;
	else
		return 0;
}

int cmp(char a, char b) {
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
	if ((a == '\0' && check(b)) || (a == '(' && check(b)))
		return -1;
}

int Operator(int a, int b, char s) {
	if (s == '+')
		return a + b;
	if (s == '-')
		return a - b;
	if (s == '*')
		return a*b;
	if (s == '/')
		return a / b;
	if (s == '%')
		return a%b;
	if (s == '^')
		return pow(a, b);
}

int main() {
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	int N, flag_Stack, flag_Num, flag_temp = 1, flag, ppap, qqaq;
	char StackOperator[1000], map[1000];
	int NumOperator[1000];
	scanf("%d", &N);
	while (N--) {
		memset(StackOperator, 0, sizeof(StackOperator)); memset(NumOperator, 0, sizeof(NumOperator)); memset(map, 0, sizeof(map));
		StackOperator[0] = '\0';
		flag = flag_Num = 0; flag_Stack = qqaq = 1;

		scanf("%s", map);
		for (int i = 0; i < strlen(map); i++) {
			flag_temp = ppap = 1;
			if (i == 0 && map[i + 1] >= '0' && map[i + 1] <= '9' && map[0] == '-') {
				flag_temp = -1;
				i++;
				ppap = 0;
			}
			if (i == 0 && map[i + 1] >= '0' && map[i + 1] <= '9' && map[0] == '+' && ppap) {
				i++;
				ppap = 0;
			}
			if (map[i] == '(' && ppap) {
				if (map[i - 1] == ')') {
					printf("error.\n");
					qqaq = 0;
					break;
				}
				if (map[i - 1] >= '0' && map[i - 1] <= '9') {
					printf("error.\n");
					qqaq = 0;
					break;
				}
				if (check(map[i + 1]) && map[i + 1] != '+' && map[i + 1] != '-') {
					printf("error.\n");
					qqaq = 0;
					break;
				}
				StackOperator[flag_Stack++] = map[i];
				if ((map[i + 1] == '+' || map[i + 1] == '-') && map[i + 2] >= '0'&&map[i + 2] <= '9')
					i++;
			}
			else {
				if (map[i] >= '0' && map[i] <= '9') {
					if (map[i - 1] == '-' && (check(map[i - 2]) || map[i - 2] == '(') && ppap)
						flag_temp = -1;
					while (1) {
						if (map[i] >= '0'&&map[i] <= '9') {
							NumOperator[flag_Num] = NumOperator[flag_Num] * 10 + map[i] - '0';
							i++;
						}
						else
							break;
					}
					if (flag_temp == -1)
						NumOperator[flag_Num] *= -1;
					flag_Num++;
					i--;
				}
				else {
					if (check(map[i]) == 1) {
						if (cmp(StackOperator[flag_Stack - 1], map[i]) < 0) {
							StackOperator[flag_Stack] = map[i];
							flag_Stack++;
							if ((map[i + 1] == '+' || map[i + 1] == '-') && map[i + 2] >= '0'&&map[i + 2] <= '9')
								i++;
						}
						else {
							while (1) {
								if (cmp(StackOperator[flag_Stack - 1], map[i])>0) {
									if (NumOperator[flag_Num - 1] == 0 && StackOperator[flag_Stack - 1] == '/') {
										printf("Divide 0.\n");
										qqaq = 0;
										break;
									}
									if (NumOperator[flag_Num - 1] < 0 && StackOperator[flag_Stack - 1] == '^') {
										printf("error.\n");
										qqaq = 0;
										break;
									}
									NumOperator[flag_Num - 2] = Operator(NumOperator[flag_Num - 2], NumOperator[flag_Num - 1], StackOperator[flag_Stack - 1]);
									NumOperator[flag_Num - 1] = 0;
									flag_Num--;
									flag_Stack--;
								}
								else
									break;
							}
							StackOperator[flag_Stack] = map[i];
							flag_Stack++;
							if ((map[i + 1] == '+' || map[i + 1] == '-') && map[i + 2] >= '0'&&map[i + 2] <= '9')
								i++;
						}
					}
					else if(qqaq) {
						if (map[i] == ')') {
							if (map[i + 1] >= '0' && map[i + 1] <= '9') {
								printf("error.\n");
								qqaq = 0;
								break;
							}
							if (map[i + 1] == '(') {
								printf("error.\n");
								qqaq = 0;
								break;
							}
							while (1) {
								if (StackOperator[flag_Stack - 1] != '(') {
									if (NumOperator[flag_Num - 1] == 0 && StackOperator[flag_Stack - 1] == '/') {
										printf("Divide 0.\n");
										qqaq = 0;
										break;
									}
									if (NumOperator[flag_Num - 1] < 0 && StackOperator[flag_Stack - 1] == '^') {
										printf("error.\n");
										qqaq = 0;
										break;
									}
									if (StackOperator[flag_Stack - 1] == '\0') {
										printf("error.\n");
										qqaq = 0;
										break;
									}
									NumOperator[flag_Num - 2] = Operator(NumOperator[flag_Num - 2], NumOperator[flag_Num - 1], StackOperator[flag_Stack - 1]);
									NumOperator[flag_Num - 1] = 0;
									flag_Num--;
									flag_Stack--;
								}
								else {
									flag_Stack--;
									break;
								}
							}
						}
					}
				}
			}
		}

		while (qqaq) {
			if (StackOperator[flag_Stack - 1] != '\0'&&StackOperator[flag_Stack - 1] != '(') {
				if (NumOperator[flag_Num - 1] == 0 && StackOperator[flag_Stack - 1] == '/') {
					printf("Divide 0.\n");
					qqaq = 0;
					break;
				}
				if (NumOperator[flag_Num - 1]<0 && StackOperator[flag_Stack - 1] == '^') {
					printf("error.\n");
					qqaq = 0;
					break;
				}
				NumOperator[flag_Num - 2] = Operator(NumOperator[flag_Num - 2], NumOperator[flag_Num - 1], StackOperator[flag_Stack - 1]);
				NumOperator[flag_Num - 1] = 0;
				flag_Num--;
				flag_Stack--;
			}
			else {
				if (StackOperator[flag_Stack - 1] == '(') {
					printf("error.\n");
					qqaq = 0;
					break;
				}
				else
					break;
			}
		}
		if(qqaq)
			printf("%d\n", NumOperator[0]);
	}
	return 0;
}