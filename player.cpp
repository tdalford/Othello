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

    Board board = Board();
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
    board.doMove(opponentsMove, oppSide);
    cout << "made opponent's move" << endl;
    vector<Move> testMoves;

    if (board.hasMoves(side)) //check and find valid moves for black
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                Move testMove(i, j);
                if (board.checkMove(&testMove, side) == true)
                {
                    testMoves.push_back(testMove);
                }
            }
        }
    }

    int randomIndex = rand() % testMoves.size();
    Move moveToPlay = testMoves[randomIndex];
    return &moveToPlay;
}
