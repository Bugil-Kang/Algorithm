def solution(gems):
    answer = []
    reference = {}
    count = 0
    for gem in gems:
        if gem not in reference.keys():
            reference[gem] = count
            count += 1
            
    min_start = 999999
    min_length = 999999
    for i in range(len(gems)-count+1):
        test = [False] * count
        test_count = count
        j = 0
        while(i+j < len(gems) and min_length >= j):
            gem = gems[i+j]
            index = reference[gem]
            if test[index] == False:
                test_count -= 1
                test[index] = True
            
            if test_count == 0:
                if min_length > j:
                    min_start = i
                    min_length = j
                break
            j += 1
                                
    return [min_start+1, min_start+min_length+1]
