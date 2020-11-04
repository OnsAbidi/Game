/**
 * @file Board.cpp
 * @brief Datei in der alle Methoden (ausser Konsolenausgabe-Methoden) der
 * Klasse Board implementiert sind
 * @author Benedikt Witteler
 * */

#include "Logic.hpp"

//----------BOARD:----------
//KONSTRUKTOREN
Board::Board()
{
    _muehle[0].first = Piece(Piece::taken, Piece::N, Piece::aussen, 0);

    //Einzelne Initialisierung von jedem Array-Element (ausser dem Nullten):
    _muehle[1].first = Piece(Piece::unset, Piece::N, Piece::aussen, 0);
    _muehle[1].second = {2, 8, 9};
    _muehle[2].first = Piece(Piece::unset, Piece::NO, Piece::aussen, 0);
    _muehle[2].second = {1, 3};
    _muehle[3].first = Piece(Piece::unset, Piece::O, Piece::aussen, 0);
    _muehle[3].second = {2, 4, 11};
    _muehle[4].first = Piece(Piece::unset, Piece::SO, Piece::aussen, 0);
    _muehle[4].second = {3, 5};
    _muehle[5].first = Piece(Piece::unset, Piece::S, Piece::aussen, 0);
    _muehle[5].second = {4, 6, 13};
    _muehle[6].first = Piece(Piece::unset, Piece::SW, Piece::aussen, 0);
    _muehle[6].second = {5, 7};
    _muehle[7].first = Piece(Piece::unset, Piece::W, Piece::aussen, 0);
    _muehle[7].second = {6, 8, 15};
    _muehle[8].first = Piece(Piece::unset, Piece::NW, Piece::aussen, 0);
    _muehle[8].second = {7, 1};

    _muehle[9].first = Piece(Piece::unset, Piece::N, Piece::mitte, 0);
    _muehle[9].second = {1, 10, 16, 17};
    _muehle[10].first = Piece(Piece::unset, Piece::NO, Piece::mitte, 0);
    _muehle[10].second = {9, 11};
    _muehle[11].first = Piece(Piece::unset, Piece::O, Piece::mitte, 0);
    _muehle[11].second = {3, 10, 12, 19};
    _muehle[12].first = Piece(Piece::unset, Piece::SO, Piece::mitte, 0);
    _muehle[12].second = {11, 13};
    _muehle[13].first = Piece(Piece::unset, Piece::S, Piece::mitte, 0);
    _muehle[13].second = {5, 12, 14, 21};
    _muehle[14].first = Piece(Piece::unset, Piece::SW, Piece::mitte, 0);
    _muehle[14].second = {13, 15};
    _muehle[15].first = Piece(Piece::unset, Piece::W, Piece::mitte, 0);
    _muehle[15].second = {7, 14, 16, 23};
    _muehle[16].first = Piece(Piece::unset, Piece::NW, Piece::mitte, 0);
    _muehle[16].second = {9, 15};

    _muehle[17].first = Piece(Piece::unset, Piece::N, Piece::innen, 0);
    _muehle[17].second = {9, 18, 24};
    _muehle[18].first = Piece(Piece::unset, Piece::NO, Piece::innen, 0);
    _muehle[18].second = {17, 19};
    _muehle[19].first = Piece(Piece::unset, Piece::O, Piece::innen, 0);
    _muehle[19].second = {11, 18, 20};
    _muehle[20].first = Piece(Piece::unset, Piece::SO, Piece::innen, 0);
    _muehle[20].second = {19, 21};
    _muehle[21].first = Piece(Piece::unset, Piece::S, Piece::innen, 0);
    _muehle[21].second = {13, 20, 22};
    _muehle[22].first = Piece(Piece::unset, Piece::SW, Piece::innen, 0);
    _muehle[22].second = {21, 23};
    _muehle[23].first = Piece(Piece::unset, Piece::W, Piece::innen, 0);
    _muehle[23].second = {15, 22, 24};
    _muehle[24].first = Piece(Piece::unset, Piece::NW, Piece::innen, 0);
    _muehle[24].second = {17, 23};

    //Alle Owner auf unset setzen
    for (ownerStatus& s : _owner) {
        s = unset;
    }

}

//GETTER
std::pair<Piece, std::array<uint8_t, 4>> Board::getPairAtPosition(int i){
    if ((i < 1 || i > 24))
        return _muehle[0];
    else
        return _muehle[i];
}
std::pair<Piece, std::array<uint8_t, 4>> Board::getPairAtPosition(Piece pieceLooking) {
    return getPairAtPosition(getBoardIndex(pieceLooking));
}

int Board::getBoardIndex(Piece searched){
    int idx = 1;
    for(; (!(_muehle[idx].first.sameCoordinates(searched)) ||
             idx >= _muehle.size()); idx++);
    if (idx >= _muehle.size()) {
        std::cout << "FEHLER: Kein Index fuer Spielstein gefunden!" << std::endl;
        return 0;
    } else {
        return idx;
    }
}

Board::ownerStatus Board::getOwnerOfPiece(Piece pieceLooking) {
    return _owner[getBoardIndex(pieceLooking)];
}

//SETTER
void Board::setGivenPiece(Piece pieceToSet) {
    int idx = getBoardIndex(pieceToSet);
    _muehle[idx].first = pieceToSet;
}

void Board::setGivenOwner(Piece pieceToSet, ownerStatus ownerToSetTo) {
    _owner[getBoardIndex(pieceToSet)] = ownerToSetTo;
}

void Board::freeGivenPieceAndOwner(Piece pieceToFree) {
    int idx = getBoardIndex(pieceToFree);
    _muehle[idx].first._statusPiece = Piece::unset;
    _muehle[idx].first._mill = false;
    _owner[idx] = unset;
}

void Board::setPieceMill(int idx1, bool millToSetTo) {
    _muehle[idx1].first._mill = millToSetTo;
}

void Board::setPieceMill(int idx1, int idx2, int idx3) {
    _muehle[idx1].first._mill = true;
    _muehle[idx2].first._mill = true;
    _muehle[idx3].first._mill = true;
}

//METHODEN
std::array<uint8_t, 4> Board::getNeighbors(Piece neighborsOf)
{
    return _muehle[getBoardIndex(neighborsOf)].second;
}

std::set<int> Board::searchForMill() {
    std::set<int> piecesInMill;

    piecesMakeMill(8, 1, 2, piecesInMill);
    piecesMakeMill(16, 9, 10, piecesInMill);
    piecesMakeMill(24, 17, 18, piecesInMill);
    piecesMakeMill(22, 21, 20, piecesInMill);
    piecesMakeMill(14, 13, 12 , piecesInMill);
    piecesMakeMill(6, 5, 4, piecesInMill);
    piecesMakeMill(6, 7, 8, piecesInMill);
    piecesMakeMill(14, 15, 16, piecesInMill);
    piecesMakeMill(22, 23, 24, piecesInMill);
    piecesMakeMill(20, 19, 18, piecesInMill);
    piecesMakeMill(12, 11, 10, piecesInMill);
    piecesMakeMill(4, 3, 2, piecesInMill);
    piecesMakeMill(1, 9, 17, piecesInMill);
    piecesMakeMill(3, 11, 19, piecesInMill);
    piecesMakeMill(5, 13, 21, piecesInMill);
    piecesMakeMill(5, 15, 23, piecesInMill);

    return piecesInMill;
}

void Board::piecesMakeMill(int i1, int i2, int i3, std::set<int>& piecesInMill) {
    if ((_owner[i1] == _owner[i2]) && (_owner[i2] == _owner[i3]) && (_owner[i1] != ownerStatus::unset)) {
        setPieceMill(i1, i2, i3);
        piecesInMill.insert(i1);
        piecesInMill.insert(i2);
        piecesInMill.insert(i3);
    }
}

//NEU:
//OPERATOREN
int Board::numberMills() {
    int count = 0;
    for (int i = 1; i <25; i++) {
        if (_muehle[i].first._mill)
            count += 1;
    }

    return count;
}
