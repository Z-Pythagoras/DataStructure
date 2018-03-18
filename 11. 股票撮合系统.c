#include <stdio.h>
#include <stdlib.h>

typedef struct date {
	int orderid, stockid, quantity, bs;
	double price;
	struct date* next;
} DATE, *PDATE;

typedef struct stock {
	int stockid;
	struct stock* next;
	PDATE b, s;
} STOCK, *PSTOCK;

PDATE adress[10000];
PSTOCK ad[10000], home;
int cnt;

PDATE setnew(PDATE p0, int stockid, float price, int quantity, int bs) {
	PDATE p = (PDATE)malloc(sizeof(DATE));
	p->bs = bs;
	if (p0 != NULL) {
		p->next = p0->next;
		p0->next = p;
	}
	else
		p->next = NULL;
	p->orderid = cnt++;
	adress[p->orderid] = p;
	p->price = price; p->quantity = quantity; p->stockid = stockid;
	return p;
}

PSTOCK setnewstock(int stockid) {
	PSTOCK p = (PSTOCK)malloc(sizeof(STOCK));
	ad[stockid] = p;
	p->b = NULL; p->s = NULL; p->stockid = stockid;
	return p;
}

PSTOCK insert(PSTOCK home, int stockid, float price, int bs, int quantity) {
	PDATE p2, p1 = NULL;
	if (ad[stockid] == NULL)
		setnewstock(stockid);
	if (bs == 1) {
		p1 = ad[stockid]->b;
		if (p1 == NULL) {
			ad[stockid]->b = setnew(NULL, stockid, price, quantity, bs);
			return ad[stockid];
		}
		else
			while (1) {
				if (p1->price < price) {
					p2 = setnew(p1, p1->stockid, p1->price, p1->quantity, p1->bs);
					p1->bs = bs;
					int tmp = p2->orderid; p2->orderid = p1->orderid; p1->orderid = tmp;
					p1->price = price; p1->quantity = quantity;
					adress[p2->orderid] = p2; adress[p1->orderid] = p1;
					return ad[stockid];
				}
				else if (p1->next == NULL) {
					setnew(p1, stockid, price, quantity, bs);
					return ad[stockid];
				}
				p1 = p1->next;
			}
	}
	else {
		p1 = ad[stockid]->s;
		if (p1 == NULL) {
			ad[stockid]->s = setnew(NULL, stockid, price, quantity, bs);
			return ad[stockid];
		}
		else
			while (1) {
				if (p1->price > price) {
					p2 = setnew(p1, p1->stockid, p1->price, p1->quantity, p1->bs);
					p1->bs = bs;
					int tmp = p2->orderid; p2->orderid = p1->orderid; p1->orderid = tmp;
					p1->price = price; p1->quantity = quantity;
					adress[p2->orderid] = p2; adress[p1->orderid] = p1;
					return ad[stockid];
				}
				else if (p1->next == NULL) {
					setnew(p1, stockid, price, quantity, bs);
					return ad[stockid];
				}
				p1 = p1->next;
			}
	}
}

PDATE del(PDATE p) {
	adress[p->orderid] = NULL;
	if (p->next == NULL) {
		PSTOCK p0 = ad[p->stockid];
		PDATE p1 = NULL;
		if (p->bs == 1) {
			p1 = p0->b;
			if (p1 == p)
				p0->b = NULL;
			else {
				while (p1->next != p)
					p1 = p1->next;
				p1->next = NULL;
			}
		}
		else {
			p1 = p0->s;
			if (p1 == p)
				p0->s = NULL;
			else {
				while (p1->next != p)
					p1 = p1->next;
				p1->next = NULL;
			}
		}
		return NULL;
	}
	PDATE pn = p->next;
	p->bs = pn->bs; p->next = pn->next; p->orderid = pn->orderid; p->price = pn->price; p->quantity = pn->quantity; p->stockid = pn->stockid;
	adress[p->orderid] = p;
	return p;
}

int fun1(PSTOCK p, int bs, int quantity) {
	printf("orderid: %04d\n", cnt - 1);
	PDATE ps = p->s, pb = p->b;
	while ((ps != NULL && pb != NULL) && ps->price <= pb->price) {
		if (ps->quantity > pb->quantity) {
			if (bs == 1)
				printf("deal--price:%6.1f  quantity:%4d  buyorder:%04d  sellorder:%04d\n", (ps->price + pb->price) / 2.0, pb->quantity, pb->orderid, ps->orderid);
			else
				printf("deal--price:%6.1f  quantity:%4d  sellorder:%04d  buyorder:%04d\n", (ps->price + pb->price) / 2.0, pb->quantity, ps->orderid, pb->orderid);
			ps->quantity -= pb->quantity; pb = del(pb);
		}
		else if (ps->quantity < pb->quantity) {
			if (bs == 1)
				printf("deal--price:%6.1f  quantity:%4d  buyorder:%04d  sellorder:%04d\n", (ps->price + pb->price) / 2.0, ps->quantity, pb->orderid, ps->orderid);
			else
				printf("deal--price:%6.1f  quantity:%4d  sellorder:%04d  buyorder:%04d\n", (ps->price + pb->price) / 2.0, ps->quantity, ps->orderid, pb->orderid);
			pb->quantity -= ps->quantity;
			ps = del(ps);
		}
		else {
			if (bs == 1)
				printf("deal--price:%6.1f  quantity:%4d  buyorder:%04d  sellorder:%04d\n", (ps->price + pb->price) / 2.0, ps->quantity, pb->orderid, ps->orderid);
			else
				printf("deal--price:%6.1f  quantity:%4d  sellorder:%04d  buyorder:%04d\n", (ps->price + pb->price) / 2.0, ps->quantity, ps->orderid, pb->orderid);
			pb = del(pb);
			ps = del(ps);
		}
		if (ps == NULL || pb == NULL)
			break;
	}
	if (quantity == 0) {
		PDATE pdel = ((bs == 1) ? p->b : p->s);
		while (pdel != NULL)
			if (pdel->quantity == 0)
				break;
			else
				pdel = pdel->next;
		if (pdel != NULL)
			del(pdel);
	}
	return 0;
}

void fun2(PSTOCK p) {
	PDATE pt = p->b;
	printf("buy orders:\n");
	while (pt != NULL) {
		printf("orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n", pt->orderid, pt->stockid, pt->price, pt->quantity, pt->bs == 1 ? 'b' : 's');
		pt = pt->next;
	}
	pt = p->s;
	printf("sell orders:\n");
	while (pt != NULL) {
		printf("orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n", pt->orderid, pt->stockid, pt->price, pt->quantity, pt->bs == 1 ? 'b' : 's');
		pt = pt->next;
	}
}

void fun3(PDATE p) {
	if (p == NULL)
		printf("not found\n");
	else {
		printf("deleted order:orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n", p->orderid, p->stockid, p->price, p->quantity, (p->bs == 1) ? 'b' : 's');
		del(p);
	}
}

int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	char choice = '\n', ctemp;
	cnt = 1;
	for (int i = 0; i<1000; i++) {
		adress[i] = NULL;
		ad[i] = NULL;
	}
	PSTOCK p0t;
	DATE temp;
	home = setnewstock(0);
	while (choice) {
		int flag = 1;
		if (choice == '1') {
			scanf("%d%lf%d %c", &temp.stockid, &temp.price, &temp.quantity, &ctemp);
			temp.bs = (ctemp == 'b' ? 1 : 2);
			p0t = insert(home, temp.stockid, temp.price, temp.bs, temp.quantity);
			fun1(p0t, temp.bs, temp.quantity);
		}
		else if (choice == '2') {
			scanf("%d", &temp.stockid);
			p0t = ad[temp.stockid];
			if (p0t == NULL) {
				printf("buy orders:\n");
				printf("sell orders:\n");
				flag = 0;
			}
			if (flag)
				fun2(p0t);
		}
		else if (choice == '3' && flag) {
			int tempid;
			scanf("%d", &tempid);
			fun3(adress[tempid]);
		}
		else if (choice == '0' && flag)
			break;
		choice = getchar();
	}
	return 0;
}