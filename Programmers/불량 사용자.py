count_dict = {}
count = 0
visit = []
length = 0

def DFS(current, next, past):
    if next >= 0:
        past = past[0:next] + [True] + past[next+1: len(past)]
    global length
    global visit
    if current == length and past not in visit:
        visit.append(past)
        global count
        count += 1
        return
    elif current == length:
        return

    for i in range(len(count_dict[current])):
        hubo = count_dict[current][i]
        if past[hubo] == True:
            continue

        DFS(current + 1, hubo, past)

    return


def isitpossible(user, ban):
    for i in range(len(user)):
        if user[i] != ban[i]:
            if ban[i] == "*":
                continue
            else:
                return False
    return True


def solution(user_id, banned_id):
    answer = 0
    banned_possible = []
    global length
    length = len(banned_id)

    for i in range(len(banned_id)):
        count_dict[i] = []

    for j in range(len(banned_id)):
        for i in range(len(user_id)):
            if len(banned_id[j]) != len(user_id[i]):
                continue

            if isitpossible(user_id[i], banned_id[j]):
                count_dict[j].append(i)

    DFS(0, -1, [False] * len(user_id))

    return count
