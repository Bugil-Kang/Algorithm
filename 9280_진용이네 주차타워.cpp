#define MAX_SPACE 101
#define MAX_CAR 2001
#include <stdio.h>

int T;
int N, M;
int fare[MAX_SPACE];
int wait[MAX_CAR];
int process[MAX_CAR * 2];
int wp, rp;

struct MinHeap {
	int heap[MAX_SPACE];
	int heapSize = 0;

	void heapPush(int idx)
	{
		heap[heapSize] = idx; // heap 끄트머리에 삽입
		int current = heapSize;

		while (current > 0 /* 현재 위치가 정점이 아니고(정점 - 0) = 부모 노드가 있고 */ && heap[current] < heap[(current - 1) / 2] /* 부모 노드 heap 값이 자손 노드보다 큰 경우 */) 
		{
			int temp = heap[(current - 1) / 2];
			heap[(current - 1) / 2] = heap[current];
			heap[current] = temp;
			current = (current - 1) / 2; // 최소 heap 이므로, 부모 노드 < 자손 노드가 되어야 하고, 현재 노드보다 부모 노드가 더 큰 값이 있으므로, 위치를 바꾸고, 위치를 저장한다
		}
		heapSize = heapSize + 1; // 끝나고 나면 최종적으로 heapSize를 갱신해준다(1개 삽입되었으므로)
	}

	int heapPop()
	{
		int nReturn = heap[0]; // 튀어 나갈 heap 값 미리 저장
		heapSize = heapSize - 1; // heapSize 를 업데이트 하고(1개 튀어나가야 하므로)
		heap[0] = heap[heapSize]; // 제일 끝값을 정점에 넣고 위와 같이 update 시작
		int current = 0;

		while (current * 2 + 1 < heapSize) // 자식이 있다면 = 왼쪽 자식이 있다면
		{
			int child; // 자식들 중에서 더
			if (current * 2 + 2 == heapSize) // 오른쪽 자식이 없다면
				child = current * 2 + 1; // 왼쪽 자식이 더 값이 작은 자식이다.
			else
				child = heap[current * 2 + 1] < heap[current * 2 + 2] ? current * 2 + 1 : current * 2 + 2;

			if (heap[current] < heap[child])
				break;

			int temp = heap[current];
			heap[current] = heap[child];
			heap[child] = temp;
			current = child;
		}
		return nReturn;
	}
};

MinHeap minheap;

struct CAR {
	int weight;
	int space;
};
CAR car[MAX_CAR + 1];

void Init() {
	for (int i = 0; i < MAX_SPACE; i++)
		fare[i] = 0;

	for (int i = 0; i < MAX_CAR; i++)
	{
		process[2 * i] = process[2 * i + 1] = 0;
		car[i].space = car[i].weight = 0;
	}
	car[MAX_CAR].space = car[MAX_CAR].weight = 0;
	wp = rp = 0;
	minheap.heapSize = 0;
}
int Processing() {
	for (int i = 0; i < 2 * M; i++) {
		int current = process[i];
		if (current > 0) { // 들어온 것
			if (minheap.heapSize == 0) { // 주차 공간 꽉 찼음
				wait[wp++] = current;
			}
			else {
				int remain = minheap.heapPop();
				car[current].space = remain;
			}
		}
		else { // 나간 것
			int outspace = car[-current].space;
			minheap.heapPush(outspace);
			if (wp > rp) {
				int waitcar = wait[rp++];
				int nextspace = minheap.heapPop();
				car[waitcar].space = nextspace;
			}
		}
	}
	int rtn = 0;
	for (int i = 1; i <= M; i++)
	{
		int now = car[i].space;
		rtn += (fare[now] * car[i].weight);
	}
	return rtn;
}
int main() {

	//setbuf(stdout, NULL);
	//freopen("car.txt", "r", stdin);

	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		Init();

		scanf("%d %d", &N, &M);
		int temp;

		for (int i = 1; i <= N; i++) {
			scanf("%d", &temp);
			fare[i] = temp;
			minheap.heapPush(i); // N번호 까지 남는 주차공간 번호를 최소 힙에 삽입
		}

		for (int i = 1; i <= M; i++) {
			scanf("%d", &temp);
			car[i].weight = temp;
		}

		for (int i = 0; i < 2 * M; i++) {
			scanf("%d", &temp);
			process[i] = temp;
		}
		int result = Processing();
		printf("#%d %d\n", t, result);
	}
	return 0;
}