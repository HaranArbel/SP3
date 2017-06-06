#include "SPFIARGame.h"
#include <stdio.h>

SPFiarGame* spFiarGameCreate(int historySize) {
	if (historySize <= 0) {
		return NULL;
	}
	struct sp_fiar_game_t game; // Declare game of type sp_fiar_game_t
	// game specification
	strcpy(game.currentPlayer, "X");
	char board[SP_FIAR_GAME_N_ROWS][SP_FIAR_GAME_N_COLUMNS] = {
			{' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' '}
	};
	game.gameBoard = board;
	char row7[SP_FIAR_GAME_FULL_ROW_LENGTH];
	for (int i = 0; i < SP_FIAR_GAME_FULL_ROW_LENGTH; ++i) {
		row7[i] = '-';
	}
	game.row7 = row7;
	char row8[SP_FIAR_GAME_FULL_ROW_LENGTH] = {' ', ' ', '1', ' ', '2', ' ', '3', ' ', '4', ' ', '5', ' ', '6', ' ', '7', ' ', ' '};
	game.row8 = row8;
	int tops[SP_FIAR_GAME_N_COLUMNS] = {6, 6, 6, 6, 6, 6, 6};
	game.tops = tops;
	SPFiarGame previousGames[historySize];
	game.previousGames = previousGames;
	int lastMoves[historySize][2]; // PROBLEM: MAYBE INITIATE TO ZEROS, BUT WE NEED NULLS
	game.lastMoves = lastMoves;
	return game;
}

SP_FIAR_GAME_MESSAGE spFiarGamePrintBoard(SPFiarGame* src) {
	if (src == NULL) {
		return SP_FIAR_GAME_INVALID_ARGUMENT;
	}
	// print the game board
	for (int i = 0; i < SP_FIAR_GAME_N_ROWS; i++) {
		for (int j = 0; j < SP_FIAR_GAME_N_COLUMNS; j++) {
			printf(src->gameBoard[i][j]);
		}
	}
	for (int i = 0; i < SP_FIAR_GAME_FULL_ROW_LENGTH; i++) {
		printf(src->row7[i]);
	}
	for (int i = 0; i < SP_FIAR_GAME_FULL_ROW_LENGTH; i++) {
		printf(src->row8[i]);
	}
	return SP_FIAR_GAME_SUCCESS;
}

char spFiarGameGetCurrentPlayer(SPFiarGame* src) {
	return src->currentPlayer;
}

SP_FIAR_GAME_MESSAGE spFiarGameSetMove(SPFiarGame* src, int col) {
	// TO DO: first need to make a copy of the current game, to save for possible undo moves
	if (src == NULL || col < 0 || col > SP_FIAR_GAME_N_COLUMNS - 1) {
		return SP_FIAR_GAME_INVALID_ARGUMENT;
	}
	bool validMove = spFiarGameIsValidMove(src, col);
	if (validMove == false) {
		return SP_FIAR_GAME_INVALID_MOVE;
	}
	src.tops[col] -= 1;
	// also need to update the board
	// which row to update:
	int rowNumber = src.tops[col];
	char currentPlayer = spFiarGameGetCurrentPlayer(src);
	src.gameBoard[rowNumber][col] = currentPlayer;
	return SP_FIAR_GAME_SUCCESS;
}

bool spFiarGameIsValidMove(SPFiarGame* src, int col) {
	if (src->tops[col] > 0) {
		return true;
	} else {
		return false;
	}
}

SPFiarGame* spFiarGameCopy(SPFiarGame* src) {
	SPFiarGame copy = src;
	return copy;
}

// SP_FIAR_GAME_MESSAGE spFiarGameUndoPrevMove(SPFiarGame* src)

char spFiarCheckWinner(SPFiarGame* src) {
	char board[][] = src->gameBoard;
	int lastDiskColumn = src->lastMoves[0][0];
	int lastDiskRow = src->lastMoves[0][1];
	char player = board[lastDiskRow][lastDiskColumn];

	// check if there are 4 in a row vertically
	if(lastDiskRow <= 2
			&& board[lastDiskRow+1][lastDiskColumn] == player
			&& board[lastDiskRow+2][lastDiskColumn] == player
			&& board[lastDiskRow+3][lastDiskColumn] == player) {
		return player;
	}
	else {
		int count = 1, i, j;
		// check if there are 4 in a row horizontally to the right
		for(i = lastDiskColumn + 1; i < SP_FIAR_GAME_N_COLUMNS; i++) {
			if(board[lastDiskRow][i] != player) {
				break;
			}
			count++;
		}
		// check if there are 4 in a row horizontally to the left
		for(i = lastDiskColumn - 1; i >= 0; i--) {
			if(board[lastDiskRow][i] != player) {
				break;
			}
			count++;
		}
		if(count >= 4) {
			return player;
		}
		/* check if there are 4 in a row diagonally, this way: \ */
		count = 1;
		for(i = lastDiskColumn + 1, j = lastDiskRow + 1;
				i < SP_FIAR_GAME_N_COLUMNS && j < SP_FIAR_GAME_N_ROWS; i++, j++) {
			if(board[j][i] != player) {
				break;
			}
			count++;
		}
		for(i = lastDiskColumn - 1, j = lastDiskRow - 1; i >= 0 && j >= 0; i--, j--) {
			if(board[j][i] != player) {
				break;
			}
			count++;
		}
		if(count >= 4) {
			return player;
		}
		/* check if there are 4 in a row diagonally, this way: / */
		count = 1;
		for(i = lastDiskColumn + 1,j = lastDiskRow - 1; i < SP_FIAR_GAME_N_COLUMNS && j >= 0; i++, j--) {
			if(board[j][i] != player) {
				break;
			}
			count++;
		}
		for(i = lastDiskColumn - 1, j = lastDiskRow + 1; i >= 0 && j < SP_FIAR_GAME_N_ROWS; i--, j++) {
			if(board[j][i] != player) {
				break;
			}
			count++;
		}
		if(count >= 4) {
			return player;
		}
	}
	// check if all columns are full then return the SP_FIAR_GAME_TIE_SYMBOL which is: '-'
	if (spFiarBoardIsFull(SPFiarGame* src) == 1) {
		return SP_FIAR_GAME_TIE_SYMBOL;
	}
	return NULL;
}

bool spFiarBoardIsFull(SPFiarGame* src) {
	for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++) {
		if (src->tops[i] != 0) {
			return false;
		}
	}
	return true;
}

void spFiarGameDestroy(SPFiarGame* src) {
	if (src != NULL) {
		free(src);
	}
}

