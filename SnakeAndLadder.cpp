#include<bits/stdc++.h>
using namespace std;

class SnakeAndLadder {
public:
    int **grid;	
    int rows = 10;
    int columns = 10;
    SnakeAndLadder(){
        grid = (int**)malloc(sizeof(int*)*rows);
        for(int i = 0 ; i < 10 ; i++){
            grid[i] = (int*)malloc(sizeof(int)*columns);
        }
        for(int i = 0 ; i < 10 ; i++){
            for(int j = 0 ; j < 10 ; j++){
                grid[i][j] = -1;
            }
        }
    }
    void updateGrid(int start,int end);
    static int getRow(int val);
    static int getColumn(int val);
};

class Player{
public:
	int row;
	int column;
	Player(){
		row = 0;
		column = 0;
	}
	void updateRowAndColumn(int dice_throw,int** grid);
	static int getValue(int row_number,int column_number);
	
};

void SnakeAndLadder::updateGrid(int start,int end){
    int row = getRow(start);
    int column = getColumn(start);
    grid[row][column] = end;
}

int SnakeAndLadder::getRow(int val){
    return val / 10;
}

int SnakeAndLadder::getColumn(int val){
    return val % 10;
}

int Player::getValue(int row_number,int column_number){
	return row_number * 10 + column_number;
}

void Player::updateRowAndColumn(int dice_throw,int** grid){
	int current_position = getValue(row,column);
	current_position += dice_throw;
	if(current_position > 99)
		return;
	row = SnakeAndLadder::getRow(current_position);
	column = SnakeAndLadder::getColumn(current_position);
	while(grid[row][column] != -1){
		int x = row,y = column;
		row = SnakeAndLadder::getRow(grid[x][y]);
		column = SnakeAndLadder::getColumn(grid[x][y]);	
	}
}

int main(){
    SnakeAndLadder s1;
    int snake_and_ladders;
    cin >> snake_and_ladders;
    int start,end;
    for(int i = 0 ; i < snake_and_ladders ; i++){
        cin >> start >> end;
        s1.updateGrid(start,end);
    }
	int number_of_moves;
	cin >> number_of_moves;
	Player A,B;
	int dice_throw;
	for(int i = 0 ; i < number_of_moves ; i++){
		cin >> dice_throw;
		if(i % 2){
//			cout << "B moves from " << B.row * 10 + B.column << " ";
			B.updateRowAndColumn(dice_throw,s1.grid);
			int current_position = Player::getValue(B.row,B.column);
//			cout << "to " << current_position << endl;
			if(current_position == 99) break;
		} else {
//			cout << "A moves from " << A.row * 10 + A.column << " ";
			A.updateRowAndColumn(dice_throw,s1.grid);
			int current_position = Player::getValue(A.row,A.column);
//			cout << "to " << current_position << endl;
			if(current_position == 99) break;
		}
	}
	int A_position = Player::getValue(A.row,A.column);
	int B_position = Player::getValue(B.row,B.column);
	if(A_position == B_position){
		cout << "Draw " << A_position << endl;
	} else {
		if(A_position > B_position){
			cout << "A " << A_position << endl;
		} else {
			cout << "B " << B_position << endl;
		}	
	}
}

