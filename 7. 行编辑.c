#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char tempinput[50000], *textline[100000];
int Lineth;

void Edit() {
	int i;
	char head[10];
	i = 0;
	gets(head);
	gets(tempinput);
	while (strcmp(tempinput, "[/Text]") != 0) {
		textline[i] = (char *)malloc(strlen(tempinput) + 1);
		strcpy(textline[i++], tempinput);
		gets(tempinput);
	}
	Lineth = i;
}

int compare(char *p, char *q) {
	int i;
	for (i = 0; i<strlen(q); i++, p++)
		if (*p != q[i])
			return 0;
	return 1;
}

void Change() {
	char input;
	char oldstr[50000], newstr[50000], tempstring[50000];
	int l, i, len_Line, len_old, len_new, j, p, q, flag;
	memset(oldstr, 0, sizeof(oldstr));
	memset(newstr, 0, sizeof(newstr));
	i = 0;
	while (1) {
		input = getchar();
		if (input == '/') 
			break;
		if (input != '\\')
			oldstr[i] = input;
		else 
			oldstr[i] = getchar();
		i++;
	}
	i = 0;
	while (1) {
		input = getchar();
		if (input == '\n') 
			break;
		if (input != '\\')
			newstr[i] = input;
		
		else 
			newstr[i] = getchar();
		i++;
	}
	for (l = 0; l<Lineth; l++) {
		len_Line = strlen(textline[l]);
		len_old = strlen(oldstr);
		len_new = strlen(newstr);
		for (i = 0; i<len_Line;) {
			flag = compare(&(textline[l][i]), oldstr);
			if (flag) {
				for (j = 0; j<50000; j++)
					tempstring[j] = 0;
				for (j = 0; j<i; j++)
					tempstring[j] = textline[l][j];
				for (j = 0; tempstring[j] != 0; j++);
				for (p = j, q = 0; q<len_new; q++, p++)
					tempstring[p] = newstr[q];
				for (j = 0; tempstring[j] != 0; j++);
				for (p = j, q = i + len_old; q<len_Line; q++, p++) 
					tempstring[p] = textline[l][q];
				free(textline[l]);
				textline[l] = (char *)malloc(strlen(tempstring) + 1);
				for (j = 0; j<strlen(tempstring); j++)
					textline[l][j] = tempstring[j];
				textline[l][j] = 0;
				len_Line += len_new - len_old;
				i += len_new;
				continue;
			}
			i++;
		}
	}
}

void Insert() {
	int m, i;
	scanf("%d", &m);
	getchar();
	if (m > Lineth)
		m = Lineth + 1;
	if (m < 1)
		m = 1;
	for (i = Lineth; i >= m; i--)
		textline[i] = textline[i - 1];
	memset(tempinput, 0, sizeof(tempinput));
	gets(tempinput);
	textline[m - 1] = (char *)malloc(strlen(tempinput) + 1);
	strcpy(textline[m - 1], tempinput);
	Lineth += 1;
}

void Delete() {
	int m, i, j;
	scanf("%d", &m);
	getchar();
	if (m > Lineth)
		return;
	if (m < 1)
		m = 1;
	free(textline[m - 1]);
	for (i = m, j = m + 1; j <= Lineth; i++, j++)
		textline[i - 1] = textline[j - 1];
	Lineth = i - 1;
}

void Fold() {
	int k, m, i, j;
	int flag1 = 1000000, flag2 = 0;
	char ch;
	scanf("%d/", &k);
	if ( k> Lineth)
		return;
	while (1) {
		scanf("%d", &m);
		ch = getchar();
		if (flag2)
			k--;
		if (flag1<m)
			m--;
		if (m>Lineth)
			continue;
		memset(tempinput, 0, sizeof(tempinput));
		strcpy(tempinput, textline[k - 1]);
		free(textline[k - 1]);
		textline[k - 1] = (char *)malloc(strlen(tempinput) + strlen(textline[m - 1]) + 1);
		strcpy(textline[k - 1], tempinput);
		strcat(textline[k - 1], textline[m - 1]);
		free(textline[m - 1]);
		for (i = m, j = m + 1; j <= Lineth; i++, j++)
			textline[i - 1] = textline[j - 1];
		Lineth--;
		if (m<k)
			flag2 = 1;
		if (m<flag1)
			flag1 = m;
		if (ch == '\n')
			break;
	}
}

int main() {
	freopen("in.txt", "r", stdin);
	char ch1, ch2;
	int j;
	Lineth = 0;
	Edit();
	while (1) {
		ch1 = getchar();
		if (ch1 == EOF)
			break;
		while (ch1 != ' ') {
			ch2 = ch1;
			ch1 = getchar();
		}
		switch (ch2) {
		case 'i':
			Insert(); break;
		case 'd':
			Delete(); break;
		case 'f':
			Fold(); break;
		case 'c':
			Change(); break;
		default:
			break;
		}
	}
	for (j = 0; j < Lineth; j++)
		printf("%s\n", textline[j]);
	
	return 0;
}