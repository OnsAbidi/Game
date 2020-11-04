#include "supervisor.h"





Supervisor::Supervisor(QObject *parent) : QObject(parent), _physServer(), _physClient(), _spiel()
{
//    Game *game= new Game;
//    Server *server = new Server();
//    Client *client = new Client();

    //Ersatzconnects um zum Beispiel beim Spielzug "Stein setzten" die implementieren Signale
    //und Slots zu verwenden
    connect (&_spiel,&Game::setPieceSig, &_spiel, &Game::simulateNetworkSlot);
    connect(&_spiel, &Game::simulateNetworkSig, &_spiel, &Game::setPieceAnsweredSlot);

}




//Verknuepfe Signals und Slots zwischen Logic und Netzwerk:
//Weil noch keine Netzwerkverbidung zwischen Server und Client augebaut wurde,
//werden diese Connects in der altuellen Version nicht benutzt. Sie wuerden sonst aber
//genau ihren Zweck erfuellen

///Server wird starten

//void Supervisor::ServerwillStart ()
//{


//    connect (&_spiel,&Game::setPieceSig, &_physServer, &Server::readyRead);
//    connect(&_physServer, &Server::Setzen, &_physClient, &Client::readyRead);
//    connect(&_physClient, &Client::Setzen, &_spiel, &Game::setPieceControlSlot);
//  connect(&_spiel, &Game::setPieceAnsweredSig, &_physClient, &Client::write);
//  connect(&_physClient, &Client::Test, &_physServer, &Server::readyRead);
//  connect(&_physServer, &Server::Test, &_spiel, &Game::setPieceAnsweredSlot);






//connect (&_spiel,&Game::makeMoveStepSig, &_physServer, &Server::readyRead);
//connect(&_physServer, &Server::Ziehen, &_physClient, &Client::readyRead);
//connect(&_physClient, &Client::Ziehen, &_spiel, &Game::makeMoveStepControlSlot);
//connect(&_spiel, &Game::makeMoveStepAnsweredSig, &_physClient, &Client::write);
//connect(&_physClient, &Client::Test, &_physServer, &Server::readyRead);
//connect(&_physServer, &Server::Test, &_spiel, &Game::makeMoveStepAnsweredSlot);





//connect (&_spiel,&Game::makeMoveJumpSig, &_physServer, &Server::readyRead);
//connect(&_physServer, &Server::Springen, &_physClient, &Client::readyRead);
//connect(&_physClient, &Client::Springen, &_spiel, &Game::makeMoveJumpControlSlot);
//connect(&_spiel, &Game::makeMoveJumpAnsweredSig, &_physClient, &Client::write);
//connect(&_physClient, &Client::Test, &_physServer, &Server::readyRead);
//connect(&_physServer, &Server::Test, &_spiel, &Game::makeMoveJumpAnsweredSlot);




//connect (&_spiel,&Game::takePieceSig, &_physServer, &Server::readyRead);
//connect(&_physServer, &Server::entfernen, &_physClient, &Client::readyRead);
//connect(&_physClient, &Client::entfernen, &_spiel, &Game::takePieceControlSlot);
//connect(&_spiel, &Game::takePieceAnsweredSig, &_physClient, &Client::write);
//connect(&_physClient, &Client::Test, &_physServer, &Server::readyRead);
//connect(&_physServer, &Server::Test, &_spiel, &Game::takePieceAnsweredSlot);

//}


///Client wird starten

//void Supervisor::clientwillStart ()
//{

//connect(&_spiel,&Game::setPieceSig, &_physClient, &Server::readyRead);
//connect(&_physClient, &Client::Setzen, &_physServer, &Server::readyRead);
//connect(&_physServer, &Server::Setzen, &_spiel, &Game::setPieceControlSlot);
//connect(&_spiel, &Game::setPieceAnsweredSig, &_physServer, &Server::write);
//connect(&_physServer, &Server::Test, &_physClient, &Client::readyRead);
//connect(&_physClient, &Client::Test, &_spiel, &Game::setPieceAnsweredSlot);






//connect (&_spiel,&Game::makeMoveStepSig, &_physClient, &Server::readyRead);
//connect(&_physClient, &Client::Ziehen, &_physServer, &Server::readyRead);
//connect(&_physServer, &Server::Ziehen, &_spiel, &Game::makeMoveStepControlSlot);
//connect(&_spiel, &Game::makeMoveStepAnsweredSig, &_physServer, &Server::write);
//connect(&_physServer, &Server::Test, &_physClient, &Client::readyRead);
//connect(&_physClient, &Client::Test, &_spiel, &Game::makeMoveStepAnsweredSlot);







//connect (&_spiel,&Game::makeMoveJumpSig, &_physClient, &Server::readyRead);
//connect(&_physClient, &Client::Springen, &_physServer, &Server::readyRead);
//connect(&_physServer, &Server::Springen, &_spiel, &Game::makeMoveJumpControlSlot);
//connect(&_spiel._playerServer, &Game::makeMoveJumpAnsweredSig, &_physServer, &Server::write);
//connect(&_physServer, &Server::Test, &_physClient, &Client::readyRead);
//connect(&_physClient, &Client::Test, &_spiel, &Game::makeMoveJumpAnsweredSlot);




//connect (&_spiel,&Game::takePieceSig, &_physClient, &Server::readyRead);
//connect(&_physClient, &Client::entfernen, &_physServer, &Server::readyRead);
//connect(&_physServer, &Server::entfernen, &_spiel, &Game::takePieceControlSlot);
//connect(&_spiel, &Game::takePieceAnsweredSig, &_physServer, &Server::write);
//connect(&_physServer, &Server::Test, &_physClient, &Client::readyRead);
//connect(&_physClient, &Client::Test, &_spiel, &Game::takePieceAnsweredSlot);
//}















