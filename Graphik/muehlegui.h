#ifndef MUEHLEGUI_H
#define MUEHLEGUI_H

#include <QObject>
#include <QMainWindow>
#include <array>
#include <QPushButton>

#include "../Netzwerk/supervisor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MuehleGUI; }
QT_END_NAMESPACE


/// @brief Klasse für das MainWindow
class MuehleGUI : public QMainWindow
{
    Q_OBJECT

public:
    /// @brief Konstruktor
    MuehleGUI(QWidget *parent = nullptr);
    /// @brief Destruktor
    ~MuehleGUI();
public slots:
    /// @brief Slot zur Emittierung von Port und Host an Netzwerk
    void emitHostAndPort();


private:

    Ui::MuehleGUI *ui;
};

/// @brief separate Klasse für Slots zur Interaktion mit Logik und Netzwerk
class UIControl : public QObject {
    Q_OBJECT
public:
    /// @brief Konstruktor
    UIControl();
    /// @brief Destruktor
    ~UIControl();

    //Attribute

    /// @brief direktes Mapping auf die enums der Logik, 0ter eintrag wird ignoriert
    std::array<std::array<QPushButton*,9>,4> fieldButtonVector;


signals:
    /// @brief Emittiert das Array mit dem die Besetzungszustände des Feldes gespeichert werden
    void emitOwnerArray(std::array<Board::ownerStatus, 25>);

public slots:
    /// @brief Setzt Spieler auf Server
    void setServer();

    /// @brief Färbt auf Basis des übergebenen Arrays die Spielsteine der GUI ein. Wird nach jedem Zug aufgerufen.
    void colourAllPB();
};

#endif // MUEHLEGUI_H
