#include "SPFIARGame.h"
#include "SPArrayList.h"
#include "SPFIARParser.h"
#include "SPMainAux.h"
#include "SPMiniMax.h"
#include "SPMiniMaxNode.h"

#include <stdio.h>
#include <stdlib.h>

int spMinimaxSuggestMove(SPFiarGame* currentGame, unsigned int maxDepth) {
	int currentDepth = 0;
	if (currentDepth < maxDepth) {

	}

}

/*
 * this is the minmax algorithm
class Tree {
    public int value;
    Board[][] Boards; // this is the board
    private ArrayList<Integer> bestMoves;
    Board prev = null;
    int depth;
    static int maxDepth = 4;  // this is the max depth im going down

    public Tree(Board[][] Boards, int depth) {
        this.Boards = Boards;
        this.bestMoves = new ArrayList<Integer>();
        this.depth = depth;
        this.value = getValue();

        if(depth < maxDepth && this.value < 100 && this.value > -100 ) {
            ArrayList<Integer> possibilities = new ArrayList<Integer>();
            for(int i = 0; i < 7; i++)
                if(Boards[i][0].piece == Piece.None)
                    possibilities.add(i);

            for(int i = 0; i < possibilities.size(); i++) {
                insertTo(Boards[possibilities.get(i)][0]);
                Tree child = new Tree(Boards, depth+1);
                prev.setPiece(Piece.None);

                if(i == 0) {
                    bestMoves.add(possibilities.get(i));
                    value = child.value;
                }
                else if(depth % 2 == 0) {
                    if(value < child.value) {
                        bestMoves.clear();
                        bestMoves.add(possibilities.get(i));
                        this.value = child.value;
                    }
                    else if(value == child.value)
                        bestMoves.add(possibilities.get(i));
                }
                else if(depth % 2 == 1) {
                    if(value > child.value) {
                        bestMoves.clear();
                        bestMoves.add(possibilities.get(i));
                        this.value = child.value;
                    }
                    else if(value == child.value)
                        bestMoves.add(possibilities.get(i));
                }
            }
        }
        else {
            this.value = getValue();
        }
    }
*/
