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
		heap[heapSize] = idx; // heap ��Ʈ�Ӹ��� ����
		int current = heapSize;

		while (current > 0 /* ���� ��ġ�� ������ �ƴϰ�(���� - 0) = �θ� ��尡 �ְ� */ && heap[current] < heap[(current - 1) / 2] /* �θ� ��� heap ���� �ڼ� ��庸�� ū ��� */) 
		{
			int temp = heap[(current - 1) / 2];
			heap[(current - 1) / 2] = heap[current];
			heap[current] = temp;
			current = (current - 1) / 2; // �ּ� heap �̹Ƿ�, �θ� ��� < �ڼ� ��尡 �Ǿ�� �ϰ�, ���� ��庸�� �θ� ��尡 �� ū ���� �����Ƿ�, ��ġ�� �ٲٰ�, ��ġ�� �����Ѵ�
		}
		heapSize = heapSize + 1; // ������ ���� ���������� heapSize�� �������ش�(1�� ���ԵǾ����Ƿ�)
	}

	int heapPop()
	{
		int nReturn = heap[0]; // Ƣ�� ���� heap �� �̸� ����
		heapSize = heapSize - 1; // heapSize �� ������Ʈ �ϰ�(1�� Ƣ����� �ϹǷ�)
		heap[0] = heap[heapSize]; // ���� ������ ������ �ְ� ���� ���� update ����
		int current = 0;

		while (current * 2 + 1 < heapSize) // �ڽ��� �ִٸ� = ���� �ڽ��� �ִٸ�
		{
			int child; // �ڽĵ� �߿��� ��
			if (current * 2 + 2 == heapSize) // ������ �ڽ��� ���ٸ�
				child = current * 2 + 1; // ���� �ڽ��� �� ���� ���� �ڽ��̴�.
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
		if (current > 0) { // ���� ��
			if (minheap.heapSize == 0) { // ���� ���� �� á��
				wait[wp++] = current;
			}
			else {
				int remain = minheap.heapPop();
				car[current].space = remain;
			}
		}
		else { // ���� ��
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
			minheap.heapPush(i); // N��ȣ ���� ���� �������� ��ȣ�� �ּ� ���� ����
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