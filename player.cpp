#include "player.hpp"
#include <vector>


/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */

    board = new Board();
    this->side = side;
    if (side == BLACK)
    {
        oppSide = WHITE;
    }
    else
    {
        oppSide = BLACK;
    }
}

/*
 * Destructor for the player.
 */
Player::~Player() {
    delete board;

}

Move * Player::minimax(int node, int depth, side player, bool isMaximising)
{

}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
    board->doMove(opponentsMove, oppSide);
    vector<Move> testMoves;
    vector<Move> badMoves;
    Move * moveToPlay = new Move(0,0);
	
    if (board->hasMoves(side)) //check and find valid moves for black
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                Move testMove(i, j);
                if (board->checkMove(&testMove, side) == true)
                {
                    //check and see if move is a corner (coordinates mod 7 == 0)
                    if (i % 7 == 0 && j % 7 == 0)
                    {
                        *moveToPlay = testMove;
                        board->doMove(moveToPlay, side);
                        return moveToPlay;
                    }

                    //check and see if edge next to corner; if it is, prioritize against
                    if ((i == 0 && j == 1)
                        ||  (i == 0 && j == 6)
                        ||  (i == 1 && j == 7)
                        ||  (i == 6 && j == 1)
                        ||  (i == 7 && j == 6)
                        ||  (i == 7 && j == 1)
                        ||  (i == 6 && j == 0)
                        ||  (i == 1 && j == 0)
                        ||  (i == 1 && j == 1)
                        ||  (i == 1 && j == 6)
                        ||  (i == 6 && j == 1)
                        ||  (i == 6 && j == 6))
                    {
                        badMoves.push_back(testMove);
                    }

                    else
                    { 
                        testMoves.push_back(testMove);
                    }
                }
            }
        }
    }
    else
    {
        return nullptr;
    }

    for (unsigned int i = 0; i < testMoves.size(); i++)
    {
        //prioritize edges still
        if (testMoves[i].getX() % 7 == 0 || testMoves[i].getY() % 7 == 0)
        {
            *moveToPlay = testMoves[i];
            board->doMove(moveToPlay, side);
            return moveToPlay;
        }
    }
    if (testMoves.size() == 0)
    {
        int randomIndex = rand() % badMoves.size();
        *moveToPlay = badMoves[randomIndex];
    }

    else
    {
        int randomIndex = rand() % testMoves.size();
    	*moveToPlay = testMoves[randomIndex];
    }

    board->doMove(moveToPlay, side);
    return moveToPlay;
}
