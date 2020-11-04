/**
 * @file Logic.cpp
 * @brief Datei in der alle Methoden (ausser Konsolenausgabe-Methoden) der
 * Klassen Piece und Player implementiert sind
 * @author Benedikt Witteler
 * */

#include "Logic.hpp"

//----------PIECE----------
//KONSTRUKTOREN:
Piece::Piece()
    : _statusPiece(unset), _directionPiece(N), _squarePiece(aussen), _mill(false)
{
}
Piece::Piece(status statusPlayer, direction directionPlayer, square squarePlayer, bool mill)
    : _statusPiece(statusPlayer), _directionPiece(directionPlayer), _squarePiece(squarePlayer),
      _mill(mill)
{
}

//OPERATOREN (fuer Iteratoren)
bool Piece::operator==(const Piece comparedPiece)
{
    if (_statusPiece == comparedPiece._statusPiece &&
        _directionPiece == comparedPiece._directionPiece &&
        _squarePiece == comparedPiece._squarePiece &&
        _mill == comparedPiece._mill)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Piece::sameCoordinates(const Piece comparedPiece)
{
    if (_directionPiece == comparedPiece._directionPiece &&
        _squarePiece == comparedPiece._squarePiece)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//NEU
//GETTER & SETTER
void Piece::setDirectionPiece(direction directionToSetTo) {
    _directionPiece = directionToSetTo;
}
void Piece::setSquarePiece(square squareToSetTo){
    _squarePiece = squareToSetTo;
}
bool Piece::setMillPiece(bool millToSetTo) {
    _mill = millToSetTo;
    return false;
}

//----------PLAYER----------
//KONSTRUKTOREN:
Player::Player()
    : _name("Player1"), _beginner(true), _color(false),
      _countPieces(9), _move(true), _phasePlayer(Setzphase), _winner(false),
      /* _piecesPlayer wird erst in Funktionskoerper initialisiert*/
      _server(true)
{
    _countSetPieces = 0;

        std::array<Piece, 9>
            _piecesPlayer;
    for (auto idx : _piecesPlayer)
        idx = Piece();
}
Player::Player(std::string name, bool beginner, bool color,
               uint8_t countPieces, bool move, phase phasePlayer, bool winner,
               /* _piecesPlayer wird default initialisiert*/
               bool server)
    : _name(name), _beginner(beginner), _color(color),
      _countPieces(countPieces), _move(move), _phasePlayer(phasePlayer), _winner(winner),
      /* _piecesPlayer wird erst in Funktionskoerper initialisiert*/
      _server(server)
{
    _countSetPieces = 0;

    std::array<Piece, 9> _piecesPlayer;
    for (auto idx : _piecesPlayer)
        idx = Piece();
}

//SPIELABLAUF:
int Player::setPiece(Piece destination, Board &currentBoard)
{
    if (_phasePlayer != Setzphase){
        std::cout << "FEHLER: Bereits alle Spielsteine gesetzt!" << std::endl;
        return 1;
    }
    else
    {
        if (currentBoard.getPairAtPosition(destination).first._statusPiece == Piece::set)
        {
            std::cout << "FEHLER: Position ist schon besetzt!" << std::endl;
            return 2;
        }
        else
        {
            //Alle Bedingungen erfuellt:
            destination._statusPiece = Piece::set;
            //Spieler anpassen
            _piecesPlayer[_countSetPieces] = destination;
            if (_countSetPieces == 8)
                _phasePlayer = Zugphase; //gehoert zu Player und ist deshalb bekannt

            //Spielfeld anpassen
            currentBoard.setGivenPiece(destination);
            if (_server)
                currentBoard.setGivenOwner(destination, Board::server);
            else if (!_server)
                currentBoard.setGivenOwner(destination, Board::client);
            _countSetPieces += 1;
            return 0;
        }
    }
}

int Player::makeMove(Piece pieceToBeMoved, Piece destination, Board &currentBoard)
{
    if (_phasePlayer == Setzphase)
    {
        std::cout << "FEHLER: Spieler ist nicht in Zugphase oder Endphase!" << std::endl;
        return 1;
    } else if (currentBoard.getPairAtPosition(pieceToBeMoved).first._statusPiece != Piece::set) {
        std::cout << "FEHLER: Zu ziehender Spielstein ist nicht gesetzt!" << std::endl;
        return 3;
    } else if (currentBoard.getPairAtPosition(destination).first._statusPiece == Piece::set) {
        std::cout << "FEHLER: Zielposition ist schon besetzt!" << std::endl;
        return 2;
    } else if ((currentBoard.getOwnerOfPiece(pieceToBeMoved) == Board::server && !_server)
                || (currentBoard.getOwnerOfPiece(pieceToBeMoved) == Board::client && _server)) {
        //Pruefe ob "pieceTeMoved" zum richtigen Spieler gehoert...
        std::cout << "FEHLER: Zu ziehender Spielstein gehoert nicht zu diesem Spieler!" << std::endl;
        return 5;
    } else {
        if (_phasePlayer == Zugphase)
        {
            //Nachbarschaftsbeziehung pruefen:
            bool isNeighbor = false;
            for (int n : currentBoard.getPairAtPosition(pieceToBeMoved).second)
            {
                if (n == currentBoard.getBoardIndex(destination))
                {
                    isNeighbor = true;
                    break;
                }
            }
            if (!isNeighbor)
            {
                std::cout << "FEHLER: Zielposition ist keine Nachbarposition!" << std::endl;
                return 4;
            }
        }
        //Alle Bedingungen fuer Zug (in Enddphase ggf. Sprung) sind erfuellt:
        //(_piecesPlayer vom Spieler wird ab jetzt nicht mehr angepasst!!)
        destination._statusPiece = Piece::set;
        pieceToBeMoved._statusPiece = Piece::unset;
        //Spielfeld anpassen
        currentBoard.setGivenPiece(destination);
        if (_server == 1)
            currentBoard.setGivenOwner(destination, Board::server);
        else
            currentBoard.setGivenOwner(destination, Board::client);
        currentBoard.freeGivenPieceAndOwner(pieceToBeMoved);

        return 0;
    }
}

int Player::takePiece(Piece pieceToTake, Board &currentBoard)
{
    if (currentBoard.getPairAtPosition(pieceToTake).first._statusPiece == Piece::unset) {
        std::cout << "FEHLER: Auf Position wo weggenommen werden soll, kann " << std::flush;
        std::cout << "nichts weggenommen werden, weil dort kein Spielstein liegt!" << std::endl;
        return 1;
    } else if (currentBoard.getPairAtPosition(pieceToTake).first._mill == true) {
        std::cout << "FEHELR: Spielstein ist Teil einer Muehle!" << std::endl;
        return 2;
    } else if ((currentBoard.getOwnerOfPiece(pieceToTake) == Board::server && !_server)
                || (currentBoard.getOwnerOfPiece(pieceToTake) == Board::client && _server)) {
        //Pruefe ob "pieceToTake" zum richtigen Spieler gehoert:
        std::cout << "FEHLER: Der Spielstein, der weggenommen werden soll, " << std::flush;
        std::cout << "gehoert nicht zu diesem Spieler!" << std::endl;
        return 5;
    } else {
        //Spielfeld anpassen
        currentBoard.freeGivenPieceAndOwner(pieceToTake);

        //Spieler anpassen
        _countPieces -= 1;
        if (_countPieces < 4)
            _phasePlayer = Endphase;

        return 0;
    }
}

//GETTER & SETTER:
bool Player::getPlayerOnMove() {
    return _move;
}

Player::phase Player::getPhasePlayer() {
    return _phasePlayer;
}

void Player::togglePlayerOnMove() {
    _move = !_move;
}

//NEU:
bool Player::getCheckPlayerBlocked(Board currentBoard) {
    if (_phasePlayer == Setzphase)
        return false;
    for (int i = 1; i < 25; i++) {
        if (_server) {
            if (currentBoard.getOwnerOfPiece(currentBoard.getPairAtPosition(i).first) == Board::server) {
                for (int neighbor : currentBoard.getPairAtPosition(i).second) {
                    if (currentBoard.getPairAtPosition(neighbor).first._statusPiece == Piece::unset)
                        return false;
                }
            }
        } else {
            if (currentBoard.getOwnerOfPiece(currentBoard.getPairAtPosition(i).first) == Board::client)
            {
                for (int neighbor : currentBoard.getPairAtPosition(i).second) //falls hoehere Nachbarn nicht
                                //existieren, sind diese das nullte Element. Dieses muss also taken sein by default
                                //was mit der Wortbedeutung taken nichts zu tun hat
                {
                    if (currentBoard.getPairAtPosition(neighbor).first._statusPiece == Piece::unset)
                        return false;
                }
            }
        }
    }
    return true; //wenn nie ein Nachbar ungesetzt war, ist der Spieler blockiert
}
