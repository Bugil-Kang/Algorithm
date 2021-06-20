#include <stdio.h>

struct Robot
{
 int r, c;
 int d; //(N: 0, E: 1, S: 2, W: 3)
};

int R, C;
int N, M;
Robot robot[101];
int map[101][101];

void InputData()
{
 char direction;

 scanf("%d %d", &C, &R);
 
 //map 초기화 진행 (로봇이 없는 상태)
 for (int r = 1; r <= R; r++)
  for (int c = 1; c <= C; c++)
   map[r][c] = 0;
 
 scanf("%d %d", &N, &M);

 for (int i = 1; i <= N; i++)
 {
  scanf("%d %d %c", &robot[i].c, &robot[i].r, &direction);

  //(N: 0, E: 1, S: 2, W: 3) robot[i].d
  switch (direction)
  {
  case 'N':
   robot[i].d = 0;
   break;
  case 'E':
   robot[i].d = 1;
   break;
  case 'S':
   robot[i].d = 2;
   break;
  case 'W':
   robot[i].d = 3;
   break;
  }

  // map 에 'i' 로봇이 있다는 것을 표시
  map[ robot[i].r ][ robot[i].c ] = i;
 }
}


//(N: 0, E: 1, S: 2, W: 3)
void TurnLeft(int n)
{
 robot[n].d--;

 if (robot[n].d == -1)
  robot[n].d = 3;
}

void TurnRight(int n)
{
 robot[n].d++;

 if (robot[n].d == 4)
  robot[n].d = 0;
}

//1.Robot X crashes into the wall : X번 로봇이 벽에 충돌하는 경우이다.즉, 주어진 땅의 밖으로 벗어나는 경우가 된다.
//2.Robot X crashes into robot Y : X번 로봇이 움직이다가 Y번 로봇에 충돌하는 경우이다.
//(N: 0, E: 1, S: 2, W: 3)
bool Go(int n)
{
 int nextR, nextC;
 int dr[4] = { 1,0,-1,0 };
 int dc[4] = { 0,1,0,-1 };

 //1. nextR, nextC 구함.
 nextR = robot[n].r + dr[robot[n].d]; // N(0): +1, E(1):  0, S(2): -1, W(3):  0 
 nextC = robot[n].c + dc[robot[n].d]; // N(0):  0, E(1): +1, S(2):  0, W(3): -1


 //2. nextR 과 nextC 값이 1~R,1~C 범위를 벗어나지 않는지 확인.
 //   nextR < 1, nextR > R, nextC < 1, nextC > C --> Fail.(사유: 로봇 n 이 벽에 충돌)
 if (nextR < 1 || nextR > R || nextC < 1 || nextC > C)
 {
  printf("Robot %d crashes into the wall", n);
  return false;
 }

 //3. map[nextR][nextC] 을 확인.
 //   확인했을때, 다른 로봇이 있는 경우 --> Fail. (사유: 로봇 n 이 로봇 'map[nextR][nextC]' 에 충돌)
 if (map[nextR][nextC] != 0)
 {
  printf("Robot %d crashes into robot %d", n, map[nextR][nextC]);
  return false;
 }

 //4. 본인 로봇을 한 칸 이동.
 //   map[ robot[n].r ][ robot[n].c ] = 0;
 //   map[ nextR ][ nextC ] = n;
 //   robot[n].r = nextR; robot[n].c = nextC;
 map[robot[n].r][robot[n].c] = 0; //원래 로봇이 있던 map 을 0 으로 초기화.
 map[nextR][nextC] = n; //다음 이동할 map 에 본인 번호 입력
 robot[n].r = nextR;
 robot[n].c = nextC;

 return true;
}

void Solve()
{
 int n, cnt; //로봇번호, 반복횟수
 char command; //명령 L, R, F
 bool check = true;

 for (int i = 0; i < M; i++)
 {
  scanf("%d %c %d", &n, &command, &cnt);

  switch (command)
  {
  case 'L':
   cnt %= 4; //moduler
   for (int j = 0; j < cnt; j++)
    TurnLeft(n);
   break;
  case 'R':
   cnt %= 4; //moduler
   for (int j = 0; j < cnt; j++)
    TurnRight(n);
   break;
  case 'F':
   for (int j = 0; j < cnt; j++)
   {
    if (Go(n) == false)
    {
     check = false;
     break;
    }
   }
   break;
  }

  if (check == false)
   break;
 }

 if (check == true)
  printf("OK");
}

int main()
{
 InputData();
 Solve();
 return 0;
}
