#include "./header/MinmaxPlayer.hpp"
#include "./header/FieldType.hpp"
#include "./header/Heuristics.hpp"
#include "interface/BoardEvaluator.hpp"
#include <limits>

MinmaxPlayer::MinmaxPlayer(const BoardEvaluator &boardEvaluator, int depth,
                           FieldType maximizingPlayer)
    : depth(depth), maximizingPlayer(maximizingPlayer),
      boardEvaluator(boardEvaluator) {}

void MinmaxPlayer::makeMove(Halma &game) {
    pair<float, piece_move> minmaxResult =
        minmax(game, depth, maximizingPlayer, boardEvaluator);

    piece_move chosenMove = minmaxResult.second;
    game.makeMove(chosenMove);
}

pair<float, piece_move>
MinmaxPlayer::minmax(Halma &game, int depth, FieldType maximizingPlayer,
                     const BoardEvaluator &boardEvaluator) {
    Board &board = game.getBoard();
    if (depth == 0) {
        return {boardEvaluator.evaluateBoard(board, maximizingPlayer),
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
            minmax(game, depth - 1, maximizingPlayer, boardEvaluator).first;
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
