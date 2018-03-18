#include <stdio.h>
#include <stdlib.h>

typedef struct Line {
	int id, time, btime;
	struct Line *next;
}line;
typedef struct{
	int id, num;
	double time;
}airline;

int main() {
	int n, landtime, flytime, landnum, flynum;
	int i, time = 0, flag1 = 0, flag2 = 0, flag3 = 1;
	line *head = NULL, *current, *pre, *p;
	scanf("%d%d%d", &n, &landtime, &flytime);
	for (i = 0; i < n; i++) {
		current = (line*)malloc(sizeof(line));
		if (head == NULL) 
			head = current;
		else
			pre->next = current;
		current->id = i + 1; current->time = -1; current->btime = 0; current->next = NULL;
		pre = current;
	}
	airline take_aline, land_aline;
	take_aline.id = 1; take_aline.num = 0; take_aline.time = 0;
	land_aline.id = 5001; land_aline.num = 0;land_aline.time = 0;
	while (1) {
		printf("Current Time: %4d\n", time++);
		p = head;
		for (i = 0; i < n; i++) {
			if (p->time >= 0) 
				p->btime++;
			if (p->time > 0) 
				p->time--;
			if (p->time == 0) {
				printf("runway %02d is free\n", p->id);
				p->time--;
			}
			p = p->next;
		}
		land_aline.time += land_aline.num;
		take_aline.time += take_aline.num;
		if (flag1 == 0) {
			scanf("%d%d", &landnum, &flynum);
		}
		if (landnum < 0 && flynum < 0) {
			flag1 = 1;
			landnum = 0;
			flynum = 0;
		}
		land_aline.num += landnum;
		take_aline.num += flynum;
		p = head;
		for (i = 0; i < n; i++) {
			if (p->time == -1) {
				if (land_aline.num > 0) {
					printf("airplane %04d is ready to land on runway %02d\n", land_aline.id, p->id);
					p->time = landtime;
					land_aline.num--; land_aline.id++;
				}
				else if (take_aline.num > 0) {
					printf("airplane %04d is ready to takeoff on runway %02d\n", take_aline.id, p->id);
					p->time = flytime;
					take_aline.num--; take_aline.id++;
				}
			}
			p = p->next;
		}
		if (flag1 && !take_aline.num && !land_aline.num) 
			flag2 = 1;
		p = head;
		flag3 = 1;
		for (i = 0; i < n; i++) {
			if (p->time != -1) 
				flag3 = 0;
			p = p->next;
		}
		if (flag2 && flag3) 
			break;
	}
	printf("simulation finished\n");
	printf("simulation time: %4d\n", --time);
	double aland, atake, sum = 0, per;
	aland = land_aline.time / (land_aline.id - 5001);
	atake = take_aline.time / (take_aline.id - 1);
	printf("average waiting time of landing: %4.1f\n", aland);
	printf("average waiting time of takeoff: %4.1f\n", atake);
	p = head;
	for (i = 0; i < n; i++) {
		printf("runway %02d busy time: %4d\n", p->id, p->btime);
		sum += p->btime;
		p = p->next;
	}
	per = sum * 100 / n / time;
	printf("runway average busy time percentage: %4.1f%%\n", per);
	return 0;
}