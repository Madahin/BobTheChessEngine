//
// Created by madahin on 17/02/23.
//
#include "Move.h"

std::array<std::array<uint8_t, 8>, Board::NUM_CASE> Move::sm_numSquareToEdge{};

auto Move::Init() -> void
{
    Log::Info("Initializing the move module");
    GenerateMoveData();
}

MoveList_t Move::GenerateMoveFromBoardForDepth(const Board &board, const uint64_t depth)
{
    MoveList_t moves = std::make_shared<std::vector<Move_t>>();
    std::stack<Board> boardStack;
    uint64_t currentDepth = 0;

    Log::Debug("Generate Moves for {} until depth {}", ((board.GetColorToMove() == Piece::White) ? "white" : "black"), depth);

    boardStack.push(board);

    while(currentDepth < depth)
    {
        std::stack<Board> futurStack;
        moves->clear();
        while (!boardStack.empty())
        {
            Board currentBoard = boardStack.top();
            boardStack.pop();
            MoveList_t newMoves = GenerateMoveFromBoard(currentBoard);

            for (const auto &move: *newMoves)
            {
                Board newBoard(currentBoard);
                newBoard.ApplyMove(move);
                futurStack.push(newBoard);
            }

            moves->reserve(moves->size() + newMoves->size());
            moves->insert(moves->begin(), newMoves->begin(), newMoves->end());
        }
        while (!futurStack.empty())
        {
            boardStack.push(futurStack.top());
            futurStack.pop();
        }

        currentDepth += 1;
    }

    return moves;
}

MoveList_t Move::GenerateMoveFromBoard(const Board &board)
{
    MoveList_t moves = std::make_shared<std::vector<Move_t>>();

    for (const auto& piece : board.GetPieces())
    {
        if (Piece::CompareColor(piece, board.GetColorToMove()))
        {
            MoveList_t newMoves;
            if (Piece::IsSliding(piece))
            {
                newMoves = GenerateSlidingMoves(board, piece, Piece::GetCoordinate(piece));
            }
            else if (Piece::CompareKind(piece, Piece::Knight))
            {
                newMoves = GenerateKnightMoves(board, piece, Piece::GetCoordinate(piece));
            }
            else if (Piece::CompareKind(piece, Piece::Pawn))
            {
                newMoves = GeneratePawnMoves(board, piece, Piece::GetCoordinate(piece));
            }
            else if (Piece::CompareKind(piece, Piece::King))
            {
                newMoves = GenerateKingMoves(board, piece, Piece::GetCoordinate(piece));
            }

            if (newMoves)
            {
                moves->reserve(moves->size() + newMoves->size());
                moves->insert(moves->begin(), newMoves->begin(), newMoves->end());
            }
        }
    }

    return moves;
}

auto Move::GenerateSlidingMoves(const Board &board, const Piece_t piece, const uint8_t square) -> MoveList_t
{
    MoveList_t moves = std::make_shared<std::vector<Move_t>>();
    const uint8_t firstDirectionIndex = ((Piece::GetKind(piece) == Piece::Bishop) ? 4 : 0);
    const uint8_t lastDirectionIndex = ((Piece::GetKind(piece) == Piece::Rook) ? 4 : 8);
    const Piece_t friendlyColor = Piece::GetColor(piece);
    const Piece_t opponentColor = ((friendlyColor == Piece::White) ? Piece::Black : Piece::White);

    for (uint8_t directionIndex=firstDirectionIndex; directionIndex < lastDirectionIndex; ++directionIndex)
    {
        for (uint8_t n=0; n < sm_numSquareToEdge[square][directionIndex]; ++n)
        {
            const uint8_t targetSquare = square + Move::sm_directionOffset[directionIndex] * (n+1);
            if (targetSquare >= Board::NUM_CASE)
            {
                break;
            }
            const Piece_t  pieceOnTargetSquare = board.GetSquareContent(targetSquare);

            if (Piece::CompareColor(pieceOnTargetSquare, friendlyColor))
            {
                break;
            }

            moves->push_back({square, targetSquare});

            if (Piece::CompareColor(pieceOnTargetSquare, opponentColor))
            {
                break;
            }
        }
    }

    return moves;
}

auto Move::GenerateKnightMoves(const Board &board, const Piece_t piece, const uint8_t square) -> MoveList_t
{
    MoveList_t moves = std::make_shared<std::vector<Move_t>>();
    const Piece_t friendlyColor = Piece::GetColor(piece);
    const Piece_t opponentColor = ((friendlyColor == Piece::White) ? Piece::Black : Piece::White);
    constexpr std::array<std::pair<int8_t, int8_t>, 8> movesDelta = {
            std::make_pair(-2,  1),
            std::make_pair(-2, -1),
            std::make_pair( 2,  1),
            std::make_pair( 2, -1),
            std::make_pair( 1,  2),
            std::make_pair(-1,  2),
            std::make_pair( 1, -2),
            std::make_pair(-1, -2),
    };
    uint8_t currentX{0}, currentY{0};
    Board::CoordinateFromBoardIndex(square, currentX, currentY);

    for (const auto& moveDelta : movesDelta)
    {
        const uint8_t x = currentX + std::get<0>(moveDelta);
        const uint8_t y = currentY + std::get<1>(moveDelta);

        const uint8_t targetSquare = Board::BoardIndexFromCoordinate(x, y);

        if ((targetSquare >= Board::NUM_CASE)||
            (x >= Board::BOARD_SIZE)         ||
            (y >= Board::BOARD_SIZE))
        {
            continue;
        }
        const Piece_t  pieceOnTargetSquare = board.GetSquareContent(targetSquare);


        if (Piece::CompareColor(pieceOnTargetSquare, friendlyColor))
        {
            continue;
        }

        moves->push_back({square, targetSquare});

        if (Piece::CompareColor(pieceOnTargetSquare, opponentColor))
        {
            continue;
        }
    }

    return moves;
}

auto Move::GeneratePawnMoves(const Board &board, const Piece_t piece, const uint8_t square) -> MoveList_t
{
    MoveList_t moves = std::make_shared<std::vector<Move_t>>();
    const uint8_t direction = ((board.GetColorToMove() == Piece::White) ? 1 : -1);
    uint8_t currentX{0}, currentY{0};
    Board::CoordinateFromBoardIndex(square, currentX, currentY);
    uint8_t maxDistance = ((((board.GetColorToMove() == Piece::White) && (currentY == 1)) ||
                            ((board.GetColorToMove() == Piece::Black) && (currentY == 6)))
                           ? 2 : 1);

    for (uint8_t step = 0; step < maxDistance; ++step)
    {
        const uint8_t y = currentY + (step + 1) * direction;

        const uint8_t targetSquare = Board::BoardIndexFromCoordinate(currentX, y);

        if ((targetSquare >= Board::NUM_CASE)||
            (y >= Board::BOARD_SIZE))
        {
            continue;
        }
        const Piece_t  pieceOnTargetSquare = board.GetSquareContent(targetSquare);


        if (pieceOnTargetSquare != Piece::None)
        {
            continue;
        }

        moves->push_back({square, targetSquare});
    }

    // TODO: Capture
    // TODO: En passant


    return moves;
}

auto Move::GenerateKingMoves(const Board &board, const Piece_t piece, const uint8_t square) -> MoveList_t
{
    MoveList_t moves = std::make_shared<std::vector<Move_t>>();
    const Piece_t friendlyColor = Piece::GetColor(piece);
    const Piece_t opponentColor = ((friendlyColor == Piece::White) ? Piece::Black : Piece::White);
    uint8_t currentX{0}, currentY{0};
    Board::CoordinateFromBoardIndex(square, currentX, currentY);

    for (int8_t deltaX = -1; deltaX < 2; ++deltaX)
    {
        for (int8_t deltaY = -1; deltaY < 2; ++deltaY)
        {
            if ((deltaX == 0) && (deltaY == 0))
            {
                continue;
            }

            const uint8_t x = currentX + deltaX;
            const uint8_t y = currentY + deltaY;

            const uint8_t targetSquare = Board::BoardIndexFromCoordinate(x, y);

            if ((targetSquare >= Board::NUM_CASE)||
                (x >= Board::BOARD_SIZE)         ||
                (y >= Board::BOARD_SIZE))
            {
                continue;
            }
            const Piece_t  pieceOnTargetSquare = board.GetSquareContent(targetSquare);


            if (Piece::CompareColor(pieceOnTargetSquare, friendlyColor))
            {
                continue;
            }

            moves->push_back({square, targetSquare});

            if (Piece::CompareColor(pieceOnTargetSquare, opponentColor))
            {
                continue;
            }
        }
    }

    // TODO: Rook


    return moves;
}


auto Move::GenerateMoveData() -> void
{
    Log::Debug("Generating static moves data");
    for (uint8_t y=0; y < Board::BOARD_SIZE; ++y)
    {
        for (uint8_t x=0; x < Board::BOARD_SIZE; ++x)
        {
            const uint8_t numNorth = y;
            const uint8_t numSouth = Board::BOARD_SIZE - (y+1);
            const uint8_t numWest  = x;
            const uint8_t numEast  = Board::BOARD_SIZE - (x+1);

            const uint8_t squareIndex = Board::BoardIndexFromCoordinate(x, y);

            sm_numSquareToEdge[squareIndex] = {
                numNorth,
                numSouth,
                numWest,
                numEast,
                std::min(numNorth, numWest),
                std::min(numSouth, numEast),
                std::min(numNorth, numEast),
                std::min(numSouth, numWest),
            };
        };
    }
}

auto Move::MoveToAlgebraicNotation(const Board &board, Move_t move) -> std::string
{
    std::stringstream ss;
    Piece_t piece = board.GetSquareContent(move.originalSquare);

    if (Piece::GetKind(piece) != Piece::Pawn)
    {
        ss << (char)toupper(Piece::FromIntToFen(piece));
    }
    ss << Board::BoardIndexToChessNotation(move.targetSquare);

    return ss.str();
}


