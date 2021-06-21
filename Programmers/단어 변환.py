def difference(word1, word2):
    rtn = 0
    for i in range(len(word1)):
        if word1[i] != word2[i]:
            rtn += 1
        if rtn > 1:
            return False
    return True

def solution(begin, target, words):
    if target not in words:
        return 0
    visit = [begin]
    queue = [[begin, 0]]
    while len(queue) != 0:
        queue_list = queue.pop()
        for word in words:
            if word in visit:
                continue

            if difference(word, queue_list[0]):
                if word == target:
                    return queue_list[1] + 1
                else:
                    visit.append(word)
                    queue.append([word, queue_list[1] + 1])

    return 0
