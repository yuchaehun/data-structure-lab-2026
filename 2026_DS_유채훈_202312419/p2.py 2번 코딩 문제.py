"""
2차원 그리드(Grid) 기반 BFS 탐색 모듈.

이 모듈은 N x M 크기의 콘서트장(2차원 배열) 정보가 주어졌을 때,
'0'으로 표시된 빈 공간들이 상하좌우로 서로 연결되어 이루는 
독립된 '무대 공간(Connected Component)'의 총 개수를 계산합니다.
"""

import sys
from collections import deque

## 입력 받는 코드입니다. 수정할 필요 없습니다.
sys.stdin = open('case.txt') # 테스트 시 주석 해제
N, M = list(map(int, input().split()))
print(N, M)
concerts = []
for v in range(N):
    values = list(map(int, input().split()))
    concerts.append(values)
###################################

def count_stages(concerts):
    """
    주어진 2차원 콘서트장 배열에서 독립된 무대 공간의 개수를 계산합니다.

    이중 반복문을 통해 배열을 순회하며, 방문하지 않은 빈 공간('0')을 발견할 때마다 
    너비 우선 탐색(BFS)을 호출하여 연결된 모든 공간을 방문 처리합니다. 
    BFS가 호출된 횟수가 곧 독립된 무대의 개수가 됩니다.
    """
    answer = 0  # 독립된 무대 공간의 총 개수를 저장하는 변수 (초기값 0)
    
    # 예외 처리: 입력된 콘서트장 배열이 비어있는 경우 바로 answer(0) 반환
    if not concerts:
        return answer

    # 콘서트장의 전체 행(N)과 열(M)의 크기를 구합니다.
    N = len(concerts)    
    M = len(concerts[0]) 
    
    # [설계 포인트 1] 방문 처리 배열 (visited)
    # 한 번 무대로 카운트된 공간('0')을 중복해서 세지 않도록 방문 여부를 기록합니다.
    # N행 M열 크기의 2차원 리스트를 False로 초기화하여 생성합니다.
    visited = [[False] * M for _ in range(N)]
    
    # [설계 포인트 2] 방향 벡터 설정 (Direction Vectors)
    # 현재 좌표를 기준으로 상, 하, 좌, 우 인접한 4개의 칸을 탐색하기 위한 이동 변화량입니다.
    dx = [-1, 1, 0, 0] # x축 변화량 (행 이동: 위, 아래, 변동없음, 변동없음)
    dy = [0, 0, -1, 1] # y축 변화량 (열 이동: 변동없음, 변동없음, 왼쪽, 오른쪽)
    
    def bfs(start_x, start_y):
        """
        특정 좌표에서 시작하여 상하좌우로 연결된 모든 빈 공간('0')을 
        너비 우선 탐색(BFS) 방식으로 찾아 방문(True) 처리합니다.
        """
        # 양방향 입출력이 O(1)로 처리되는 deque를 큐(Queue)로 사용합니다.
        queue = deque([(start_x, start_y)])
        
        # 시작 좌표를 방문했음을 기록합니다.
        visited[start_x][start_y] = True
        
        # 큐에 남은 좌표가 없을 때까지(연결된 모든 빈 공간을 찾을 때까지) 반복합니다.
        while queue:
            # 큐의 맨 앞에서 현재 탐색할 좌표를 꺼냅니다.
            x, y = queue.popleft()
            
            # 현재 좌표를 기준으로 상, 하, 좌, 우 4가지 방향을 모두 확인합니다.
            for i in range(4):
                nx = x + dx[i] 
                ny = y + dy[i] 
                
                # 조건 1: 새로운 좌표가 콘서트장 범위를 벗어나지 않는지 확인
                if 0 <= nx < N and 0 <= ny < M:
                    
                    # 조건 2: 아직 방문한 적이 없고 빈 공간(0)인지 확인
                    if not visited[nx][ny] and concerts[nx][ny] == 0:
                        
                        # 조건을 모두 만족하면 방문 처리 후 큐에 삽입
                        visited[nx][ny] = True  
                        queue.append((nx, ny))  

    # [설계 포인트 3] 전체 배열 순회 및 무대(Component) 카운트
    # 0행 0열부터 순차적으로 하나씩 확인합니다.
    for i in range(N):
        for j in range(M):
            # 아직 방문하지 않은 '0'(빈 공간)을 발견하면 새로운 무대의 시작점입니다.
            if concerts[i][j] == 0 and not visited[i][j]:
                
                # 연결된 모든 빈 공간을 찾아 방문 처리 (무대 1개 완성)
                bfs(i, j)     
                
                # 정답 카운트를 1 증가시킵니다.
                answer += 1   

    # 순회가 모두 끝나면 누적된 총 무대의 개수를 반환합니다.
    return answer

# 결과 출력
print(count_stages(concerts))
