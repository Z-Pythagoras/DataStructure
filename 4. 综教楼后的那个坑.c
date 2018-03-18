#include<stdio.h>
#include<stdlib.h>

typedef long long ll;
typedef struct pit {
	int w, h, num;
	ll time;
	struct pit *prior, *next;
}pit, *ppit;

const int maxh = 0x3f3f3f3f;
ppit head, r, p, q, min;

int main() {
	int n, w, h;
	scanf("%d", &n);
	ll *time = (ll*)malloc(sizeof(ll) * n);
	head = (ppit)malloc(sizeof(pit));
	head->h = maxh; head->next = head->prior = NULL;
	p = q = head;
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &w, &h);
		p = (ppit)malloc(sizeof(pit));
		p->num = i;	p->h = h; p->w = w; p->time = 0;
		p->prior = q; q->next = p; q = p;
	}
	r = (ppit)malloc(sizeof(pit));
	r->h = maxh;
	p->next = r; r->prior = p; r->next = NULL; p = p->next;
	min = p;
	for (int i = n + 2; i > 0; i--) {
		if (p->h <= min->h)
			min = p;
		p = p->prior;
	}
	p = min;
	ll clock = 0;
	while (p->prior->h != p->next->h) {
		p->time = clock + p->w;
		time[p->num] = p->time;
		if (p->prior->h > p->next->h) {
			clock += (p->next->h - p->h)*p->w;
			p->next->w += p->w;
			p->prior->next = p->next;
			p->next->prior = p->prior;
			p = p->next;
		}
		else {
			clock += (p->prior->h - p->h)*p->w;
			p->prior->w += p->w;
			p->prior->next = p->next;
			p->next->prior = p->prior;
			p = p->prior;
		}
		if (p->next->h > p->h && p->prior->h > p->h)
			continue;
		else if (p->prior->h < p->next->h)
			while (p->h > p->prior->h)
				p = p->prior;
		else
			while (p->h > p->next->h)
				p = p->next;
	}
	clock += p->w;
	p->time = clock;
	time[p->num] = p->time;
	while(n--)
		printf("%lld\n", *(time++));
	return 0;
}