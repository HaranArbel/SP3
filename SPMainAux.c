#include <stdio.h>
#include "SPMainAux.h"

int spFiarGameGetDifficultyLevelFromUser() {
	int difficulty_level;
	do {
		printf("Please enter the difficulty level between [1-7]:\n");
		scanf("%d",&difficulty_level);
		if (difficulty_level < 1 || difficulty_level > 7) {
			printf("Error: invalid level (should be between 1 to 7\n");
		}
	} while (difficulty_level < 1 || difficulty_level > 7);
	return difficulty_level;
}
