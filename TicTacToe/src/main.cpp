#include <iostream>

class Board {
private:
	char grid[3][3] = { {'.','.','.'},{'.','.','.'},{'.','.','.'} };


public:
	Board() {}
	~Board() {}
	bool GoodMove(int row, int col) {
		return (grid[row - 1][col - 1] == '.')? true : false;
	}

	void SetMoveinGrid(int row, int col, char turn) {
		grid[row-1][col-1] = turn;
	}

	void PrintGrid() {
		for (int i = 0; i < sizeof(grid) / sizeof(grid[0]); i++)
		{
			for (int j = 0; j < sizeof(grid[i]) / sizeof(grid[i][0]); j++)
			{
				std::cout << grid[i][j];
			}
			std::cout << std::endl;
		}
	}

	// To Do: Flesh out checking win status
	bool IsInWinState() {
		// Check Rows
		for (int i = 0; i < sizeof(grid) / sizeof(grid[0]); i++)
		{
			if ((grid[i][0] == 'X') && (grid[i][1] == 'X') && (grid[i][2] == 'X'))
				return true;
			else if ((grid[i][0] == 'O') && (grid[i][1] == 'O') && (grid[i][2] == 'O'))
				return true;
		}
		// Check Columns
		for (int i = 0; i < sizeof(grid) / sizeof(grid[0]); i++)
		{
			if ((grid[0][i] == 'X') && (grid[1][i] == 'X') && (grid[2][i] == 'X'))
				return true;
			else if ((grid[0][i] == 'O') && (grid[1][i] == 'O') && (grid[2][i] == 'O'))
				return true;
		}
		// Check Diagonals
		if ((grid[0][0] == 'X') && (grid[1][1] == 'X') && (grid[2][2] == 'X'))
			return true;
		else if ((grid[0][0] == 'O') && (grid[1][1] == 'O') && (grid[2][2] == 'O'))
			return true;
		else if ((grid[2][0] == 'X') && (grid[1][1] == 'X') && (grid[0][2] == 'X'))
			return true;
		else if ((grid[2][0] == 'O') && (grid[1][1] == 'O') && (grid[0][2] == 'O'))
			return true;
		else 
			return false;
	}

	void ResetBoard() {
		for (int i = 0; i < sizeof(grid) / sizeof(grid[0]); i++)
		{
			for (int j = 0; j < sizeof(grid[i]) / sizeof(grid[i][0]); j++)
			{
				grid[i][j] = '.';
			}
		}
	}
};

class Game {
private: 
	int round;
	int xScore;
	int oScore;
	bool gameOver;
	char turn;
	Board board;

	void SwapPlayer() {
		turn = (turn == 'X') ? 'O' : 'X';
	}

public:
	Game()
		:round(0), xScore(0), oScore(0), gameOver(false), turn('X')
	{
	}
	~Game(){}
	int GetRound() { return round; }
	int GetXScore() { return xScore; }
	int GetOScore() { return oScore; }
	int GameOver() { return gameOver; }


	// TO DO: verify input from user
	void MakeMove() {
		char move[4];
		std::cout << "Enter a move in row,col format: ";
		std::cin.getline(move,4);
		std::cout << std::endl;
		if (board.GoodMove((int)move[0] - '0', (int)move[2] - '0')) {
			board.SetMoveinGrid((int)move[0] - '0', (int)move[2] - '0', turn);
			SwapPlayer();
		}
		else {
			std::cout << "Not a valid move" << std::endl;
		}
		round++;
	}

	void PrintState() {
		board.PrintGrid();
	}

	void CheckForWin() {
		if (board.IsInWinState()) {
			gameOver = true;
			SwapPlayer();
			std::cout << turn << " Wins!" << std::endl;
			(turn == 'X') ? xScore++ : oScore++;
		}
		
	}

	void ResetGame() {
		gameOver = false;
		board.ResetBoard();
	}

};

int main() {

	Game* game = new Game;

 	while (!game->GameOver()) {
		game->MakeMove();
		game->PrintState();
		game->CheckForWin();

		if (game->GameOver()) {
			std::cout << "O Score: " << game->GetOScore() << " | X Score: " << game->GetXScore() << std::endl;
			std::cout << "Play again? Y or N" << std::endl;
			char playAgain[2];
			std::cin.getline(playAgain, 2);
			if (playAgain[0] == 'Y') game->ResetGame();
		}

	}
}