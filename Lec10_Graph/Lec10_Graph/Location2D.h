#pragma once
#include <stack>
using namespace std;
struct Location2D
{
	int row;
	int col;
	Location2D(int r = 0, int c = 0) { row = r;
		col = c;
	}
	bool isNeighbor(Location2D& p) {
		return ((row == p.row && (col ==p.col-1) || (col == p.col+1)) 
			|| (col==p.col && (row == p.row - 1 || row==p.row+1)) );
	}
	bool operator==( Location2D& p) {
		return (row == p.row && col == p.col);
	}
};

// 파일 범위의 실행문은 허용되지 않으므로 함수로 감쌈
inline void SampleStacksUsage()
{
	stack<int> intStack; // int 스택 객체 생성
	intStack.push(3); // int 스택에 3을 삽입
	int x = intStack.top(); // 스택 상단 요소를 x에 복사
	intStack.pop(); // 스택 상단 요소를 제거
	stack<Location2D> locSt; // 위치 스택 객체 생성
	locSt.push(Location2D(1, 0)); // 위치(1,0)을 push
	Location2D p = locSt.top(); // 최근 위치 p에 복사
	locSt.pop(); // 최근 위치를 삭제
}