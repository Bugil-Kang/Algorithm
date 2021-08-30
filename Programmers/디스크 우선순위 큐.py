min_queue = []
def put_min(index, number):
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
            return
    return

def pop_min():
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

def sorting(jobs):
    for i in range(len(jobs)):
        for j in range(0, len(jobs)-1-i):
            comp1 = jobs[j]
            comp2 = jobs[j+1]
            if comp1[0] > comp2[0]:
                temp = jobs[j]
                jobs[j] = jobs[j+1]
                jobs[j+1] = temp
            elif comp1[0] == comp2[0] and comp1[1] > comp2[1]:
                temp = jobs[j]
                jobs[j] = jobs[j+1]
                jobs[j+1] = temp

    return jobs

def solution(jobs):
    end_time = 0
    in_time = [] ## 들어온 시간
    take_time = [] ## 걸리는 시간
    out_time = [-1] * len(jobs)
    jobs = sorting(jobs)

    for job in jobs:
        in_time.append(job[0])
        take_time.append(job[1])

    now = jobs[0][0]
    end_time = now + jobs[0][1]
    out_time[0] = end_time
    index = 1
    jobs.pop(0)


    while(len(jobs) > 0 or len(min_queue) > 0):
        Move = False
        if len(min_queue) != 0 and now == end_time:
            next_task = pop_min()
            ind = next_task[0]
            end_time = now + take_time[ind]
            out_time[ind] = end_time

        while(len(jobs) > 0 and jobs[0][0] <= end_time):
            wait_task = jobs.pop(0)
            comp_num = wait_task[1] * 1000 + wait_task[0]
            put_min(index, comp_num)
            index += 1
            Move = True

        if Move == True:
            continue

        if now == end_time and len(jobs) != 0:
            now = jobs[0][0]
            end_time = jobs[0][0]
        else:
            now = end_time

    wait_sum = 0
    for i in range(len(out_time)):
        wait_sum += (out_time[i] - in_time[i])

    return int(wait_sum/len(out_time))

print(solution([[0, 3], [3, 3], [1000, 16], [1002, 14]]), 31)
