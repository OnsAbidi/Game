#include "server.h"


Server::Server(QObject *parent) : QObject(parent)
{
   connect(&server,&QTcpServer::newConnection,this, &Server::newConnection) ;
   qDebug() << __func__;

}

void Server::Start(quint16 port)
{
  server.listen(QHostAddress::Any,port) ;
  emit Startbrett();

}

void Server::quit()
{
    server.close();

}

void Server::newConnection()
{
  socket = server.nextPendingConnection();
  ///<bearbeitet die nächste Verbindung
  inOutStream.setDevice(socket);

//  connect(socket,&QTcpSocket::disconnected,this,&Server::disconnected);

  connect(socket,&QTcpSocket::readyRead,this,&Server::readyRead);
  qDebug()<<inOutStream.device() ;

  write(v);
  server.close();


}




void Server::readyRead ()
{
    quint8 cmd, length,Gruppennummerop,HimmelRchtgNeuPos,QuadratNeuPos,ZahlNochZuStehendeSteiene
            ,Muehle,HimmelRchtgAktPos,QuadratAktPos,Status,HimmelRcht,Quadrat,ZahlEntfernterSteine;

    inOutStream >>cmd;
    inOutStream >>length;

    qDebug() <<"server received:"<< (int) cmd << " , " << (int) length ;


     switch (cmd) {
    case 0x02:
         inOutStream >> Gruppennummerop ;
         qDebug() << Gruppennummerop;
         emit GruppennummerderGegner(Gruppennummerop);
        break;


     case 0x10:
         inOutStream >> HimmelRchtgNeuPos;
         inOutStream >> QuadratNeuPos;
         inOutStream >> ZahlNochZuStehendeSteiene ;
         inOutStream >> Muehle;
         switch (Muehle){
         case 0x00:
             inOutStream << "nein";
         case 0x01:
             inOutStream << "Ja";
         }
             emit Setzen(HimmelRchtgNeuPos,QuadratNeuPos,ZahlNochZuStehendeSteiene,Muehle);
     case 0x11:
         inOutStream >> HimmelRchtgAktPos;
         inOutStream >> QuadratAktPos;
         inOutStream >> HimmelRchtgNeuPos ;
         inOutStream >> Muehle;
         switch (Muehle){
         case 0x00:
             inOutStream << "nein";
         case 0x01:
             inOutStream << "Ja";
         }

     emit Ziehen(HimmelRchtgAktPos,QuadratAktPos,HimmelRchtgNeuPos,Muehle);

     case 0x12:
         inOutStream >> HimmelRchtgAktPos;
         inOutStream >> QuadratAktPos;
         inOutStream >> HimmelRchtgNeuPos ;
         inOutStream >> QuadratNeuPos;
         inOutStream >> Muehle;
         switch (Muehle){
         case 0x00:
             qDebug() << "nein";
         case 0x01:
              qDebug() << "Ja";
         }

     emit Springen(HimmelRchtgAktPos,QuadratAktPos,HimmelRchtgNeuPos,QuadratNeuPos,Muehle);
     case 0x13:
         inOutStream >> Status ;
         switch (Status) {
         case 0x00:
              qDebug() << "Ok, Ende des Zuges";
                emit Test("Ok, Ende des Zuges");

         case 0x01:
              qDebug() << "Ok, Muehle geschlossen,Warten auf oder zu entfernenden Spielstein";
                emit Test( "Ok, Muehle geschlossen,Warten auf oder zu entfernenden Spielstein");


         case 0x10:
              qDebug() << "Fehler, kein eigener Spielstein an der aktuellen Position";
             emit Test("Fehler, kein eigener Spielstein an der aktuellen Position");
              socket->disconnectFromHost();

         case 0x11:
              qDebug() << "Fehler, Zielposition bereits belegt";
               emit Test("Fehler, Zielposition bereits belegt");
              socket->disconnectFromHost();

         case 0x12:
              qDebug() << "Fehler, Zug nicht erlaubt";
              emit Test("Fehler, Zug nicht erlaubt");
              socket->disconnectFromHost();

             break;
         default:
               qDebug() << "Fehler, nicht an der Reihe";
                emit Test("Fehler, nicht an der Reihe");
               socket->disconnectFromHost();

             break;
         }

     case 0x20:
         inOutStream >> HimmelRcht;
         inOutStream >> Quadrat;
         emit entfernen(HimmelRcht,Quadrat);
     case 0x21:
         inOutStream >> Status ;
         switch (Status) {
         case 0x00:
              qDebug() << "Okay, Ende des Zuges";
              emit Test("Okay, Ende des Zuges");
             break;
         case 0x01:
              qDebug() << "Okay, Gegner hat gewonnen, Spielende";
              emit Test( "Okay, Gegner hat gewonnen, Spielende");
             break;
         case 0x10:
              qDebug() << "Fehler, Stein kann nicht aus geschlossener Muhle entfernt werden";
              emit Test("Fehler, Stein kann nicht aus geschlossener Muhle entfernt werden");
             socket->disconnectFromHost();
             break;
         case 0x11:
              qDebug() << "Fehler, kein passender Stein  an den Zielkoordinaten";
              emit Test("Fehler, kein passender Stein  an den Zielkoordinaten");
              socket->disconnectFromHost();

             break;
         case 0x12:
              qDebug() << "Kein Grund fur das Entfernen eines  gegnerischen Steines vorhanden";
              emit Test( "Kein Grund fur das Entfernen eines  gegnerischen Steines vorhanden");


             break;

         default:
              qDebug() << "Not implemented";
              emit Test("Not implemented");

             break;
         }

     default:  qDebug() << "Not implemented";
         emit Test("Not implemented");

         break;
     inOutStream >> ZahlEntfernterSteine;
     }

 }


void Server::write(QVector<quint8> vector)
    {
    qDebug() << "Server::" << __func__;
       qDebug() << "\tStreamDevice: " << inOutStream.device();
       qDebug() << "\tsocket: " << ((socket == nullptr)? "is nullptr" : "is not nullptr");
        for (quint8 i : vector)
            inOutStream << i;
    }

void Server::writen(QVector<quint8> v)
{
    for ( auto i : v )
            v.push_back(i) ;
}



