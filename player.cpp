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

	std::cerr<<"Here 1" << std::endl;
	
    if (board->hasMoves(side)) //check and find valid moves for black
    {
		std::cerr<<"Here 2" << std::endl;
        for (int i = 0; i < 8; i++)
        {
			std::cerr<<"Here 3" << std::endl;
            for (int j = 0; j < 8; j++)
            {
				std::cerr<<"Here 4" << std::endl;
                Move testMove(i, j);
                if (board->checkMove(&testMove, side) == true)
                {
					std::cerr<<"Here 5" << std::endl;
                    testMoves.push_back(testMove);
                    std::cerr << "found available move" << testMove.getX() << " " << testMove.getY() << std::endl;
                }
            }
        }
    }
    else
    {
        std::cerr << "no moves available" << std::endl;
    }

    int randomIndex = rand() % testMoves.size();
    Move * moveToPlay = new Move(0,0);
	*moveToPlay = testMoves[randomIndex];
    board->doMove(moveToPlay, side);
    return moveToPlay;
}
