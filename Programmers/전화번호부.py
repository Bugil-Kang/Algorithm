def solution(phone_book):
    phone_book.sort()
    for i in range(1,len(phone_book)):
        A=len(phone_book[i-1])
        if phone_book[i-1][0:A]==phone_book[i][0:A]:
            return False
    return True
