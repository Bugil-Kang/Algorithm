answer_dict = {}

def down(current, count):
    while (count > 0):
        count -= 1
        current = answer_dict[current][1]
    return current


def up(current, count):
    while (count > 0):
        count -= 1
        current = answer_dict[current][0]
    return current

def find_up(end, reinsert):
    current = end
    while(current > reinsert):
        current = answer_dict[current][0]

    after = answer_dict[current][1]
    answer_dict[reinsert][0] = current
    answer_dict[reinsert][1] = after
    answer_dict[current][1] = reinsert
    answer_dict[after][0] = reinsert

    return


def find_down(start, reinsert):
    current = start
    while(current < reinsert):
        current = answer_dict[current][1]

    before = answer_dict[current][0]
    answer_dict[reinsert][0] = before
    answer_dict[reinsert][1] = current
    answer_dict[current][0] = reinsert
    answer_dict[before][1] = reinsert

    return

def solution(n, k, cmd):
    answer_string = ["X"]
    answer_dict[0] = [0, 1]
    delete_stack = []

    for i in range(1, n):
        answer_string.append("X")
        answer_dict[i] = [i - 1, i + 1]
    answer_dict[n - 1] = [n - 2, n - 1]

    start = 0
    end = n-1

    current = k
    for command in cmd:
        detail = command.split()
        if len(detail) == 2:
            if detail[0] == "U":
                current = up(current, int(detail[1]))
            else:
                current = down(current, int(detail[1]))
        else:
            if detail[0] == "C":
                delete_stack.append(current)

                if current == end:
                    before = answer_dict[current][0]
                    current = before
                    end = before
                elif current == start:
                    after = answer_dict[current][1]
                    current = after
                    start = after
                else:
                    before = answer_dict[current][0]
                    after = answer_dict[current][1]

                    answer_dict[after][0] = before
                    answer_dict[before][1] = after
                    current = after
            else:
                reinsert = delete_stack.pop(len(delete_stack)-1)
                if reinsert > end:
                    answer_dict[end][1] = reinsert
                    answer_dict[reinsert][0] = end
                    end = reinsert
                elif reinsert < start:
                    answer_dict[start][0] = reinsert
                    answer_dict[reinsert][1] = start
                    start = reinsert
                else:
                    if end - reinsert > reinsert - start:
                        find_down(start, reinsert)
                    else:
                        find_up(end, reinsert)

    current = start
    while(current != end):
        answer_string[current] = "O"
        current = answer_dict[current][1]
    answer_string[end] = "O"

    return "".join(answer_string)
