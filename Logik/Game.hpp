/**
 * @file Game.hpp
 * @brief Datei mit Klasse Game
 * @author Benedikt Witteler
 * */

/** @mainpage Startseite
 *
 * @section Blockprktikum C++ WS 19/20
 * @subsection Gruppe_11
 * 
 * @version final
 * @date 26.03.2020
 * @warning Das Programm laeuft ohne GUI und Netzwerkverbindung. Siehe README.md
 * 
 * @section Programmierstiel
 * @subsection Exceptions im Logikteil
 * Der Rueckgabetyp von Funktionen (oder Metohden), die eigentlich nichts zurueckgeben und damit 
 * "void" waere , ist haeufig als "int" (ggf. auch "bool") gewaehlt um anhand des Rueckgabetyps
 * festzustellen, ob bei der Ausfuehrung der Funktion alles funktioniert hat.
 * 0 (false) = kein Fehler, andere Zahl (true) = Fehler. Der Fehler kann durch verschiedene
 * Rueckgabewerte ungleich Null spezifiziert werden. Bei aehnlichen Funktionen mit den gleichen
 * Fehlern, wurde versucht die gleichen Fehlercodes zurueckzugeben.
 * */

#pragma once

#include "Logic.hpp"
#include <QObject>


/**
 * @class Game Klasse
 * @brief Basisklasse fuer Logik des Muehlespiels
 * @details In dieser Klasse sind alle Komponenten des Muehlespiels vereinigt.
 * Von  hier wird alles verwaltet, z.B. das Spiel gestartet oder beendet.
 * */
class Game : public QObject {
    Q_OBJECT

    public:
        //fuer GUI:
        friend class UIControl;

        // KONSTRUKTOREN:
        Game();                  ///< Standardkonstruktor
        Game(bool middleOfGame); ///< Konstruktor, der in der in Mitte eines Spiels einsteigen laesst
        ~Game() = default; ///< Defaultdestruktor

        // SPIELSTEUERUNG:
        int start(); ///< Startet das Spiel
        /**
         * @brief Steuert den Spielablauf
         * @details Es werden im Wechsel Spielzuege fuer Server- und Client-Spieler aufgerufen.
         * Waehrend jedem Spielzug werden in den aufgerufenen Methoden die Game-Attribute aktualisiert.
         * Nach jedem Spielzug werden die Muehlen auf dem gesamten Spielfeld aktualisiert.
         * @exception 1 Kein eideutiger Spieler ist am Zug
         * */
        int play();
        int end();   ///< Beendet das Spiel

        /**
         * @brief Fuer den uebergebenen Spieler wird der passende Spielzug ausgewaehlt 
         * und durchgefuehrt
         * @details Es werden jeweils so lange Positionen eingelesen, bis alle eingegebenen
         * Positionen fuer den durchzufuehrenden Spielzug gueltig sind.
         * */
        int findAndPlayMove(Player& playerOnMove);
        int playSetPiece(Player& playerOnMove, Piece destination); //TODO not needed
        int playMakeMove(Player& playerOnMove, Piece pieceToBeMoved, Piece destionation); //TODO not needed
        /**
         * @brief Methode, die Spielstein vom uebergebenen Spieler wegnimmt
         * @details Es werden so lange Spielsteine eingelesen, bis ein zum Wegnehmen
         * gueltiger Spielstein eingegeben wurde.
         * */
        int playTakePiece(Player& playerTakenFrom);

        /**
         * @brief Setzt alle Spielsteine, die nach einem Spiezug nicht mehr Teil einer Muehle sind
         * auf false
         * @details Dazu werden zunaechst alle Muehlen geloescht und mit updateMill alle
         * gueltigen wieder erstellt.
         * */
        void eraseOldMills();
        /**
         * @brief Setzt #Piece::_mill von allen Positionen des Spielbretts auf den aktuellen Wert
         * @details Dazu wird die Methode nach jedem gueltigen Spielzug aufgerufen.
         * Zurueckgegeben wird true, falls im letzten Spielzug eine neue Muehle geschlossen
         * wurde. Falls nicht, dann false.
         * */
        bool updateMill();
        /**
         * @brief Liest so lange Koordinaten ein, bis eine valide Position eingegeben wurde.
         * Gibt einen Spielstein mit den eingegebenen Koordinaten zurueck
         * */
        Piece inputCoordinates();
        /**
         * @brief Ueberprueft, ob Spiel weitergeht
         * */
        bool continueGame();
        

        //ATTRIBUTE:
        Player _playerServer; ///< Spieler, der Server ist
        Player _playerClient; ///< Spieler, der Client ist
        Board _gameBoard; ///< Zum Spiel gehoeriges, immer aktuell gehaltenes Spielfled

        /**
         * @brief currentMoveInfo
         * @details Aufbau Array: {[1. Uebertragene Info], [2. Uebertragene Info], [3. Uebertragene Info],
         *          [4. Uebertragene Info], [5. Uebertragene Info], [isServer (ture or false)]}
         * Die entsprechenden Slots wissen, welche Elemente sie auslesen/veraundern...
         *
         * */
        std::array<quint8, 6> _currentMoveInfo;

        //Gui interface; //TODO

        //Ueberladene Methoden
        int playUe(quint8 direction, quint8 square, quint8 piecesLeftToSet, quint8 closedMill);
        int findAndPlayMove(Player& playerOnMove, Piece destination);

        //Konvertermethoden
        /*static */std::array<quint8, 4> convertPieceToQuint(Piece direction);
        /*static */Piece convertQuintToPiece(quint8 direction, quint8 square);


    public slots:
        //eigenen Zug machen
        /**
         * @brief Wurede, wenn es eine Verbindung gaebe, auf die Antwort des Gegners reagieren (entweder mit
         * Setzzug oder durch neue Eingabe)
         * */
        int setPieceAnsweredSlot(quint8);

        //gegnerischen Zug ueberpruefen
        /**
         * @brief Wurede, wenn es eine Verbindung gaebe, den Setzzug des Gegners ueberpruefen
         * */
        int setPieceControlSlot(quint8 direction, quint8 square, quint8 piecesLeftToSet, quint8 closedMill);

        //Slots, die Netzwerkuebertragung simulieren (wuerden bei Netzwerkverbindung nicht gebraucht)
        /**
         * @brief Weil keine Nezwerkverbindung aufgebaut werden konnte, simuliert dieser Slot, 
         * die Uebertragung im Netzwerk, damit das Spiel tritzdem funktioniert
         * */
        void simulateNetworkSlot(quint8 direction, quint8 square, quint8 piecesLeftToSet, quint8 closedMill);

    signals:
        //eigenen Zug machen
        /**
         * @brief Wurede, wenn es eine Verbindung gaebe, dem Netzwerke sagen, dass ein Spielstein
         * gesetzt wird
         * */
        void setPieceSig(quint8 direction, quint8 square, quint8 piecesLeftToSet, quint8 closedMill);
        //gegnerischen Zug ueberpruefen
        /**
         * @brief Wurede, wenn es eine Verbindung gaebe, der Logik sagen, wie der Gegner dazu steht, dass ein Spielstein
         * gesetzt wird
         * */
        void setPieceAnsweredSig(quint8);

        //Slots, die Netzwerkuebertragung simulieren (wuerden bei Netzwerkverbindung nicht gebraucht)
        /**
         * @brief Simuliert die Netzwerkverbindung im aktuellen Fall ohne Verbindung (wuerden bei
         *  Netzwerkverbindung nicht gebraucht).
         * */
        void simulateNetworkSig(quint8);

    private:
        Board _boardBeforeMove; ///< Spielbrett vor dem aktuellen Spielzug als Vergleich

};
