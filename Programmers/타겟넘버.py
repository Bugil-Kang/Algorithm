def dist(num1, num2):
    if num1 > num2:
        return num1 - num2
    else:
        return num2 - num1


def solution(numbers, target):
    answer = 0
    current = 0
    queue = []
    queue.append([0, 0])
    length = len(numbers)

    for number in numbers:
        while (len(queue) != 0 and queue[0][1] == current):
            queue_list = queue.pop(0)
            new_list1 = [queue_list[0] + number, queue_list[1] + 1]
            new_list2 = [queue_list[0] - number, queue_list[1] + 1]
            if new_list1[1] == len(numbers) - 1:
                if dist(new_list1[0], target) == numbers[length - 1]:
                    answer += 1
                if dist(new_list2[0], target) == numbers[length - 1]:
                    answer += 1
            else:
                queue.append(new_list1)
                queue.append(new_list2)

        current += 1

    return answer
