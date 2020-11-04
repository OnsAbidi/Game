/**
 * @file LogicConsole.cpp
 * @brief Datei in der alle Konsolenausgabe-Methoden der
 * Klassen Piece, Board und Player implementiert sind
 * @author Benedikt Witteler
 * */

#include "Logic.hpp"

//----------PIECE----------
//KONSOLENFUNKTIONEN:
std::string Piece::stringPiece()
{
    std::string position;
    switch (_statusPiece) 
    {
    case unset:
        position = "unset ";
        break;
    case set:
        position = "set   ";
        break;
    case taken:
        position = "taken ";
        break;
    default:
        break;
    }
    switch (_directionPiece)
    {
    case N:
        position = position + "N  ";
        break;
    case NO:
        position = position + "NO ";
        break;
    case O:
        position = position + "O  ";
        break;
    case SO:
        position = position + "SO ";
        break;
    case S:
        position = position + "S  ";
        break;
    case SW:
        position = position + "SW ";
        break;
    case W:
        position = position + "W  ";
        break;
    case NW:
        position = position + "NW ";
        break;
    default:
        break;
    }
    switch (_squarePiece)
    {
    case aussen:
        position = position + "aussen ";
        break;
    case mitte:
        position = position + "mitte  ";
        break;
    case innen:
        position = position + "innen  ";
        break;
    default:
        break;
    }
    if (_mill)
        position = position + "muehle";
    else
        position = position + "frei  ";
    return position;
}

//----------BOARD----------
void Board::printPositionsOfBoard() {
    int i = 0;
    for (auto at : _muehle)
        std::cout << i++ << ": " << at.first.stringPiece() << std::endl;
    std::cout << std::endl;
}

void Board::printInitialBoardVisual(){
    std::cout << "o - - - - - o - - - - - o" << std::endl;
    std::cout << "|           |           |" << std::endl;
    std::cout << "|   o - - - o - - - o   |" << std::endl;
    std::cout << "|   |       |       |   |" << std::endl;
    std::cout << "|   |   o - o - o   |   |" << std::endl;
    std::cout << "o - o - o       o - o - o" << std::endl;
    std::cout << "|   |   o - o - o   |   |" << std::endl;
    std::cout << "|   |       |       |   |" << std::endl;
    std::cout << "|   o - - - o - - - o   |" << std::endl;
    std::cout << "|           |           |" << std::endl;
    std::cout << "o - - - - - o - - - - - o" << std::endl;
}

void Board::printBoardVisual(){
    
    std::cout << giveActualPiece(8) << std::flush;
    std::cout << " - - - - - " << std::flush;
    std::cout << giveActualPiece(1) << std::flush;
    std::cout << " - - - - - " << std::flush;
    std::cout << giveActualPiece(2) << std::endl;

    std::cout << "|           |           |" << std::endl;

    std::cout << "|   " << std::flush;
    std::cout << giveActualPiece(16) << std::flush;
    std::cout << " - - - " << std::flush;
    std::cout << giveActualPiece(9) << std::flush;
    std::cout <<  " - - - " << std::flush;
    std::cout << giveActualPiece(10) << std::flush;
    std::cout << "   |" << std::endl;

    std::cout << "|   |       |       |   |" << std::endl;

    std::cout << "|   |   " << std::flush;
    std::cout << giveActualPiece(24) << std::flush; //24???
    std::cout << " - " << std::flush;
    std::cout << giveActualPiece(17) << std::flush;
    std::cout << " - " << std::flush;
    std::cout << giveActualPiece(18) << std::flush;
    std::cout << "   |   |" << std::endl;

    std::cout << giveActualPiece(7) << std::flush;
    std::cout << " - " << std::flush;
    std::cout << giveActualPiece(15) << std::flush;
    std::cout << " - " << std::flush;
    std::cout << giveActualPiece(23) << std::flush;
    std::cout << "       " << std::flush;
    std::cout << giveActualPiece(19) << std::flush;
    std::cout << " - " << std::flush;
    std::cout << giveActualPiece(11) << std::flush;
    std::cout << " - " << std::flush;
    std::cout << giveActualPiece(3) << std::endl;


    std::cout << "|   |   " << std::flush;
    std::cout << giveActualPiece(22) << std::flush;
    std::cout << " - " << std::flush;
    std::cout << giveActualPiece(21) << std::flush;
    std::cout << " - " << std::flush;
    std::cout << giveActualPiece(20) << std::flush;
    std::cout << "   |   |" << std::endl;

    std::cout << "|   |       |       |   |" << std::endl;

    std::cout << "|   " << std::flush;
    std::cout << giveActualPiece(14) << std::flush;
    std::cout << " - - - " << std::flush;
    std::cout << giveActualPiece(13) << std::flush;
    std::cout <<  " - - - " << std::flush;
    std::cout << giveActualPiece(12) << std::flush;
    std::cout << "   |" << std::endl;

    std::cout << "|           |           |" << std::endl;

    std::cout << giveActualPiece(6) << std::flush;
    std::cout << " - - - - - " << std::flush;
    std::cout << giveActualPiece(5) << std::flush;
    std::cout << " - - - - - " << std::flush;
    std::cout << giveActualPiece(4) << std::endl;

}

std::string Board::giveActualPiece(int idx) {
    std::string playerSymbol;
    switch (_owner[idx]) {
        case unset:
            playerSymbol = "o";
            break;
        case server:
            playerSymbol = "\x1B[36m#\033[0m";
            break;
        case client:
            playerSymbol = "\033[1;31m*\033[0m";
            break;
        default:
            playerSymbol = " ";
            break;
    }
    return playerSymbol;

}

//----------PLAYER----------
//KONSOLENFUNKTIONEN:
void Player::printPlayer()
{
    std::cout << "-----PLAYER-----" << std::endl;
    std::cout << "Generelle Informationen:" << std::endl;
    std::cout << "  _name: " << _name << std::endl;
    std::cout << "  _beginner: " << _beginner << std::endl;
    std::cout << "  _color: " << _color << std::endl;

    std::cout << "Spielablauf:" << std::endl;
    std::cout << "  _countPieces: " << static_cast<uint>(_countPieces) << std::endl;
    //wahrscheinlich ist uint8_t nicht normal ausgebbar, weil es wir char behandelt wird
//    std::cout << "  _blocked: " << _blocked << std::endl;
    std::cout << "  _move: " << _move << std::endl;
    std::cout << "  _phasePlayer: " << _phasePlayer << std::endl;
    std::cout << "  _winner: " << _winner << std::endl;
    std::cout << "  _piecesPlayer: " << std::endl;
        for (int idx = 0; idx < _piecesPlayer.size(); idx++)
        {
            std::cout << "      Position " << idx << ": " << _piecesPlayer[idx].stringPiece() << std::endl;
            
        }

    std::cout << "Netzwerkspeziefisches:" << std::endl;
    std::cout << "  _server: " << _server << std::endl;

    std::cout << std::endl;
}
