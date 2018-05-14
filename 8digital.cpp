#include <iostream>
using namespace std;
#define up 0
#define left 1
#define down 2
#define right 3

int findSmall(int *a) {
	int i;
	int min = a[0];
	int mini = 0;
	for (i = 1; i < 4; i++) {
		if (a[i] < min) {
			min = a[i];
			mini = i;
		}
	}
	return mini;
}

int DirectionReverse(int dir) {
	if (dir = up)
		return down;
	if (dir = down)
		return up;
	if (dir = left)
		return right;
	if (dir = right)
		return left;
}

class chessboard {
public:
	int data[3][3];
	int placeOfSpaceX;
	int placeOfSpaceY;
	int Gn;
	
	chessboard(int gn){
		Gn = gn;
		find_space();
	}

	chessboard() {
		Gn = 0;
		find_space();
	}

	bool exchange(int x1,int y1,int x2,int y2) {
		if (x1 > 2 || y1 > 2 || x2 > 2 || y2 > 2 || x1 < 0 || x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0)
			return false;

		int temp = data[x1][y1];
		data[x1][y1] = data[x2][y2];
		data[x2][y2] = temp;
		find_space();
		return true;
	}

	void input() {
		cout << "输入3x3棋盘，0代表空格" << endl;
		int i, j;
		for (i = 0; i < 3; i++) {
			for (j = 0; j < 3; j++)
				cin >> data[i][j];
		}
	}

	void find_space() {
		int i, j;
		for (i = 0; i < 3; i++) {
			for (j = 0; j < 3; j++)
				if (data[i][j] == 0){
					placeOfSpaceX = i;
					placeOfSpaceY = j;
				}
		}
	}
	
	int Wn() {
		int count = 0;
		int i, j;
		int breakpoint;
		for (i = 0; i < 3; i++) {
			for (j = 0; j < 3; j++)
				if (data[i][j] != i * 3 + j + 1) {
					count++;
				}
				else
					breakpoint = 1;
		}
		return count;
	}

	int Fn() {
		return Wn() + Gn;
	}

	int bestWay() {
		
		chessboard boardtemp = *this;
		//turn up
		int F_up = 1000;
		int F_left = 1000;
		int F_down = 1000;
		int F_right = 1000;

		if (boardtemp.exchange(boardtemp.placeOfSpaceX, boardtemp.placeOfSpaceY, boardtemp.placeOfSpaceX - 1, boardtemp.placeOfSpaceY))
			F_up = boardtemp.Fn();

		boardtemp = *this;
		//turn left
		if (boardtemp.exchange(boardtemp.placeOfSpaceX, boardtemp.placeOfSpaceY, boardtemp.placeOfSpaceX, boardtemp.placeOfSpaceY - 1))
			F_left = boardtemp.Fn();

		boardtemp = *this;
		//turn down
		if (boardtemp.exchange(boardtemp.placeOfSpaceX, boardtemp.placeOfSpaceY, boardtemp.placeOfSpaceX + 1, boardtemp.placeOfSpaceY ))
			F_down = boardtemp.Fn();

		boardtemp = *this;
		//turn right
		if (boardtemp.exchange(boardtemp.placeOfSpaceX, boardtemp.placeOfSpaceY, boardtemp.placeOfSpaceX, boardtemp.placeOfSpaceY + 1))
			F_right = boardtemp.Fn();

		int a[4] = { F_up,F_left,F_down,F_right };
		int s = findSmall(a);

		return s;
	}

	void print() {
		int i, j;
		for (i = 0; i < 3; i++) {
			for (j = 0; j < 3; j++)
				cout << data[i][j] << " ";
			cout << endl;
		}
		cout << endl;
		cout << "Gn=" << Gn << endl;
		cout << "Wn=" << Wn() << endl;
	}
};

void search_bfs(chessboard board,int parent) {
	board.print();
	
	if (board.Wn() == 0) {
		cout << "结束" << endl;
		return;
	}
	chessboard boardtemp = board;
	boardtemp.Gn++;
	switch (boardtemp.bestWay())
	{
	case up:
		if (parent == down)
			break;
		//turn up
		if (boardtemp.exchange(boardtemp.placeOfSpaceX, boardtemp.placeOfSpaceY, boardtemp.placeOfSpaceX - 1, boardtemp.placeOfSpaceY))
			search_bfs(boardtemp,up);
		break;
	case left:
		if (parent == right)
			break;
		//turn left
		if (boardtemp.exchange(boardtemp.placeOfSpaceX, boardtemp.placeOfSpaceY, boardtemp.placeOfSpaceX, boardtemp.placeOfSpaceY - 1))
			search_bfs(boardtemp,left);
		break;
	case down:
		if (parent == up)
			break;
		//turn down
		if (boardtemp.exchange(boardtemp.placeOfSpaceX, boardtemp.placeOfSpaceY, boardtemp.placeOfSpaceX + 1, boardtemp.placeOfSpaceY))
			search_bfs(boardtemp,down);
		break;
	case right:
		if (parent == left)
			break;
		//turn right
		if (boardtemp.exchange(boardtemp.placeOfSpaceX, boardtemp.placeOfSpaceY, boardtemp.placeOfSpaceX, boardtemp.placeOfSpaceY + 1))
			search_bfs(boardtemp,right);

	default:
		break;
	}


}

chessboard originBoard;

int main() {
	chessboard board;
	originBoard.input();
	
	search_bfs(originBoard,-1);


	return 0;
}

