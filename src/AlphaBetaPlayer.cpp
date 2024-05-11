#include "AlphaBetaPlayer.hpp"
#include <limits>

AlphaBetaPlayer::AlphaBetaPlayer(int depth, FieldType maximizingPlayer,
                                 const HeuristicDistance &distanceFunction)
    : depth(depth), maximizingPlayer(maximizingPlayer),
      distanceFunction(distanceFunction){};

void AlphaBetaPlayer::makeMove(Halma &game){};

pair<float, piece_move>
alphabeta(Halma &game, int depth, FieldType maximizingPlayer,
          const HeuristicDistance &distanceFunction,
          float alpha = -numeric_limits<float>::infinity(),
          float beta = numeric_limits<float>::infinity()) {

    Board &board = game.getBoard();
    if (depth == 0) {
        return {evaluateBoardState(board, maximizingPlayer, distanceFunction),
                piece_move(-1, -1, -1, -1)};
    }

    FieldType currentPlayer = game.getCurrentPlayer();
    bool maximize = currentPlayer == maximizingPlayer;
    float bestEvaluation = maximize ? -numeric_limits<float>::infinity()
                                    : numeric_limits<float>::infinity();
    piece_move bestMove = {-1, -1, -1, -1};

    vector<piece_move> allMoves = board.getPlayerMoves(currentPlayer);

    for (piece_move move : allMoves) {
        game.makeMockMove(move);
        float evaluation = alphabeta(game, depth - 1, maximizingPlayer,
                                     distanceFunction, alpha, beta)
                               .first;
        game.undoMockMove(move);

        if (maximize) {
            if (evaluation > bestEvaluation) {
                bestEvaluation = evaluation;
                bestMove = move;
            }
        } else {
            if (evaluation < bestEvaluation) {
                bestEvaluation = evaluation;
                bestMove = move;
            }
        }
    }

    return {bestEvaluation, bestMove};
};