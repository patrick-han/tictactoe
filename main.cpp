#include <iostream>
#include <limits>


void checkInput();
void updateBoard();
void renderBoard();
bool checkGameStatus();


bool playerWon = false;
bool canMark = true;

int numMoves = 0;
int playerTurn = 1;
int input;
char board[] = {'1', '2', '3', 
				'4', '5', '6', 
				'7', '8', '9'};


							   // d1
int checkBoard[] = {0, 0, 0,   // r1
					0, 0, 0,   // r2
					0, 0, 0,}; // r3
				  //c1 c2 c3 d2

int r1, r2, r3;
int c1, c2, c3;
int d1, d2;




int main() {
	std::cout << "\033[2J\033[1;1H"; // Refer to below
	std::cout << "Waiting for initial player input..." << std::endl;

	renderBoard(); // Initial render of the board to display square numbers

	while (!playerWon) {
		
		// Prompt player 1 or 2 to enter the number (1-9) corresponding to the square they want to place their mark
		std::cout << "Player " << playerTurn << (playerTurn == 1 ? " (X)" : " (O)") << " please enter the square you want to mark: ";
		std::cin >> input;
		checkInput(); // Ensure valid input
		std::cout << "\033[2J\033[1;1H";  // Black magic that clears the terminal output each time so it doesn't get too messy
		std::cout << "Player " << playerTurn << (playerTurn == 1 ? " (X)" : " (O)") << " entered on square " << input << "!" << std::endl;
		updateBoard(); // Update board rendering

		numMoves++;

		

		renderBoard(); // Show current board state


		// Update which player's turn it is
		if (playerTurn == 1) {
			playerTurn++;
		}
		else {
			playerTurn--;
		}


		playerWon = checkGameStatus(); // Change game state if stalemate/win, set as true even in the case of stalemate


	}

	return 0;
}





void checkInput() { // Checks for valid player input
	// Check to make sure the player doesn't try to overwrite another player's square


	while (1) {
		if (checkBoard[input-1] != 0) { // If the square is already marked
			canMark = false;
		}
		else if ( std::cin.fail() || (input > 9) || (input < 1) ){ // If input is invalid
			canMark = false;
		}
		else {
			canMark = true;
		}

		// std::cout << canMark << std::endl;

		if ( std::cin.fail() || (input  > 9) || (input < 1) || (!canMark) ) { 	// If input failure occurs
			std::cin.clear(); 	// Clear error state of the buffer

			// Function is used to ignore the rest of the line after the first instance of error that has occurred and it skips to or moves to the next line.
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
			std::cout << "Invalid input! (Enter 1-9 on a square not yet marked): " << std::endl;
			std::cin >> input;
		}

		if ( !std::cin.fail() && (input  <= 9) && (input >= 1) && canMark)    // If input fail does not occur
			break;
	}
}


void updateBoard() { // Mark the board
	if (playerTurn == 1) { // If player 1's input
		board[input - 1] = 'X';
		checkBoard[input-1] = -1;
	}
	else {
		board[input - 1] = 'O';
		checkBoard[input - 1] = 1;
	}

}


void renderBoard() { // Renders current board state
	std::cout << " " << board[0] << "  | " << " " << board[1] << " " << " | " << " " << board[2] << std::endl;

	std::cout << "---" << " | " << "---"  << " | " << "---" << std::endl;

	std::cout << " " << board[3] << "  | " << " " << board[4] << " " << " | " << " " << board[5] << std::endl;

	std::cout << "---" << " | " << "---"  << " | " << "---" << std::endl;

	std::cout << " " << board[6] << "  | " << " " << board[7] << " " << " | " << " " << board[8] << std::endl;
}

bool checkGameStatus() {
	// Method of checking for a win: Check sums of rows, cols, diagonals for 3 or -3 (O or X)


	// Check col, row, diagonal sums
	r1 = checkBoard[0] + checkBoard[1] + checkBoard[2];
	r2 = checkBoard[3] + checkBoard[4] + checkBoard[5];
	r3 = checkBoard[6] + checkBoard[7] + checkBoard[8];

	c1 = checkBoard[0] + checkBoard[3] + checkBoard[6];
	c2 = checkBoard[1] + checkBoard[4] + checkBoard[7];
	c3 = checkBoard[2] + checkBoard[5] + checkBoard[8];

	d1 = checkBoard[6] + checkBoard[4] + checkBoard[2];
	d2 = checkBoard[0] + checkBoard[4] + checkBoard[8];

	if ( (numMoves == 9) && (playerWon == false) ) { // Check for a stalemate (can only happen on move 9)
		std::cout << "Stalemate!" << std::endl;
		return true;
	}
	else { // Check for a win
		if (r1 == 3 || r2 == 3 || r3 == 3 || c1 == 3 || c2 == 3 || c3 == 3 || d1 == 3 || d2 == 3) {
			std::cout << "Player 2 (O) won!" << std::endl;
			return true;
		}
		else if (r1 == -3 || r2 == -3 || r3 == -3 || c1 == -3 || c2 == -3 || c3 == -3 || d1 == -3 || d2 == -3) {
			std::cout << "Player 1 (X) won!" << std::endl;
			return true;
		}
		else {
			return false;
		}


	}


}




