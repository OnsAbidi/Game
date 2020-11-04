/**
 * @file Game.cpp
 * @brief Datei in der alle Methoden (auch Konsolenausgabe-Methoden) der
 * Klasse Gamr implementiert sind
 * @author Benedikt Witteler
 * */

#include "Game.hpp"

//----------GAME:----------
// KONSTRUKTOREN:
Game::Game()
    : _playerServer(),
      _playerClient(Player("Player2", false, true, 9, false, Player::Setzphase, false, false)),
      _gameBoard(),
      _boardBeforeMove()
{
}
Game::Game(bool middleOfGame)
    :Game() //darf nicht in Funktionskoerper, wegen const-Initialisierungen
{
    if (middleOfGame) {
        for (int i = 1; i < (19 +4); i++) {
            if (i == 5)
                i++;
            if (i == 9)
                i++;
            if (i == 17)
                i++;
            if (i == 19)
                i++;

            if (_playerServer.getPlayerOnMove() && !_playerClient.getPlayerOnMove())
            {
                //...Server ist am Zug, Client nicht
                _playerServer.setPiece(_gameBoard.getPairAtPosition(i).first, _gameBoard);
            }
            else if (!_playerServer.getPlayerOnMove() && _playerClient.getPlayerOnMove())
            {
                //...Client ist am Zug, Server nicht
                _playerClient.setPiece(_gameBoard.getPairAtPosition(i).first, _gameBoard);
            }
            else
            {
                std::cout << "FEHLER: Kein eideutiger Spieler ist am Zug!" << std::endl;
            }
            //Umstellen wer dran ist:
            _playerServer.togglePlayerOnMove();
            _playerClient.togglePlayerOnMove();
        }
    }
}
// SPIELSTEUERUNG:
int Game::play() {
    _gameBoard.printBoardVisual();

    while (continueGame()) {
        //Vergleichsbrett aktualisieren
        _boardBeforeMove = _gameBoard;

        if (_playerServer.getPlayerOnMove() && !_playerClient.getPlayerOnMove()){
            //...Server ist am Zug, Client nicht
            std::cout << "-----" << _playerServer._name << " (Server) \x1B[36m#\033[0m am Zug-----" << std::endl;
            findAndPlayMove(_playerServer);

//            //Aus Slot...
//            //Muehlen ueberpruefen und anpassen
//            updateMill();
//            //Wurde Muehle geschlossen?
//            if (_gameBoard.numberMills() > _boardBeforeMove.numberMills())
//                playTakePiece(_playerClient);

        }
        else if (!_playerServer.getPlayerOnMove() && _playerClient.getPlayerOnMove()) {
            //...Client ist am Zug, Server nicht
            std::cout << "-----" << _playerClient._name << " (Client) \033[1;31m*\033[0m am Zug-----" << std::endl;
            findAndPlayMove(_playerClient);

//            //Aus Slot ...
//            //Muehlen ueberpruefen und anpassen
//            updateMill();
//            //Wurde Muehle geschlossen?
//            if (_gameBoard.numberMills() > _boardBeforeMove.numberMills())
//                playTakePiece(_playerServer);

        } else {
            std::cout << "FEHLER: Kein eideutiger Spieler ist am Zug!" << std::endl;
            return 1;
        }

//        //Aufrufe aus Slots, weil diese nicht aufgerufen werden koennen:...
//        //Alte Muehlen aufraeumen:
//        eraseOldMills();
//        //Umstellen, wer am Zug ist:
//        _playerServer.togglePlayerOnMove();
//        _playerClient.togglePlayerOnMove();
//        //Konsolenaudgabe
//        _gameBoard.printBoardVisual();

    }

    end();
    return 0;
}

int Game::findAndPlayMove(Player& playerOnMove) {
    if (playerOnMove.getPhasePlayer() == Player::Setzphase) {
//        {/* kann ohne Netzwerk nicht durchgefuehrt werden...
            Piece coord = inputCoordinates();
            std::array<quint8, 4> params = convertPieceToQuint(coord);
            //Gewuenschten Zug zwischenspeichern:
            _currentMoveInfo[0] = params[0];
            _currentMoveInfo[1] = params[1];
            _currentMoveInfo[2] = params[2];
            _currentMoveInfo[3] = params[3];
            // _currentMoveInfo[4] bleibt in diesem Fall leer
            if (playerOnMove._server)
                _currentMoveInfo[5] = true;
            else
                _currentMoveInfo[5] = false;
            //Sende an Netzwerk:
            emit setPieceSig(params[0], params[1], params[2], params[3]);
//        */}
//        //Lokale Alternative:...
//        bool error = false; //ungueltiger Zug
//        do {
//            std::cout << "Spielstein setzten - Zielposition: " << std::endl;
//            //Position einlesen:
//            Piece coord = inputCoordinates();
//            error = playerOnMove.setPiece(coord, _gameBoard);
//        } while (error);

    } else {
        bool error = false; //ungueltiger Zug
        do {
            std::cout << "Spielstein ziehen - Startposition: " << std::endl;
            Piece tempStart = inputCoordinates();
            std::cout << "Spielstein ziehen - Zielposition: " << std::endl;
            Piece tempZiel = inputCoordinates();
            error = playerOnMove.makeMove(tempStart, tempZiel, _gameBoard);
        } while (error);

        //Aufrufe aus Slots, weil diese nicht aufgerufen werden koennen:...
        //Alte Muehlen aufraeumen:
        eraseOldMills();
        //Umstellen, wer am Zug ist:
        _playerServer.togglePlayerOnMove();
        _playerClient.togglePlayerOnMove();
        //Konsolenaudgabe
        _gameBoard.printBoardVisual();
    }
    return 0;
}


/////√
int Game::playTakePiece(Player& playerTakenFrom) {
    bool error = false;
    do {
        std::cout << "Gegnerischen Spielstein wegnehmen: " << std::endl;
        error = playerTakenFrom.takePiece(inputCoordinates(), _gameBoard);
    } while (error);

    return 0;
}

void Game::eraseOldMills() {
    for (int i = 1; i < 25; i++) {
        _gameBoard.setPieceMill(i, false);
    }
    updateMill();
}

bool Game::updateMill(){
    //Muehlen ueberpruefen und anpassen
    std::set<int> piecesInMill = _gameBoard.searchForMill();
    for (int p : piecesInMill)
    {
        _gameBoard.getPairAtPosition(p).first.setMillPiece(true);
    }
    return false;
}

Piece Game::inputCoordinates() {
    Piece inputPiece;
    bool invalidDirection = false;
    bool invalidSquare = false;

    do {
        invalidDirection = false;

        std::string inputDirection;
        std::cout << "Himmelsrichtung: ";
        std::cin >> inputDirection;
        std::transform(inputDirection.begin(), inputDirection.end(), inputDirection.begin(), ::toupper);

        if (inputDirection == "N" || inputDirection == "1")
            inputPiece.setDirectionPiece(Piece::N);
        else if (inputDirection == "NO" || inputDirection == "2")
            inputPiece.setDirectionPiece(Piece::NO);
        else if (inputDirection == "O" || inputDirection == "3")
            inputPiece.setDirectionPiece(Piece::O);
        else if (inputDirection == "SO" || inputDirection == "4")
            inputPiece.setDirectionPiece(Piece::SO);
        else if (inputDirection == "S" || inputDirection == "5")
            inputPiece.setDirectionPiece(Piece::S);
        else if (inputDirection == "SW" || inputDirection == "6")
            inputPiece.setDirectionPiece(Piece::SW);
        else if (inputDirection == "W" || inputDirection == "7")
            inputPiece.setDirectionPiece(Piece::W);
        else if (inputDirection == "NW" || inputDirection == "8")
            inputPiece.setDirectionPiece(Piece::NW);
        else {
            invalidDirection = true;
            std::cout << "FEHLER: Keine gueltige Himmelsrichtung!" << std::endl;
        }
    } while (invalidDirection);

    do {
        invalidSquare = false;

        std::string inputSquare;
        std::cout << "Quadrat: ";
        std::cin >> inputSquare;
        std::transform(inputSquare.begin(), inputSquare.end(), inputSquare.begin(), ::toupper);

        if (inputSquare == "AUSSEN" || inputSquare == "1" || inputSquare == "A")
            inputPiece.setSquarePiece(Piece::aussen);
        else if (inputSquare == "MITTE" || inputSquare == "2" || inputSquare == "M")
            inputPiece.setSquarePiece(Piece::mitte);
        else if (inputSquare == "INNEN" || inputSquare == "3" || inputSquare == "I")
            inputPiece.setSquarePiece(Piece::innen);
        else {
            invalidSquare = true;
            std::cout << "FEHLER: Kein gueltiges Quadrat!" << std::endl;
        }
    } while (invalidSquare);

    return inputPiece;
}


//NEULOGIC:
bool Game::continueGame() {
    if (_playerServer._countPieces < 3) {
        std::cout << "--> " << _playerServer._name << " hat weniger als 3 Steine." << std::endl;
        _playerClient._winner = true;
        return false;
    }
    if (_playerClient._countPieces < 3) {
        std::cout << "--> " << _playerClient._name << " hat weniger als 3 Steine." << std::endl;
        _playerServer._winner = true;
        return false;
    }
    if (_playerServer.getCheckPlayerBlocked(_gameBoard)) {
        std::cout << "--> " << _playerServer._name << " ist blockiert." << std::endl;
        _playerClient._winner = true;
        return false;
    }
    if (_playerClient.getCheckPlayerBlocked(_gameBoard)) {
        std::cout << "--> " << _playerClient._name << " ist blockiert." << std::endl;
        _playerServer._winner = true;
        return false;
    }
    return true;
}

int Game::end() {
    if (_playerServer._winner)
        std::cout << "ENDE: " << _playerServer._name << " hat gewonnen!" << std::endl;
    else
        std::cout << "ENDE: " << _playerClient._name << " hat gewonnen!" << std::endl;

    return 0;
}


int Game::start() {
    play();
    return 0;
}
