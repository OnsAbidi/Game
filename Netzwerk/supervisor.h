
/**
 * @file Supervisor.h
 * @brief Datei mit der Klasse Supervisor
 * @details Fuegt verschiedne Aufagabenbereiche zusammen. Hier UNBEDINGT auch die Kommentare in
 * supervisor.cpp anschauen, weil das alles connects sind,
 * diese so auskommentiert sind, dass sie nicht im Doxyfile erscheinen (was schliesslich verwirren wuerde).
 * @author Abidi Ons
 * */

#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include <QObject>
#include"client.h"
#include "server.h"
#include "../Logik/Game.hpp"

class Supervisor : public QObject
{
    Q_OBJECT
public:
    explicit Supervisor(QObject *parent = nullptr);



    Server _physServer;
    Client _physClient;
    Game _spiel;



//Verknuepfe Signals und Slots zwischen Logic und Netzwerk:
//Weil noch keine Netzwerkverbidung zwischen Server und Client augebaut wurde,
//werden diese Connects in der altuellen Version nicht benutzt. Sie wuerden sonst aber
//genau ihren Zweck erfuellen
//public slots:
//   void ServerwillStart () ;
//   void clientwillStart () ;



};

#endif // SUPERVISOR_H
