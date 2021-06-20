#define _CRT_SECURE_NO_WARNINGS

#define MAX_NODE 10001
#include <stdio.h>

int Parent[MAX_NODE]; // ��ü ������ ������� �����(�θ� ��� ������ -1)
int visit1[MAX_NODE];
int visit2[MAX_NODE];

void Init()
{
	for (int i = 0; i < MAX_NODE; i++)
		Parent[i] = -1; // �θ�� -1 ������ -1 ����

	wp1 = wp2 = 0; // �Ŀ� �θ� ��ȸ ��� ��� ��
}

int Compare1[MAX_NODE]; // �� ��� ��� ��ȣ�� ���� ������ �����
int Compare2[MAX_NODE]; // �� ��� ��� ��ȣ�� ���� ������ �����
int wp1, wp2; // Write Point�� 0���� �ؼ� �� Compare �迭�� ����

int find()
{
	int cur1, cur2;
	while (1) // �ݺ�
	{
		cur1 = Compare1[wp1 - 1]; // Compare1 �迭 ���� �� �ε��� ����
		for (int i = 0; i < wp2; i++)
		{
			if (cur1 == Compare2[i]) // Compare2 �迭�� ���� ��ȣ�� ��
				return cur1; // ������ �״�� Return
		}
		Compare1[wp1++] = Parent[cur1]; // �´°� ������ �� �ε����� ���� ��� ��ȣ�� ����

		cur2 = Compare2[wp2 - 1];
		for (int i = 0; i < wp1; i++)
		{
			if (cur2 == Compare1[i])
				return cur2;
		}
		Compare2[wp2++] = Parent[cur2];
	}
	return -1; // �ߴ��� ��� ���� Ȯ�� -> ���� ����
}

int main()
{
	int T, N;
	scanf("%d", &T);
	for (int i = 0; i < T; i++) {
		scanf("%d", &N);

		Init(); // �ʱ�ȭ �Լ�

		int p, c;

		for (int i = 0; i < N - 1; i++)
		{
			scanf("%d %d", &p, &c);
			Parent[c] = p; // �θ� ���� ����
		}

		scanf("%d %d", &p, &c);
		visit2[p] = visit1[c] = 1;

		int result = find(p, c);
		printf("%d\n", result);
	}
	return 0;
}