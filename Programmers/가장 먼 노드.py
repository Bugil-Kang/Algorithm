queue = []
visit = []
node = {}
def BFS():
    rp = 0
    while(len(queue) != rp):
        info = queue[rp]
        
        for i in range(len(node[info[0]])):
            next_info = node[info[0]][i]
            
            if visit[next_info] == True:
                continue
                
            visit[next_info] = True
            queue.append([next_info, info[1]+1])
        
        rp += 1
    return
  
def solution(n, edge):
    answer = 0
    for i in range(1, n+1):
        node[i] = []
        
    for i in range(len(edge)):
        node1 = edge[i][0]
        node2 = edge[i][1]
        node[node1].append(node2)
        node[node2].append(node1)
        
    queue.append([1, 0])
    global visit
    visit = [False] * (n+1)
    visit[1] = True
    BFS()
    max_distance = queue[len(queue)-1][1]
    for i in range(len(queue)-1, 0, -1):
        if queue[i][1] == max_distance:
            answer += 1
        else:
            break
    return answer
