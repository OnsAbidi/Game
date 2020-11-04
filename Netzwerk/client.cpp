#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{
    connect(&socket,&QTcpSocket::connected,this, &Client::connected) ;
    connect(&socket,&QTcpSocket::disconnected,this, &Client::disconnected) ;
    connect(&socket,&QTcpSocket::readyRead,this, &Client::readyRead) ;
    connect(&socket,&QTcpSocket::stateChanged,this, &Client::stateChanged) ;


    connect(&socket,QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),this,&Client::error);

    qDebug() << __func__;
     qDebug() << "\t" << &socket;
}

void Client::connectToHost(const QString &hostName,quint16 port)
{
    qDebug() << __func__ << " with " << hostName << " on port " <<
    QString::number(port);
     qDebug() << "\t" << &socket;

    if(socket.isOpen()) disconnect();
    socket.connectToHost(hostName,port);
}

void Client::disconnect()
{
    socket.close();
}

void Client::connected()
{
    qDebug() << "Client : Connected!";

    emit Startbrett();
    inOutStream.setDevice(&socket);

    qDebug() << __func__;
    qDebug() << "\t" << &socket;


}

void Client::disconnected()
{
     qDebug() << "Disconnected";

}



void Client::error(QAbstractSocket::SocketError socketError)
{
    qDebug() << "Error:" << socketError << "  " << socket.errorString();

}



void Client::stateChanged(QAbstractSocket::SocketState socketstate){
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState>();

    qDebug() << "Client State: " << metaEnum.valueToKey(socketstate);
}




void Client::readyRead()
{
    quint8 cmd, length,beginnender,GruppenNummerderGegner,
            HimmelRchtgNeuPos,QuadratNeuPos,ZahlNochZuStehendeSteiene
            ,Muehle,HimmelRchtgAktPos,QuadratAktPos,Status
            ,HimmelRcht,Quadrat,ZahlEntfernterSteine;
    inOutStream >>cmd;
    inOutStream >>length;
    qDebug() <<"client received: "<< cmd << length ;


    switch (cmd) {
    case 0x01:
        inOutStream >> beginnender;
        inOutStream >> GruppenNummerderGegner;
        qDebug() << beginnender << GruppenNummerderGegner;
       emit AntwortAufSpielbeginn(beginnender);
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
             socket.disconnectFromHost();

        case 0x11:
             qDebug() << "Fehler, Zielposition bereits belegt";
              emit Test("Fehler, Zielposition bereits belegt");
             socket.disconnectFromHost();

        case 0x12:
             qDebug() << "Fehler, Zug nicht erlaubt";
             emit Test("Fehler, Zug nicht erlaubt");
             socket.disconnectFromHost();

            break;
        default:
              qDebug() << "Fehler, nicht an der Reihe";
               emit Test("Fehler, nicht an der Reihe");
              socket.disconnectFromHost();

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
            socket.disconnectFromHost();
            break;
        case 0x11:
             qDebug() << "Fehler, kein passender Stein  an den Zielkoordinaten";
             emit Test("Fehler, kein passender Stein  an den Zielkoordinaten");
             socket.disconnectFromHost();

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



void Client::write(QVector<quint8> vector)

{
    qDebug() << "Client::" << __func__;
        qDebug() << "\t" << &socket;
        qDebug() << "\t" << inOutStream.device();
    for(quint8 i : vector)
        inOutStream << i;
}

void Client::WriteDataClient(QVector<quint8> vecData)
{
    for (auto i : vecData)
        vec.push_back(i);
}
