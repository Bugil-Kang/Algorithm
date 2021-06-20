visit = []

def DFS(start, computers):
    visit[start] = 1
    for i in range(len(computers[start])):
        if i == start:
            continue
        if computers[start][i] == 1 and visit[i] == 0:
            DFS(i, computers)


def solution(n, computers):
    answer = 0

    for i in range(200):
        visit.append(0)

    for i in range(n):
        if visit[i] == 1:
            continue

        DFS(i, computers)
        answer += 1

    return answer
