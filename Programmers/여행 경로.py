ticket_dict = {}
answer = []
length = 0


def DFS(depart, used, root, count):
    global answer
    if len(answer) != 0:
        return
    if count == length:
        answer = root
        return

    if depart not in ticket_dict.keys():
        return

    for i in range(len(ticket_dict[depart])):
        info = ticket_dict[depart][i]
        index = info[0]
        arrival = info[1]

        if used[index] == True:
            continue

        DFS(arrival, used[0:index] + [True] + used[index + 1:], root + [arrival], count + 1)

    return


def solution(tickets):
    global length
    length = len(tickets)
    for i in range(len(tickets)):
        ticket = tickets[i]
        if ticket[0] not in ticket_dict.keys():
            ticket_dict[ticket[0]] = [[i, ticket[1]]]
        else:
            ticket_dict[ticket[0]].append([i, ticket[1]])

    for key in ticket_dict.keys():
        ticket_dict[key] = sorted(ticket_dict[key], key=lambda ticket: ticket[1])

    used = [False] * len(tickets)
    DFS("ICN", used, ["ICN"], 0)

    global answer
    return answer
