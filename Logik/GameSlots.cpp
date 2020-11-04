#include "Game.hpp"

//Slots
int Game::setPieceControlSlot(quint8 direction, quint8 square, quint8 piecesLeftToSet, quint8 closedMill) {
    //call Game::play() -> while-Schleife verschwindet..?
    bool error = false;

    error = playUe(direction, square, piecesLeftToSet, closedMill);

    if (error)
        emit setPieceAnsweredSig(0x12);
    else
        emit setPieceAnsweredSig(0x00);

    return 0;
}

int Game::setPieceAnsweredSlot(quint8 answer) {
    if (answer) {
        //Fehler
        std::cout << "FEHLER: Gegenspieler hat Zug fuer ungueltig erklaert!" << std::endl;
        //Neuer Zugversuch:
        Piece coord = inputCoordinates();
        std::array<quint8, 4> params = convertPieceToQuint(coord);
        //Sende an Netzwerk:
        emit setPieceSig(params[0], params[1], params[2], params[3]);
    } else {
        //Zug durchführen
        Piece destination = convertQuintToPiece(_currentMoveInfo[0], _currentMoveInfo[1]);
        if (_currentMoveInfo[5] == true) { //Server am Zug
            //Eingabe wird mitueberprueft
            int inputError = 0;
            inputError = _playerServer.setPiece(destination, _gameBoard);
            if (inputError)
                return inputError;

            //Muehlen ueberpruefen und anpassen
            updateMill();
            //Wurde Muehle geschlossen?
            if (_gameBoard.numberMills() > _boardBeforeMove.numberMills())
                playTakePiece(_playerClient);

            //Alte Muehlen aufraeumen:
            eraseOldMills();

            //Umstellen, wer am Zug ist:
            _playerServer.togglePlayerOnMove();
            _playerClient.togglePlayerOnMove();

            //Konsolenausgabe
            _gameBoard.printBoardVisual();

        } else { //Client am Zug
            //Eingabe wird mitueberprueft
            int inputError = 0;
            inputError = _playerClient.setPiece(destination, _gameBoard);
            if (inputError)
                return inputError;

            //Muehlen ueberpruefen und anpassen
            updateMill();
            //Wurde Muehle geschlossen?
            if (_gameBoard.numberMills() > _boardBeforeMove.numberMills())
            playTakePiece(_playerServer);

            //Alte Muehlen aufraeumen:
            eraseOldMills();

            //Umstellen, wer am Zug ist:
            _playerServer.togglePlayerOnMove();
            _playerClient.togglePlayerOnMove();

            //Konsolenausgabe
            _gameBoard.printBoardVisual();
        }
    }

    return 0;
}

//Konvertermethoden
std::array<quint8, 4> Game::convertPieceToQuint(Piece destination) {
    std::array<quint8, 4> temp;
    temp[0] = static_cast<quint8>(destination._directionPiece);
    if (destination._squarePiece == Piece::aussen)
        temp[1] = 1;
    if (destination._squarePiece == Piece::mitte)
        temp[1] = 2;
    if (destination._squarePiece == Piece::innen)
        temp[1] = 3;
    temp[2] = static_cast<quint8>(0); //es muessen nie noch Steine gesetzt werden
    temp[2] = static_cast<quint8>(0); //nie Muehle geschlossen
    return temp;
}
Piece Game::convertQuintToPiece(quint8 direction, quint8 square) {
    Piece temp;
    temp._directionPiece = static_cast<Piece::direction>(direction);
    if (square == 1)
        temp._squarePiece = Piece::aussen;
    if (square == 2)
        temp._squarePiece = Piece::mitte;
    if (square == 3)
        temp._squarePiece = Piece::innen;
    return temp;
}

//Ueberladungen
int Game::playUe(quint8 direction, quint8 square, quint8 piecesLeftToSet, quint8 closedMill) {
    //Koordinaten sind fest, werden nicht eingelesen sondern uebergeben:
    Piece destination = convertQuintToPiece(direction, square);

    if (_playerServer.getPlayerOnMove() && !_playerClient.getPlayerOnMove()){
        //...Server ist am Zug, Client nicht
        std::cout << "-----" << _playerServer._name << " (Server) \x1B[36m#\033[0m am Zug-----" << std::endl;
        findAndPlayMove(_playerServer, destination);

        //Muehlen ueberpruefen und anpassen
        updateMill();
        //Wurde Muehle geschlossen?
        if (_gameBoard.numberMills() > _boardBeforeMove.numberMills())
            playTakePiece(_playerClient);
    }
    else if (!_playerServer.getPlayerOnMove() && _playerClient.getPlayerOnMove()) {
        //...Client ist am Zug, Server nicht
        std::cout << "-----" << _playerClient._name << " (Client) \033[1;31m*\033[0m am Zug-----" << std::endl;
        findAndPlayMove(_playerClient, destination);

        //Muehlen ueberpruefen und anpassen
        updateMill();
        //Wurde Muehle geschlossen?
        if (_gameBoard.numberMills() > _boardBeforeMove.numberMills())
            playTakePiece(_playerServer);
    } else {
        std::cout << "FEHLER: Kein eideutiger Spieler ist am Zug!" << std::endl;
        return 1;
    }

    //Alte Muehlen aufraeumen:
    eraseOldMills();
    //Umstellen, wer am Zug ist:
    _playerServer.togglePlayerOnMove();
    _playerClient.togglePlayerOnMove();
    //Konsolenaudgabe
    _gameBoard.printBoardVisual();

    return 0;
}

int Game::findAndPlayMove(Player& playerOnMove, Piece destination) {
    if (playerOnMove.getPhasePlayer() == Player::Setzphase) {
        return playerOnMove.setPiece(destination, _gameBoard);

    } else {
            std::cout << "Spielstein ziehen - Startposition: " << std::endl; ////TODO
            Piece tempStart = inputCoordinates();
            std::cout << "Spielstein ziehen - Zielposition: " << std::endl;
            Piece tempZiel = inputCoordinates();
            playerOnMove.makeMove(tempStart, tempZiel, _gameBoard);
    }
    return 0;
}






//Weil keine Netzwerkverbindung vorhanden ist, wird in diesem SLOT die Netzwerkuebertragung,
//durch eine Zuordnung der Parameter simuliert:
void Game::simulateNetworkSlot(quint8 direction, quint8 square, quint8 piecesLeftToSet, quint8 closedMill) {

    //weil kein Verbindungsfehler auftreten kann, ist Antwort immer gleich
    emit simulateNetworkSig(0x00);
}


