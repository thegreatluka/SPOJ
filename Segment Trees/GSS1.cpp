#include <iostream>
#include <stdint.h>
using namespace std;

struct SegTree
{
	int pSum, sSum, mSum, Sum;
};

int arr[50005];
SegTree segTree[50005<<3];

SegTree meRge(SegTree a, SegTree b)
{
	SegTree res;
	res.Sum = a.Sum + b.Sum;
	res.mSum = max(max(a.mSum, b.mSum), a.sSum + b.pSum);
	res.pSum = max(a.pSum, a.Sum + b.pSum);
	res.sSum = max(b.sSum, b.Sum + a.sSum);
	
	return res;
}

void Construct(int start, int end, int pos)
{
	if(start == end)
	{
	    int X;
	    scanf("%d", &X);
		segTree[pos].pSum = segTree[pos].sSum = segTree[pos].mSum = segTree[pos].Sum = X;
		return;
	}
	
	int mid = (start + end)>>1;
	int l = pos<<1;
	int r = pos<<1|1;
	Construct(start, mid, l);
	Construct(mid+1, end, r);
	
	segTree[pos] = meRge(segTree[l], segTree[r]);
}

SegTree quEry(int pos, int start, int end, int x, int y)
{
	if(start == x && end == y)
	{
		return segTree[pos];
	}
	
	int l = pos<<1;
	int r = pos<<1|1;
	
	int mid = (start + end)>>1;
	
	if(y <= mid)
		return quEry(l, start, mid, x, y);
	else if(x > mid)
		return quEry(r, mid+1, end, x, y);
	else
	{
		return meRge(quEry(l, start, mid, x, mid), quEry(r, mid+1, end, mid+1, y));
	}
}

int main() {
	int N, i, M, X, Y;
	scanf("%d",&N);
	Construct(1, N, 1);
	scanf("%d",&M);
	for(i = 1; i <= M; i++)
	{
		scanf("%d%d",&X,&Y);
		printf("%d\n",quEry(1, 1, N, X, Y).mSum);
	}
	return 0;
}