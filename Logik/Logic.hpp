/**
 * @file Logic.hpp
 * @brief Datei mit den Klassen Piece, Board und Player
 * @author Benedikt Witteler
 * */

#pragma once

#include <string>
#include <array>
#include <iostream>
#include <utility>
#include <algorithm>
#include <set>

/**
 * @class Piece Klasse
 * @brief Klasse zur Beschreibung eines Spielsteins
 * */
class Piece {
    public:
        friend class Player;
        friend class Board;
        friend class Game;

        //ENUMERATIONS:
        enum status : uint8_t{unset = 1, set = 2, taken = 3};
        enum direction : uint8_t{N = 1, NO = 2, O = 3, SO = 4,
                                 S = 5, SW = 6, W = 7, NW = 8};
        enum square : uint8_t{aussen = 1, mitte = 2, innen = 3};
        // KONSTRUKTOREN:
        Piece(); ///< Standardkonstruktor
        /**
         * @brief Konstruktor, mit dem alle Attributwerte individuell initialisiert werden
         * koennen
         * */
        Piece(status statusPlayer, direction directionPlayer, square squarePlayer, bool mill);

        //GETTER & SETTER
        void setDirectionPiece(direction directionToSetTo); ///< Setter
        void setSquarePiece(square squareToSetTo); ///< Setter
        /**
         * @brief Setter
         * @details Gibt zurueck, ob Spielsteinattribut #_mill schon vor Methodenaufruf den
         * Gleichen Wert hatte wie millToSetTo (ture) oder nicht (false)
         * */
        bool setMillPiece(bool millToSetTo);

        //OPERATOREN (fuer Iteratoren)
        bool operator ==(const Piece comparedPiece); ///< Gleichheitsoperator
        /**
         * @brief Schwaecherer Gleichheitsoperator. Prueft nur auf Gleichheit der Koordinaten
         * */
        bool sameCoordinates(const Piece comparedPiece); 

        //KONSOLENMETHODEN:
        std::string stringPiece(); ///< Gibt String mit Piece-Attributen zurueck


    private:
        status _statusPiece; ///< Spielstein ist noch nicht gesetzt, gesetzt oder geschlagen
        /**<
         * @details Attribute #_directionPiece, #_squarePiece und #_mill tragen default-Wert, wenn
         * Spielstein nicht gesetzt ist (#_statusPiece = unset), der falsch sein kann, sodass sich
         * mehrere Spielsteine in #Player::_piecesPlayer an der selben Position befinden
         * */
        direction _directionPiece; ///< Richtungskoordinate des Spielsteins
        square _squarePiece; ///< Koordinate, in welchem Quadrat sich Spielstein befindet
        bool _mill; ///< Spielstein ist Teil einer Muehle (falls true)
};

/**
 * @class Board Klasse
 * @brief Klasse fuer Spielbrett
 * @details Enthaelt ein Array #_muehle, das Nachbarschaftsbeziehungen und Zustaende der Positionen
 * auf dem Spielfeld enthaelt und ein Array #_owner in gleicher Reihenfolge, das angibt, welchem Spieler
 * der Spielstein auf einer Postiton gehoert. \n
 * Allen Spielsteinen ist zusaetzlich zu ihrem Identifierer durch die Koordinaten der Identifier durch
 * ihren Index in #_muehle hinzugefuegt. So sind alle Spielsteine durchnummeriert von 1 bis 24.
 * */
class Board {
    public:
        //ENUMERATIONS:
        enum ownerStatus : uint8_t{unset = 0, server = 1, client = 2};

        //KONSTRUKTOREN:
        Board(); ///< Standardkonstruktor, initialisiert alle Nachbarschaftsbeziehungen

        //GETTER:
        /**
         * @brief Gibt zu einem gegebenen Index das zugehoerige Paar mit Spielstein 
         * (Koordinaten, Status, ...) und Nachbarn-Array aus #_muehle zurueck
         * @param i Positionsindex in #_muehle.
         * */
        std::pair<Piece, std::array<uint8_t, 4>> getPairAtPosition(int i);
        /**
         * @brief Gibt zu einem gegebenen Spielstein das zugehoerige Paar mit 
         * Spielstein (Koordinaten, Status, ...) und Nachbarn-Array aus #_muehle zurueck
         * @param pieceLooking Spielstein, von dem nur die Koordinaten betrachtet werden,
         * zu dem das zugehoerige Element in #_muehle gesucht ist.
         * */
        std::pair<Piece, std::array<uint8_t, 4>> getPairAtPosition(Piece pieceLooking);
        /**
         * @brief Liefert zu einem Spielstein (nur Koordinaten werden betrachtet)
         * den zugehörigen Index in #_muehle
         * */
        int getBoardIndex(Piece indexOf);
        ownerStatus getOwnerOfPiece(Piece pieceLooking); ///< Gibt Besitzer eines Spielsteins zurueck

        //SETTER
        void setGivenPiece(Piece pieceToSet); ///< Setzt Spielstein in #_muehle auf gegebenen Wert
        /**
         * @brief Setzt Besitzter von gegebenem Spielstein auf gegebenen Wert
         * @param pieceToSet Spielstein, dessen Besitzer gesetzt werden soll
         * @param ownerToSetTo Besitzer auf den Spielstein gesetzt werden soll
         * */
        void setGivenOwner(Piece pieceToSet, ownerStatus ownerToSetTo);
        /**
         * @brief Setzt uebergebenen Spielstein im #_muehle und #_owner auf unbesetzten Zustand
         * @details In #_muehle wird der Status des Spielsteins auf #Piece::unset und #Piece::mill auf
         * false gesetzt (Spielstein ist nicht Teil einer Muehle, weil kein Spielstein da ist). In
         * #_owner wird der zugehoerige Index auf #unset gesetzt.
         * */
        void freeGivenPieceAndOwner(Piece pieceToFree);
        /**
         * @brief Setzt Spielsteinattribut #_mill vom Spielstein mit Index idx1 in #_muehle auf 
         * uebergebenen Wert
         * */
        void setPieceMill(int idx1, bool millToSetTo);
        /**
         * @brief Setzt Spielsteinattribut #_mill vom Spielsteinen mit Index idx1, idx3 & idx3
         * in #_muehle auf true
         * */
        void setPieceMill(int idx1, int idx2, int idx3);

        //METHODEN
        /**
         * @brief Gibt zu einem uebergebenen Spielstein die Nachbarn zurueck
         * @details Die Nachbarn werden zurueckgegeben in Form eines Arrays. In diesem Array
         * befinden sich die Indizes, an denen sich die Nachbarn in #_muehle befinden. Sind Indizes = 0,
         * so zeigen sie auf den default-Wert eines Spielsteins und stehen damit fuer keinen Nachbarn.
         * */
        std::array<uint8_t, 4> getNeighbors(Piece neighborsOf);
        /**
         * @brief Gibt std::set<int> zurueck, das die Indizes aller Spielsteine enthaelt, die Teil
         * einer Muehle sind
         * @details Dazu wird auf allen moeglichen Kanten mithilfe von _piecesMakeMill 
         * ueberprueft, ob die dort liedenden Spieler eine Muehle bilden.
         * */
        std::set<int> searchForMill();
        /**
         * @brief Vergleicht, ob die auf  einer Kante liegenden Spielstein alle dem selben Spieler
         * gehoeren und gesetzt sind und somit eine Muehle bilden
         * @details Spielsteiner einer Muehle werden dem by reference uebergebenen 
         * std::set<int> piecesInMill hinzugefuegt
         * */
        void piecesMakeMill(int i1, int i2, int i3, std::set<int> &piecesInMill);

        int numberMills(); ///< Gibt Anzahl der Muehlen auf Feld zurueck

        //KONSOLENMETHODE:
        void printPositionsOfBoard(); ///< Schreibt Spielsteininformaitonen der #_muehle Elemente auf Konsole
        void printInitialBoardVisual(); ///< Schreibt leeres Muehlefeld auf Konsole
        /**
         * @brief Schreibt Muehlefeld mit den in #_muehle gespeicherten Spielsteininformationen auf Konsole
         * @details Dabei ist eine leere Position ein "o", eine vom Player Server besetzte Position eine tuerkise
         * "#" und eine vom Player Client besetztes Position ein rostes "*".
         * */
        void printBoardVisual();
        /**
         * @brief Gibt zu #_muehle-Index zugehoeriges Symbol fuer Konsolenausgabe zurueck
         * */
        std::string giveActualPiece(int idx);
    private:
    /**
     * @brief Array, das Nachbarschaftsbeziehungen und Zustaende der Positionen enthaelt
     * @details Es besteht aus 25 Elementen (Anzahl Positionen + eine default Position = 0)
     * vom Typ "pair", die wie fogt aufgebaut sind:
     * ((Koordinateninformationen in Form eines Piece),(Array der Indizes der maximal vier Nachbarn)).
     * Zur Veranschaulichung: \n
     * std::array<uint8_t, 4> neighbors; -> Array der bis zu vier Nachbarn\n
     * std::pair<Piece, std::array<uint8_t, 4>> coordinates; -> "pair"-Element \n
     * -> Ueber den "pair"-.first Member erhaelt man den Spielstein von einem #_muehle-Element \n
     * -> Ueber den "pair"-.second Member erhaelt man das Nachbarn-Indizes-Array
     * */
    std::array<std::pair<Piece, std::array<uint8_t, 4>>, 25> _muehle;
    /**
     * @brief Array, das Information ueber den Besitzer eines Spielsteins enthaelt
     * @details Array ist so wie #_muehle geordnet und kann deshalb ueber die selben Indizes angesprochen
     * werden
     * */
    std::array<ownerStatus, 25> _owner;

};

/**
 * @class Player Klasse
 * @brief Klasse zur Beschreibung eines Spielers
 * */
class Player {
    public:
        friend class Game;

        //ENUMERATIONS:
        enum phase : uint8_t{Setzphase = 1, Zugphase = 2, Endphase = 3};

        //KONSTRUKTOREN:

        Player(); ///< Standardkonstruktor
        /**
         * @brief Konstruktor mit fast allen Initialisierungen
         * @details Allen Attributen werden Werte uebergeben, ausser #_piecesPlayer.
         * #_piecesPlayer erhaet default-Werte: Jeder Spielstein wird mit Piece::Piece() initialisiert
         * @param name Name, den Spieler tragen soll (...)
         * */
        Player(std::string name, bool beginner, bool color,
               uint8_t countPieces, bool move, phase phasePlayer, bool winner,
               /* _piecesPlayer wird default initialisiert*/
               bool server);

        //SPIELABLAUF: (Veraendern lediglich Player. Ueberpruefungen bezueglich der Spiellogik
        //werden in Game vorgenommen.)

        /**
         * @brief Setzten eines uebergebenen Spielsteins auf by reference uebergebenem Spielbrett
         * @details Nur in Setzphase moeglich.
         * @exception 1 Bereits alle Spielsteine gesetzt
         * @exception 2 Position ist schon besetzt
         * */
        int setPiece(Piece destination, Board& currentBoard);
        /**
         * @brief Bewegung eines uebergebenen Spielsteins auf eine uebergebene Position
         * auf by reference uebergebenem Spielbrett
         * @details Abhaenig von der Spielphase in der sich der Spieler befindet,
         * kann nur um eine Position gerueckt (Zugphase),
         * oder gesprungen werden(Endphase). \n
         * Moegliche Erweiterung: #_piecesPlayer wird nicht angepasst, weil alle
         * Spielsteininformationen in Board::_muehle enthalten sind. Beispielsweise fuer ein
         * Spiel-Log koennte man #_piecesPlayer auch nach der #Setzphase aktuell halten.
         * @exception 1 Spieler ist nicht in Zugphase oder Endphase
         * @exception 2 Zielposition ist schon besetzt
         * @exception 3 Zu ziehender Spielstein ist nicht gesetzt
         * @exception 4 Zielposition ist keine Nachbarposition (wenn Spieler in Zugphase)
         * @exception 5 Zu ziehender Spielstein gehoert nicht zu diesem Spieler
         * */
        int makeMove(Piece pieceToBeMoved, Piece destination, Board &currentBoard);
        /**
         * @brief Schalgen/wegnehmen eines uebergebenen Spielsteins
         * auf by reference uebergebenem Spielbrett
         * @details Diese Methode wird immer von demjenigen Spieler aufgerufen,
         * von dem ein Spielstein weggenommen wird, nicht von dem Spieler der ihn nimmt und auswaehlt.
         * @exception 1 Auf Position wo weggenommen werden soll, kann nichts weggenommen werden,
         * weil dort kein Spielstein liegt
         * @exception 2 Spielstein ist Teil einer Muehle
         * @exception 5 Der Spielstein, der weggenommen werden soll, gehoert nicht zu diesem Spieler
         * */
        int takePiece(Piece piedeToTake, Board& currentBoard);

        // KONSOLENMETHODEN:
        void printPlayer(); ///< Schreibt Playerinformationen auf die Konsole

        //GETTER & SETTER:
        bool getPlayerOnMove(); ///< Getter
        phase getPhasePlayer(); ///< Getter
        void togglePlayerOnMove(); ///< Setter: setzt #_move auf gegenteiligen Wert
        /**
         * @brief Ueberprueft ob Spieler blockiert ist und gibt entsprechend true oder false
         * zurueck
         * */
        bool getCheckPlayerBlocked(Board currentBoard);


        private:
        //GENERELLE SPIELERINFORMATIONEN:
        std::string _name; ///< Spielername
        const bool _beginner;///< Spieler beginnt (true), oder nicht
        const bool _color; ///< Spieler hat Farbe schwarz (true), sonst weiss

        //SPIELABLAUF:
        /**
         * @brief Anzahl der Spielsteine
         * @details Spieler startet mit 0 Steinen. Beim setzten werden die Steine hochgezaehlt
         * bis 9. Danach wird #_countPieces mit jedem Spielsteinverlust um 1 dekrementiert.
         * */
        int _countPieces; ///< Anzahl der besessenen Spielsteine
        int _countSetPieces; ///< Anzahl bereits gesetzter Spielsteine
        /**
         * @brief Spieler ist blockiert (true), oder nicht
         * @details Spieler ist genau dann blockiert, wenn er keine seiner Spielsteine
         * bewegen kann, weil eigene oder gegnerische Steine daneben liegen.
         * (#_blocked == true) fuehrt zur sofortigen Niederlage
         * */
        // bool _blocked;
        bool _move; ///< Spieler ist am Zug (true), oder nicht
        phase _phasePlayer; ///< Phase in der Spieler sich aktuell befindet
        /**
         * @brief Spieler ist Gewinner (true), oder nicht
         * @details Ist waehrend des gesamten Spiels false und wird erst am Ende gesetzt
         * */
        bool _winner;
        /**
         * @brief Array, das alle Informationen ueber Spielsteine des Spielers enthaelt
         * @details (...)
         * */
        std::array<Piece, 9> _piecesPlayer;

        //NETZWERKSPEZIEFISCHES:
        const bool _server; ///< Spieler ist Server(true), sonst Client
            //TODO




};
