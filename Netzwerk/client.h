/**
 * @file Client.h
 * @brief Datei mit der Klasse Client
 * @author Abidi Ons
 * */


#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QDebug>
#include<QTcpServer>
#include<QTcpSocket>
#include<QVector>
#include<QByteArray>
#include<QDataStream>
#include<QAbstractSocket>
#include<QMetaEnum>




class Client: public QObject
{
    Q_OBJECT
public:
    //Konstruktor
    explicit Client(QObject *parent = nullptr);

signals:
    void AntwortAufSpielbeginn(quint8);
    void Setzen(quint8,quint8,quint8,quint8 );
    void Ziehen(quint8,quint8,quint8,quint8);
    void Springen(quint8,quint8,quint8,quint8,quint8);
    void entfernen(quint8,quint8);
    void Startbrett();
    void Test(QString);

public slots:
      /**
            * @brief Client::connectToHost
            *Bauet Verbindung zum Server
            * @param hostName und port , die zusammenverbunden sein sollen
     * */
    void connectToHost(const QString &hostName,quint16 port);

    /**
          * @brief Client::disconnect
          * Schließt die Socket-Verbindung und gibt alle zugeordneten Ressourcen frei

   * */

    void disconnect();

    ///Verbindung wurde hergestellt
    void connected();



    void disconnected() ;



    /**
     * @brief Client::error
     * Ruft die Fehler auf
     * @param socketError
     *
     */
    void error(QAbstractSocket::SocketError socketError);

    /**
     * @brief Client::stateChanged
     * @param socketState Zeigt die Connectionsschritte
     */
    void stateChanged(QAbstractSocket::SocketState socketState);

    /**
     * @brief Client::readyRead
     * liest die Daten von dem Server und schickt sie an den Logik
     * Liest den Signal von dem Server , nimmt die lange und die cmd raus , Überpüft um welchen Art es handelt
     * schickt ein Signal an den Logik .
     */

    void readyRead();


    /**
    * @brief Client::write
    * @param vector ist ein Signal von dem Logik ,der zu dem server geschickt wird
    */
    void write(QVector<quint8>);
    void WriteDataClient (QVector<quint8>);

private:
    QTcpSocket socket ;
    QDataStream inOutStream;
    quint8 GruppenNummer = 0x02;
    QVector<quint8> vec;



};
#endif // CLIENT_H
