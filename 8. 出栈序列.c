#include<stdio.h>
int stack[1005], top;

int Pop() {    //³öÕ»
	return stack[--top];
}

void Push(int x) {    //½øÕ»
	stack[top++] = x;
}

int IfTop(int x) {    //ÅÐ¶ÏÊÇ·ñµÈÓÚÕ»¶¥ÔªËØ
	return top && x == stack[top - 1];
}

int main() {
	int n, m, outNum, inNum, flag, cas = 0;
	while (~scanf("%d%d", &n, &m) && (n || m)) {
		if (cas++)    //Êä³öÖ»ÔÚÓÃÀýÖ®¼äÓÐµÄ¿Õ¸ñ
			printf("\n");
		while (m--) {
			flag = 1; inNum = 1; top = 0;    //³õÊ¼»¯
			for (int i = 0; i < n; i++) {    //ÊäÈë³öÕ»ÔªËØ
				scanf("%d", &outNum);
				while (!IfTop(outNum) && flag) {    //ÕÒµ½²»·ûºÏÒªÇóµÄÔªËØ£¬Ö®ºó²»ÔÙ½øÐÐÅÐ¶Ï
					if (outNum < inNum) {
						printf("No\n");
						flag = 0;
						break;
					}
					Push(inNum++);    //1~n½øÕ»
				}
				Pop();    //³öÕ»
			}
			if (flag)    //È«²¿·ûºÏÊä³öYes
				printf("Yes\n");
		}
	}
	return 0;
}