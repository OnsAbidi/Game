/**
 * @file testMain.cpp
 * @brief Datei mit main-Funktion zum Testen
 * @author Benedikt Witteler
 * */


#include "../Netzwerk/supervisor.h"

//TESTMETHODEN
void addPieceToPlayer (Player& playerToAddTo, int directionToSetTo, int squareToSetTo,
                       Board& currentBoard) {
    Piece tempPiece = Piece(Piece::set,
                            static_cast<Piece::direction>(directionToSetTo % 8 + 1),
                            static_cast<Piece::square>(squareToSetTo % 3 + 1),
                            false);
    playerToAddTo.setPiece(tempPiece, currentBoard);
}

void randomInitializePlayer(Player& playerToInitialize, Board& currentBoard){
    for (int i = 0; i < 9; i++) {
        addPieceToPlayer(playerToInitialize, i, i, currentBoard);
    }
}


int main() {

    Supervisor muehelNetzwerkUndLogik;
    muehelNetzwerkUndLogik._spiel.start();

}

//Alternative main wenn Netzwerkverbindung genutzt wuerde
//int main(int argc, char *argv[])
//{
//    //Create application
//    QCoreApplication a(argc, argv);
//    Supervisor superv;

//    //run application
//    return a.exec();
//}
