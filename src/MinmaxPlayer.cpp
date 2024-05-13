#include "./header/MinmaxPlayer.hpp"
#include "./header/FieldType.hpp"
#include "interface/IBoardEvaluator.hpp"
#include <limits>

MinmaxPlayer::MinmaxPlayer(const IBoardEvaluator &boardEvaluator, int depth)
    : depth(depth), boardEvaluator(boardEvaluator) {}

search_result MinmaxPlayer::chooseMove(Halma &game) const {
    search_result minmaxResult = minmax(game, depth, player, boardEvaluator);

    return minmaxResult;
}

search_result
MinmaxPlayer::minmax(Halma &game, int depth, FieldType maximizingPlayer,
                     const IBoardEvaluator &boardEvaluator) const {
    int visitedNodes = 0;
    Board &board = game.getBoard();
    if (depth == 0) {
        return search_result{
            boardEvaluator.evaluateBoard(board, maximizingPlayer),
            piece_move(-1, -1, -1, -1), visitedNodes};
    }

    FieldType currentPlayer = game.getCurrentPlayer();
    bool maximize = currentPlayer == maximizingPlayer;
    float bestEvaluation = maximize ? -numeric_limits<float>::infinity()
                                    : numeric_limits<float>::infinity();
    piece_move bestMove = {-1, -1, -1, -1};
    vector<piece_move> allMoves = board.getPlayerMoves(currentPlayer);

    for (const piece_move &move : allMoves) {
        game.makeMockMove(move);
        search_result childResult =
            minmax(game, depth - 1, maximizingPlayer, boardEvaluator);
        game.undoMockMove(move);

        float evaluation = childResult.evaluation;
        visitedNodes++;
        visitedNodes += childResult.visitedNodes;

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

    return search_result{bestEvaluation, bestMove, visitedNodes};
};
