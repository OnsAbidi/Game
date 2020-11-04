/**
 * @file Server.h
 * @brief Datei mit der Klasse Server
 * @author Abidi Ons
 * */


#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QDebug>
#include<QTcpServer>
#include<QTcpSocket>
#include<QVector>
#include<QByteArray>
#include<QDataStream>
#include<QAbstractSocket>


class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

signals:
    void Setzen(quint8,quint8,quint8,quint8 );
    void Ziehen(quint8,quint8,quint8,quint8);
    void Springen(quint8,quint8,quint8,quint8,quint8);
    void entfernen(quint8,quint8);
    void Startbrett();
    void Test(QString);
    void GruppennummerderGegner(quint8);

public slots:
    void Start(quint16);


    /**
    * @brief Server::quit
    * Schließt den Server
    * Der Server wartet nicht mehr auf eingehende Verbindungen
    */
    void quit ();


    void newConnection();


//    void disconnected();

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
    void writen(QVector<quint8>);

private:
    QTcpServer server;
    QTcpSocket *socket =0;
    QVector<quint8> v;
    QDataStream inOutStream;
    quint8 GruppenNummer = 0x02;

};

#endif // SERVER_H
