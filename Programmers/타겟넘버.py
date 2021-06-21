def solution(numbers, target):
    answer = 0
    length = len(numbers)  ## List 길이 구함
    twice = [1]
    for idx in range(length+1):
        twice.append(twice[idx]*2)

    num_list = [0, 0]
    for idx in range(length):
        number = numbers[idx]
        for bin in range(twice[idx],twice[idx+1]):
            num_list.append(num_list[bin]-number)
            num_list.append(num_list[bin]+number)

    for idx in range(twice[length], twice[length+1]):
        if num_list[idx] == target:
            answer += 1

    return answer
