#include <stdio.h>
struct Queue
{
	int r, c;
	int cnt;
};

Queue queue[100 * 100 + 10];

int R, C;
int map[101][101];
int visit[101][101];
int f, b;
int dr[4] = { 0, 1, 0, -1 };
int dc[4] = { 1, 0, -1, 0 };

void Init()
{
	f = 0;
	b = 0;
	for (int r = 1; r <= R; r++)
		for (int c = 1; c <= C; c++)
			visit[r][c] = 0;
}
void Push(Queue data)
{
	queue[b++] = data;
}
Queue Pop()
{
	return queue[f++];
}
bool isEmpty()
{
	if (f == b)
		return true;
	else
		return false;
}
void InputData()
{
	scanf("%d", &R);
	C = R;
	for (int r = 1; r <= R; r++)
		for (int c = 1; c <= C; c++)
			scanf("%d", &map[r][c]);
}
void DFS(int r, int c, int addr)
{
	int nr, nc;
	for (int i = 0; i < 4; i++)
	{
		nr = r + dr[i];
		nc = c + dc[i];

		if (nr < 1 || nr > R || nc < 1 || nc > C)
			continue;

		if (visit[nr][nc] == 1)
			continue;

		if (map[nr][nc] == 0)
			continue;

		visit[nr][nc] = 1;
		map[nr][nc] = addr;

		DFS(nr, nc, addr);
	}
}
int BFS(int addr)
{
	Queue cd, nd;
	while (isEmpty() == false)
	{
		cd = Pop();
		for (int i = 0; i < 4; i++)
		{
			nd.r = cd.r + dr[i];
			nd.c = cd.c + dc[i];
			nd.cnt = cd.cnt + 1;

			if (nd.r < 1 || nd.r > R || nd.c < 1 || nd.c > C)
				continue;

			if (visit[nd.r][nd.c] != 0)
				continue;

			if (map[nd.r][nd.c] != 0)
				if (map[nd.r][nd.c] != addr)
					return cd.cnt;
				else
					continue;

			visit[nd.r][nd.c] = 1;
			Push(nd);

		}

	}
	return 0;
}

int main()
{
	int best = 200;
	Queue sd;
	int addr = 0;
	InputData();
	
	Init();

	for (int r = 1; r <= R; r++)
		for (int c = 1; c <= C; c++)
		{
			if (map[r][c] == 1)
			{
				addr++;
				map[r][c] = addr;
				visit[r][c] = 1;
				DFS(r, c, addr);
			}
		}

	for (int r = 1; r <= R; r++)
		for (int c = 1; c <= C; c++)
			if (map[r][c] != 0)
			{
				Init();
				visit[r][c] = 1;
				sd = { r, c, 0 };
				Push(sd);
				int length = BFS(map[r][c]);
				if (length > 0)
					if (best > length)
						best = length;
			}

	printf("%d", best);
	return 0;
}
