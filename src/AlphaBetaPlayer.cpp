#include "./header/AlphaBetaPlayer.hpp"
#include "./header/Halma.hpp"
#include "./interface/IBoardEvaluator.hpp"
#include <limits>

AlphaBetaPlayer::AlphaBetaPlayer(const IBoardEvaluator &boardEvaluator,
                                 int depth)
    : boardEvaluator(boardEvaluator), depth(depth){};

search_result AlphaBetaPlayer::chooseMove(Halma &game) const {
    search_result result = alphabeta(game, depth, player, boardEvaluator,
                                     -numeric_limits<float>::infinity(),
                                     numeric_limits<float>::infinity());

    return result;
};

search_result AlphaBetaPlayer::alphabeta(
    Halma &game, int depth, FieldType maximizingPlayer,
    const IBoardEvaluator &boardEvaluator,
    float alpha = -numeric_limits<float>::infinity(),
    float beta = numeric_limits<float>::infinity()) const {
    int visitedNodes = 0;

    Board &board = game.getBoard();
    if (depth == 0 || game.checkWinner(maximizingPlayer)) {
        return {boardEvaluator.evaluateBoard(board, maximizingPlayer),
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

        search_result childResult = alphabeta(game, depth - 1, maximizingPlayer,
                                              boardEvaluator, alpha, beta);
        game.undoMockMove(move);
        float evaluation = childResult.evaluation;

        visitedNodes++;
        visitedNodes += childResult.visitedNodes;

        if (maximize) {
            if (evaluation > bestEvaluation) {
                bestEvaluation = evaluation;
                bestMove = move;
            }
            alpha = max(alpha, evaluation);
            if (beta <= alpha) {
                break;
            }
        } else {
            if (evaluation < bestEvaluation) {
                bestEvaluation = evaluation;
                bestMove = move;
            }
            beta = min(beta, evaluation);
            if (beta <= alpha) {
                break;
            }
        }
    }

    return search_result{bestEvaluation, bestMove, visitedNodes};
};
