def put_min(min_queue, index, number):
    min_queue.append([index, number])
    current = len(min_queue) - 1
    while(current > 0):
        if current % 2 == 1:
            parent = int((current - 1)/2)
        else:
            parent = int((current - 2)/2)

        if min_queue[parent][1] > min_queue[current][1]:
            temp = min_queue[parent]
            min_queue[parent] = min_queue[current]
            min_queue[current] = temp
            current = parent
        else:
            return min_queue
    return min_queue

def put_max(max_queue, index, number):
    max_queue.append([index, number])
    current = len(max_queue) - 1
    while(current > 0):
        if current % 2 == 1:
            parent = int((current - 1)/2)
        else:
            parent = int((current - 2)/2)

        if max_queue[parent][1] < max_queue[current][1]:
            temp = max_queue[parent]
            max_queue[parent] = max_queue[current]
            max_queue[current] = temp
            current = parent
        else:
            return max_queue
    return max_queue

def pop_min(min_queue):
    rtn = min_queue[0]
    min_queue[0] = min_queue[len(min_queue)-1]
    min_queue.pop(len(min_queue)-1)
    length = len(min_queue)
    Move = True
    current = 0
    while(Move):
        Move = False
        left = current * 2 + 1
        right = current * 2 + 2

        if left >= length:
            return rtn
        elif right >= length:
            if min_queue[current][1] > min_queue[left][1]:
                temp = min_queue[left]
                min_queue[left] = min_queue[current]
                min_queue[current] = temp
                current = left
                Move = True
        else:
            if min_queue[left][1] > min_queue[right][1] and min_queue[current][1] > min_queue[right][1]:
                temp = min_queue[right]
                min_queue[right] = min_queue[current]
                min_queue[current] = temp
                current = right
                Move = True
            elif min_queue[left][1] < min_queue[right][1] and min_queue[current][1] > min_queue[left][1]:
                temp = min_queue[left]
                min_queue[left] = min_queue[current]
                min_queue[current] = temp
                current = left
                Move = True                       
    return rtn

def pop_max(max_queue):
    rtn = max_queue[0]
    max_queue[0] = max_queue[len(max_queue)-1]
    max_queue.pop(len(max_queue)-1)
    length = len(max_queue)
    Move = True
    current = 0
    while(Move):
        Move = False
        left = current * 2 + 1
        right = current * 2 + 2

        if left >= length:
            return rtn
        elif right >= length:
            if max_queue[current][1] < max_queue[left][1]:
                temp = max_queue[left]
                max_queue[left] = max_queue[current]
                max_queue[current] = temp
                current = left
                Move = True
        else:
            if max_queue[left][1] < max_queue[right][1] and max_queue[current][1] < max_queue[right][1]:
                temp = max_queue[right]
                max_queue[right] = max_queue[current]
                max_queue[current] = temp
                current = right
                Move = True
            elif max_queue[left][1] > max_queue[right][1] and max_queue[current][1] < max_queue[left][1]:
                temp = max_queue[left]
                max_queue[left] = max_queue[current]
                max_queue[current] = temp
                current = left
                Move = True                       
    return rtn

def solution(operations):
    answer = []
    number_list = []
    delete_list = []
    min_queue = []
    max_queue = []
    num_count = 0
    count = 0
    for i in range(len(operations)):
        direction = operations[i].split()
        if direction[0] == "I":
            num_count += 1
            number = int(direction[1])
            number_list.append(number)
            delete_list.append(False)
            min_queue = put_min(min_queue, count, number)
            max_queue = put_max(max_queue, count, number)
            count += 1
        else:
            if num_count == 0:
                continue
            number = int(direction[1])
            if number > 0:
                while(True):
                    rtn_list = pop_max(max_queue)
                    index = rtn_list[0]
                    if delete_list[index] == False:
                        num_count -= 1
                        delete_list[index] = True
                        break
            else:
                while(True):
                    rtn_list = pop_min(min_queue)
                    index = rtn_list[0]
                    if delete_list[index] == False:
                        num_count -= 1
                        delete_list[index] = True
                        break

    search = 0
    while(search < len(delete_list)):
        if delete_list[search] == False:
            break
        search += 1

    if search == len(delete_list):
        return [0, 0]
    else:
        max_num = 0
        min_num = 9999999999
        for i in range(search, len(delete_list)):
            if delete_list[i] == True:
                continue

            if number_list[i] > max_num:
                max_num = number_list[i]
            if number_list[i] < min_num:
                min_num = number_list[i]

        return [max_num, min_num]

    return answer
