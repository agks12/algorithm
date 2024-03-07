# import sys
# from heapq import heappush, heappop
#
# class Node:
#     def __init__(self, _from, _to, cost):
#         self.from_ = _from
#         self.to = _to
#         self.cost = cost
#
#     def __lt__(self, other):
#         if self.cost > other.cost:
#             return True
#         if self.cost < other.cost:
#             return False
#         return False
#
# def Find(num):
#     if num == parent[num]:
#         return num
#     parent[num] = Find(parent[num])
#     return parent[num]
#
# def Union(a, b):
#     rootA = Find(a)
#     rootB = Find(b)
#     if rootA == rootB:
#         return
#     parent[rootA] = rootB
#
# def input_data():
#     n = int(input())
#     Min = sys.maxsize
#     for i in range(n):
#         parent[i] = i
#         visited[i] = 0
#         v[i].clear()
#         row = list(map(int, input().split()))
#         for j in range(n):
#             arr[i][j] = row[j]
#             dist[i][j] = 21e8
#     for i in range(n):
#         for j in range(n):
#             if i == j:
#                 continue
#             v[i].append(Node(i, j, arr[i][j]))
#
# def sol(now, level):
#     global sum, Min
#     if now == 0 and level == n:
#         if sum < Min:
#             Min = sum
#         return
#     if level > n:
#         return
#     for i in range(len(v[now])):
#         next_ = v[now][i].to
#         if visited[next_] == 1:
#             continue
#         visited[next_] = 1
#         if level == 0 and next_ == 0:
#             visited[next_] = 0
#         sum += arr[now][next_]
#         sol(next_, level+1)
#         sum -= arr[now][next_]
#         visited[next_] = 0
#
# tc = int(input())
# for i in range(1, tc+1):
#     n = 0
#     arr = [[0] * 11 for _ in range(11)]
#     dist = [[0] * 11 for _ in range(11)]
#     visited = [0] * 11
#     parent = [0] * 11
#     v = [[] for _ in range(11)]
#     input_data()
#     sum = 0
#     Min = sys.maxsize
#     sol(0, 0)
#     print("#{} {}".format(i, Min))

visited1 = []
visited2 = []
tc = int(input())

def inval():
    global arr
    arr = list(map(int, input().split()))  # 입력 : 1 2 3 /출력 : [1, 2, 3]


def sol():
    global arr
    #print("arr",arr)
    now_list1 = []
    now_list2 = []
    print(now_list1, arr)

    for i in range(10):
        visited1[i] = 0
        visited2[i] = 0
    print(visited1, visited2)
    nowindex = -1
    for i in range(12):
        if(i%2==0):
            nowindex +=1
            now_list1.append(arr[i])
            visited1[arr[i]]+=1
            if(i>6):
                if(now_list1[nowindex-2] + 1 == now_list1[nowindex-1] and now_list1[nowindex-1] + 1 == now_list1[nowindex]):
                    print(1)
                    return
            if(visited1[arr[i]]>=3):
                print(1)
                return
        if(i%2==1):
            now_list2.append(arr[i])
            visited2[arr[i]]+=1
            if(i>6):
                if(now_list2[nowindex-2] + 1 == now_list2[nowindex-1] and now_list2[nowindex-1] + 1 == now_list2[nowindex]):
                    print(2)
                    return
            if(visited2[arr[i]]>=3):
                print(2)
                return
    print(0)
    return

for i in range(10):
    visited1.append(0)
    visited2.append(0)
    #print(visited1[i])
for i in range(1,tc+1):
    arr = []
    inval()
    print("#%d"%i,end=' ')
    sol()
