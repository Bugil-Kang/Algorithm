answer = []
def find_index(reinsert):
    start = 0
    end = len(answer)-1
    while(start != end):
        middle = int((start + end) / 2)
        if reinsert > answer[middle] and reinsert < answer[middle + 1]:
            return middle + 1

        if answer[middle] > reinsert:
            end = middle
        else:
            start = middle
    return int((start + end) / 2)

def solution(n, k, cmd):
    answer_string = []
    delete_stack = []

    for i in range(0, n):
        answer_string.append("X")
        answer.append(i)

    current = k
    for command in cmd:
        detail = command.split()
        if len(detail) == 2:
            if detail[0] == "U":
                current -= int(detail[1])
            else:
                current += int(detail[1])
        else:
            if detail[0] == "C":
                delete_stack.append(answer[current])
                answer.pop(current)
                if current == len(answer):
                    current -= 1
            else:
                reinsert = delete_stack.pop(len(delete_stack) - 1)
                if reinsert > answer[-1]:
                    answer.append(reinsert)
                elif reinsert < answer[0]:
                    answer.insert(0, reinsert)
                    current += 1
                else:
                    now = answer[current]
                    if now > reinsert:
                        current += 1
                    index = find_index(reinsert)
                    answer.insert(index, reinsert)

    for i in range(len(answer)):
        index = answer[i]
        answer_string[index] = "O"
    return "".join(answer_string)
