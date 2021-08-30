def hash_player(player):
    ret = 0
    for s in player:
        ret += ord(s)

    return ret % 9997


def solution(participant, completion):
    Hash_table = {}
    for i in range(9997):
        Hash_table[i] = []

    for comp in completion:
        hash_key = hash_player(comp)
        Hash_table[hash_key].append(comp)

    check = [False]*len(participant)
    for index in range(len(participant)):
        hash_key = hash_player(participant[index])
        for i in range(len(Hash_table[hash_key])):
            if Hash_table[hash_key][i] == participant[index]:
                Hash_table[hash_key].pop(i)
                check[index] = True
                break
    count = 0
    while(count < len(participant)):
        if check[count] == False:
            break
        count += 1

    answer = participant[count]
    return answer
