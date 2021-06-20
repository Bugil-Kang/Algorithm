#define _CRT_SECURE_NO_WARNINGS

#define MAX_NODE 10001
#include <stdio.h>

int Parent[MAX_NODE]; // 전체 노드들의 조상들을 담아줌(부모 노드 없으면 -1)
int visit1[MAX_NODE];
int visit2[MAX_NODE];

void Init()
{
	for (int i = 0; i < MAX_NODE; i++)
		Parent[i] = -1; // 부모로 -1 없으니 -1 삽입

	wp1 = wp2 = 0; // 후에 부모 순회 경로 기록 용
}

int Compare1[MAX_NODE]; // 비교 대상 노드 번호의 조상 노드들을 담아줌
int Compare2[MAX_NODE]; // 비교 대상 노드 번호의 조상 노드들을 담아줌
int wp1, wp2; // Write Point를 0부터 해서 각 Compare 배열에 담음

int find()
{
	int cur1, cur2;
	while (1) // 반복
	{
		cur1 = Compare1[wp1 - 1]; // Compare1 배열 가장 끝 인덱스 추출
		for (int i = 0; i < wp2; i++)
		{
			if (cur1 == Compare2[i]) // Compare2 배열의 조상 번호와 비교
				return cur1; // 맞으면 그대로 Return
		}
		Compare1[wp1++] = Parent[cur1]; // 맞는게 없으면 끝 인덱스의 조상 노드 번호를 삽입

		cur2 = Compare2[wp2 - 1];
		for (int i = 0; i < wp1; i++)
		{
			if (cur2 == Compare1[i])
				return cur2;
		}
		Compare2[wp2++] = Parent[cur2];
	}
	return -1; // 중단점 찍고 오류 확인 -> 올일 없음
}

int main()
{
	int T, N;
	scanf("%d", &T);
	for (int i = 0; i < T; i++) {
		scanf("%d", &N);

		Init(); // 초기화 함수

		int p, c;

		for (int i = 0; i < N - 1; i++)
		{
			scanf("%d %d", &p, &c);
			Parent[c] = p; // 부모 정보 저장
		}

		scanf("%d %d", &p, &c);
		visit2[p] = visit1[c] = 1;

		int result = find(p, c);
		printf("%d\n", result);
	}
	return 0;
}
