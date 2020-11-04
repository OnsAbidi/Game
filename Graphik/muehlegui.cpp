#include "muehlegui.h"
#include "ui_muehlegui.h"
#include "../Logik/Game.hpp"
#include "../Logik/Logic.hpp"

#include <iostream>
#include <string>
#include <time.h>

MuehleGUI::MuehleGUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MuehleGUI)
{

}

MuehleGUI::~MuehleGUI()
{
    delete ui;
}

//verbinden-Slot emittiert host und port
void MuehleGUI::emitHostAndPort() {
    //read port and host, cast them to int then to uint_8
    QString portString = ui->LE_port->text();
    int portInt = portString.toInt();
    uint8_t _port = portInt;
    QString hostString = ui->LE_host->text();
    int hostInt = hostString.toInt();
    uint8_t _host = hostInt;

    emit _host, _port; //zu emittierendes Signal
}

//---------------------------UIControl-----------------------

//Konstruktor
UIControl::UIControl() {
    // Besetze feldarray
        fieldButtonVector[1][1] = MuehleGUI::ui->PB_NNQ1;
        fieldButtonVector[2][1] = MuehleGUI::ui->PB_NNQ2;
        fieldButtonVector[3][1] = MuehleGUI::ui->PB_NNQ3;
        fieldButtonVector[1][2] = MuehleGUI::ui->PB_NOQ1;
        fieldButtonVector[2][2] = MuehleGUI::ui->PB_NOQ2;
        fieldButtonVector[3][2] = MuehleGUI::ui->PB_NOQ3;
        fieldButtonVector[1][3] = MuehleGUI::ui->PB_OOQ1;
        fieldButtonVector[2][3] = MuehleGUI::ui->PB_OOQ2;
        fieldButtonVector[3][3] = MuehleGUI::ui->PB_OOQ3;
        fieldButtonVector[1][4] = MuehleGUI::ui->PB_SOQ1;
        fieldButtonVector[2][4] = MuehleGUI::ui->PB_SOQ2;
        fieldButtonVector[3][4] = MuehleGUI::ui->PB_SOQ3;
        fieldButtonVector[1][5] = MuehleGUI::ui->PB_SSQ1;
        fieldButtonVector[2][5] = MuehleGUI::ui->PB_SSQ2;
        fieldButtonVector[3][5] = MuehleGUI::ui->PB_SSQ3;
        fieldButtonVector[1][6] = MuehleGUI::ui->PB_SWQ1;
        fieldButtonVector[2][6] = MuehleGUI::ui->PB_SWQ2;
        fieldButtonVector[3][6] = MuehleGUI::ui->PB_SWQ3;
        fieldButtonVector[1][7] = MuehleGUI::ui->PB_WWQ1;
        fieldButtonVector[2][7] = MuehleGUI::ui->PB_WWQ2;
        fieldButtonVector[3][7] = MuehleGUI::ui->PB_WWQ3;
        fieldButtonVector[1][8] = MuehleGUI::ui->PB_NWQ1;
        fieldButtonVector[2][8] = MuehleGUI::ui->PB_NWQ2;
        fieldButtonVector[3][9] = MuehleGUI::ui->PB_NWQ3;

        //Connects für inputCoordinates
            for(int i = 1; i<=9; i++) {
                for(int j= 1; j<=4; j++) {
                    connect(MuehleGUI::fieldButtonVector[i][j], &QPushButton::clicked, [&](){emit Game::inputCoordinates(i,j);});
                }
            }

        //connect für Feldfärbung
        connect(&spiel, &Game::emitOwner, &control, &UIControl::colourAllPB);

        //verbinde Client mit Host, rauskommentiert da Netzwerkcode noch nicht da
        connect(MuehleGUI::ui->PB_verbinden, &MuehleGUI::on_PB_verbinden_clicked, &clientName, &Client::clientName.connectToHost());

        //stelle ein ob Server oder nicht
        connect(&MuehleGUI::ui->CB_isServer, &QPushButton::clicked, &control, &setServer);

        //connect zwischen findandplaymove und slot colourfields
        connect(&Game::spiel, Game::emit_board(), &MuehleGUI:, &MuehleGUI::slot_colourFields);
}

//EinfärbeSlot
void UIControl::colourAllPB() {
    std::array<Board::ownerStatus, 25> ownerArray = _owner;
    for (int i = 1; i <=24; i++) {
        if(ownerArray[i] == 0) {
            switch (i) {
             case 1: UIControl::fieldButtonVector[1][1]->setStyleSheet("background-color: grey"); break;
             case 2: UIControl::fieldButtonVector[1][2]->setStyleSheet("background-color: grey"); break;
             case 3: UIControl::fieldButtonVector[1][3]->setStyleSheet("background-color: grey"); break;
             case 4: UIControl::fieldButtonVector[1][4]->setStyleSheet("background-color: grey"); break;
             case 5: UIControl::fieldButtonVector[1][5]->setStyleSheet("background-color: grey"); break;
             case 6: UIControl::fieldButtonVector[1][6]->setStyleSheet("background-color: grey"); break;
             case 7: UIControl::fieldButtonVector[1][7]->setStyleSheet("background-color: grey"); break;
             case 8: UIControl::fieldButtonVector[1][8]->setStyleSheet("background-color: grey"); break;
             case 9: UIControl::fieldButtonVector[2][1]->setStyleSheet("background-color: grey"); break;
             case 10: UIControl::fieldButtonVector[2][2]->setStyleSheet("background-color: grey"); break;
             case 11: UIControl::fieldButtonVector[2][3]->setStyleSheet("background-color: grey"); break;
             case 12: UIControl::fieldButtonVector[2][4]->setStyleSheet("background-color: grey"); break;
             case 13: UIControl::fieldButtonVector[2][5]->setStyleSheet("background-color: grey"); break;
             case 14: UIControl::fieldButtonVector[2][6]->setStyleSheet("background-color: grey"); break;
             case 15: UIControl::fieldButtonVector[2][7]->setStyleSheet("background-color: grey"); break;
             case 16: UIControl::fieldButtonVector[2][8]->setStyleSheet("background-color: grey"); break;
             case 17: UIControl::fieldButtonVector[3][1]->setStyleSheet("background-color: grey"); break;
             case 18: UIControl::fieldButtonVector[3][2]->setStyleSheet("background-color: grey"); break;
             case 19: UIControl::fieldButtonVector[3][3]->setStyleSheet("background-color: grey"); break;
             case 20: UIControl::fieldButtonVector[3][4]->setStyleSheet("background-color: grey"); break;
             case 21: UIControl::fieldButtonVector[3][5]->setStyleSheet("background-color: grey"); break;
             case 22: UIControl::fieldButtonVector[3][6]->setStyleSheet("background-color: grey"); break;
             case 23: UIControl::fieldButtonVector[3][7]->setStyleSheet("background-color: grey"); break;
             case 24: UIControl::fieldButtonVector[3][8]->setStyleSheet("background-color: grey"); break;
            }
        }
        if(ownerArray[i] == 1) {
            switch (i) {
                case 1: UIControl::fieldButtonVector[1][1]->setStyleSheet("background-color: black"); break;
                case 2: UIControl::fieldButtonVector[1][2]->setStyleSheet("background-color: black"); break;
                case 3: UIControl::fieldButtonVector[1][3]->setStyleSheet("background-color: black"); break;
                case 4: UIControl::fieldButtonVector[1][4]->setStyleSheet("background-color: black"); break;
                case 5: UIControl::fieldButtonVector[1][5]->setStyleSheet("background-color: black"); break;
                case 6: UIControl::fieldButtonVector[1][6]->setStyleSheet("background-color: black"); break;
                case 7: UIControl::fieldButtonVector[1][7]->setStyleSheet("background-color: black"); break;
                case 8: UIControl::fieldButtonVector[1][8]->setStyleSheet("background-color: black"); break;
                case 9: UIControl::fieldButtonVector[2][1]->setStyleSheet("background-color: black"); break;
                case 10: UIControl::fieldButtonVector[2][2]->setStyleSheet("background-color: black"); break;
                case 11: UIControl::fieldButtonVector[2][3]->setStyleSheet("background-color: black"); break;
                case 12: UIControl::fieldButtonVector[2][4]->setStyleSheet("background-color: black"); break;
                case 13: UIControl::fieldButtonVector[2][5]->setStyleSheet("background-color: black"); break;
                case 14: UIControl::fieldButtonVector[2][6]->setStyleSheet("background-color: black"); break;
                case 15: UIControl::fieldButtonVector[2][7]->setStyleSheet("background-color: black"); break;
                case 16: UIControl::fieldButtonVector[2][8]->setStyleSheet("background-color: black"); break;
                case 17: UIControl::fieldButtonVector[3][1]->setStyleSheet("background-color: black"); break;
                case 18: UIControl::fieldButtonVector[3][2]->setStyleSheet("background-color: black"); break;
                case 19: UIControl::fieldButtonVector[3][3]->setStyleSheet("background-color: black"); break;
                case 20: UIControl::fieldButtonVector[3][4]->setStyleSheet("background-color: black"); break;
                case 21: UIControl::fieldButtonVector[3][5]->setStyleSheet("background-color: black"); break;
                case 22: UIControl::fieldButtonVector[3][6]->setStyleSheet("background-color: black"); break;
                case 23: UIControl::fieldButtonVector[3][7]->setStyleSheet("background-color: black"); break;
                case 24: UIControl::fieldButtonVector[3][8]->setStyleSheet("background-color: black"); break;
            }
        }
        if(ownerArray[i] == 2) {
            switch (i) {
                case 1: UIControl::fieldButtonVector[1][1]->setStyleSheet("background-color: white"); break;
                case 2: UIControl::fieldButtonVector[1][2]->setStyleSheet("background-color: white"); break;
                case 3: UIControl::fieldButtonVector[1][3]->setStyleSheet("background-color: white"); break;
                case 4: UIControl::fieldButtonVector[1][4]->setStyleSheet("background-color: white"); break;
                case 5: UIControl::fieldButtonVector[1][5]->setStyleSheet("background-color: white"); break;
                case 6: UIControl::fieldButtonVector[1][6]->setStyleSheet("background-color: white"); break;
                case 7: UIControl::fieldButtonVector[1][7]->setStyleSheet("background-color: white"); break;
                case 8: UIControl::fieldButtonVector[1][8]->setStyleSheet("background-color: white"); break;
                case 9: UIControl::fieldButtonVector[2][1]->setStyleSheet("background-color: white"); break;
                case 10: UIControl::fieldButtonVector[2][2]->setStyleSheet("background-color: white"); break;
                case 11: UIControl::fieldButtonVector[2][3]->setStyleSheet("background-color: white"); break;
                case 12: UIControl::fieldButtonVector[2][4]->setStyleSheet("background-color: white"); break;
                case 13: UIControl::fieldButtonVector[2][5]->setStyleSheet("background-color: white"); break;
                case 14: UIControl::fieldButtonVector[2][6]->setStyleSheet("background-color: white"); break;
                case 15: UIControl::fieldButtonVector[2][7]->setStyleSheet("background-color: white"); break;
                case 16: UIControl::fieldButtonVector[2][8]->setStyleSheet("background-color: white"); break;
                case 17: UIControl::fieldButtonVector[3][1]->setStyleSheet("background-color: white"); break;
                case 18: UIControl::fieldButtonVector[3][2]->setStyleSheet("background-color: white"); break;
                case 19: UIControl::fieldButtonVector[3][3]->setStyleSheet("background-color: white"); break;
                case 20: UIControl::fieldButtonVector[3][4]->setStyleSheet("background-color: white"); break;
                case 21: UIControl::fieldButtonVector[3][5]->setStyleSheet("background-color: white"); break;
                case 22: UIControl::fieldButtonVector[3][6]->setStyleSheet("background-color: white"); break;
                case 23: UIControl::fieldButtonVector[3][7]->setStyleSheet("background-color: white"); break;
                case 24: UIControl::fieldButtonVector[3][8]->setStyleSheet("background-color: white"); break;
            }
        }
    }
}

//konnte aus Zeitmangel nicht mehr implementiert werden
void UIControl::setServer() {


}
