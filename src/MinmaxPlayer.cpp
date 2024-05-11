#include "MinmaxPlayer.hpp"
#include "FieldType.hpp"
#include "Heuristics.hpp"
#include <limits>

MinmaxPlayer::MinmaxPlayer(int depth, FieldType maximizingPlayer,
                           const HeuristicDistance &distanceFunction)
    : depth(depth), maximizingPlayer(maximizingPlayer),
      distanceFunction(distanceFunction) {}

void MinmaxPlayer::makeMove(Halma &game) {
    pair<float, piece_move> minmaxResult =
        minmax(game, depth, maximizingPlayer, distanceFunction);

    piece_move chosenMove = minmaxResult.second;
    game.makeMove(chosenMove);
}

pair<float, piece_move>
MinmaxPlayer::minmax(Halma &game, int depth, FieldType maximizingPlayer,
                     const HeuristicDistance &distanceFunction) {

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
        float evaluation =
            minmax(game, depth - 1, maximizingPlayer, distanceFunction).first;
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
