Tommy- Created the initial random AI's moves and also the minimax algorithm. Then modified minimax until it worked, also adding some suggestions for the heuristic.

Alex- Created and constantly updated the board heuristic. Also helped debug and change heuristic test values.

To make our AI tourney-worthy we tried improving our heuristic as best we could, changing corner and next-to-corner values based on if those pieces are all controlled by one player or not. Also we tested a lot of different combinations of values until we found one that worked the best for each side (for both white and black). We ran out of time and didn't add any iterative deepening/alpha-beta pruning. 

We tried adding more heuristics to check pieces that were in general harder to flip and give those higher values and also change corner and edge values towards the end game but those were too hard to make perfect and didn't make our AI any better. 

Hopefully our AI does decently but definitely won't be winning anything big!