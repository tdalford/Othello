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

vector<Move> Player::possibleMoves(Side player, Board* currBoard)
{
    vector<Move> possibles;
    if (currBoard->hasMoves(player)) //check and find valid moves for black
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                Move testMove(i, j);
                if (currBoard->checkMove(&testMove, player) == true)
                {
                    possibles.push_back(testMove);
                }
            }
        }
    }
    else
    {
        return possibles;
    }

    return possibles;
}

int Player::minimax(int depth, Side player, Board* currBoard)
{
    //int numWhite = currBoard->countWhite();
    //int numBlack = currBoard->countBlack();
    // cerr << "num Black = " << numBlack << endl;
    // cerr << "num White = " << numWhite << endl;
    Side oppPlayer;
    if (player == BLACK)
    {
        oppPlayer = WHITE;
    }
    else
    {
        oppPlayer = BLACK;
    }
    if (depth == 0)
    {
        //evaluate board for given player
		int cornWeight = 6;
		int nxtCornWeight = 15;
		int edgeWeight = 2;
        return board->evalBoard(edgeWeight, nxtCornWeight, cornWeight, side);
    }

    Move * testMove = new Move(0,0);
    int bestScore;
    vector<Move> possibles = possibleMoves(oppPlayer, currBoard);
    if (possibles.size() == 0)
    {
        //have to pass
        int score = minimax(depth - 1, oppPlayer, currBoard);
        if (player == side) //maximise
        {
            bestScore = -1e8;
            if (score > bestScore)
            {
                bestScore = score;
            }
        }
        else //minimise
        {   
            bestScore = 1e8;
            if (score < bestScore)
            {
                bestScore = score;
            }
        }
    }

    for (unsigned int i = 0; i < possibles.size(); i++)
    {
        Board * boardCopy = new Board();
        boardCopy = currBoard->copy();
        *testMove = possibles[i];
        boardCopy->doMove(testMove, oppPlayer);
        int score = minimax(depth - 1, oppPlayer, boardCopy);
        if (player == side) //maximise
        {
            bestScore = -1e8;
            if (score > bestScore)
            {
                bestScore = score;
            }
        }
        else //minimise
        {   
            bestScore = 1e8;
            if (score < bestScore)
            {
                bestScore = score;
            }
        }
        delete boardCopy;
    }
    //cout << "bestScore = " << bestScore << endl;
    return bestScore;

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

    board->doMove(opponentsMove, oppSide);
    vector<Move> testMoves;
    //vector<Move> badMoves;
    Move * moveToPlay = new Move(0, 0);
    Move * testMove = new Move(0, 0);
    int depth;
    if (testingMinimax)
    {   
        depth = 1;
    }
    else
    {
        depth = 3;
    }

    int bestScore = 100;
    vector<Move> possibles = possibleMoves(side, board);
    for (unsigned int i = 0; i < possibles.size(); i++)
    {
        Board* boardCopy = new Board();
        boardCopy = board->copy();
        *testMove = possibles[i];
        boardCopy->doMove(testMove, side);
        //cerr << "current test " << testMove->getX() << " " << testMove->getY() << endl;
        int score = minimax(depth, side, boardCopy);
        //cerr << "score = " << score << endl;
        if (score < bestScore)
        {
            bestScore = score;
            *moveToPlay = possibles[i];
        }
        delete boardCopy;
    }


    if (possibles.size() == 0)
    {
        return nullptr;
    }

    board->doMove(moveToPlay, side);
    return moveToPlay;
	
    // if (board->hasMoves(side)) //check and find valid moves for black
    // {
    //     for (int i = 0; i < 8; i++)
    //     {
    //         for (int j = 0; j < 8; j++)
    //         {
    //             Move testMove(i, j);
    //             if (board->checkMove(&testMove, side) == true)
    //             {
    //                 //check and see if move is a corner (coordinates mod 7 == 0)
    //                 if (i % 7 == 0 && j % 7 == 0)
    //                 {
    //                     *moveToPlay = testMove;
    //                     board->doMove(moveToPlay, side);
    //                     return moveToPlay;
    //                 }

    //                 //check and see if edge next to corner; if it is, prioritize against
    //                 if ((i == 0 && j == 1)
    //                     ||  (i == 0 && j == 6)
    //                     ||  (i == 1 && j == 7)
    //                     ||  (i == 6 && j == 1)
    //                     ||  (i == 7 && j == 6)
    //                     ||  (i == 7 && j == 1)
    //                     ||  (i == 6 && j == 0)
    //                     ||  (i == 1 && j == 0)
    //                     ||  (i == 1 && j == 1)
    //                     ||  (i == 1 && j == 6)
    //                     ||  (i == 6 && j == 1)
    //                     ||  (i == 6 && j == 6))
    //                 {
    //                     badMoves.push_back(testMove);
    //                 }

    //                 else
    //                 { 
    //                     testMoves.push_back(testMove);
    //                 }
    //             }
    //         }
    //     }
    // }
    // else
    // {
    //     return nullptr;
    // }

    // for (unsigned int i = 0; i < testMoves.size(); i++)
    // {
    //     //prioritize edges still
    //     if (testMoves[i].getX() % 7 == 0 || testMoves[i].getY() % 7 == 0)
    //     {
    //         *moveToPlay = testMoves[i];
    //         board->doMove(moveToPlay, side);
    //         return moveToPlay;
    //     }
    // }
    // if (testMoves.size() == 0)
    // {
    //     int randomIndex = rand() % badMoves.size();
    //     *moveToPlay = badMoves[randomIndex];
    // }

    // else
    // {
    //     int randomIndex = rand() % testMoves.size();
    // 	   *moveToPlay = testMoves[randomIndex];
    // }

    // board->doMove(moveToPlay, side);
    // return moveToPlay;
}
