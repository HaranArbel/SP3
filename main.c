#include "SPFIARGame.h"
#include "SPArrayList.h"
#include "SPFIARParser.h"
#include "SPMainAux.h"
#include "SPMiniMax.h"
#include "SPMiniMaxNode.h"

#include <stdio.h>
#include <stdlib.h>

int main() {

	// Initialization phase
	int difficulty_level = spFiarGameGetDifficultyLevelFromUser();

	// Game phase
	// create an instance of sp_fiar_game_t
	SPFiarGame* game = spFiarGameCreate(2);

	// user turn: print status and then print prompt message
	spFiarGamePrintBoard(game);
			//    user plays one of the 2 options:
			//	  	OR undo previous move (last 2 disks are removed)
			//	  	OR drop a new disk
			//    check if user won: if so, game ends. if not, computer turn
	// computer turn


	// in the end: free memory resources
	spFiarGameDestroy(game);
}
