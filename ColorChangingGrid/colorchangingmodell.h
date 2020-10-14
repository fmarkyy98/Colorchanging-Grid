#ifndef COLORCHANGINGMODELL_H
#define COLORCHANGINGMODELL_H

#include <QObject>
#include <QTime>
#include <QTimer>
#include "enums.h"

class ColorChangingModell : public QObject
{
    Q_OBJECT
public:
    Size getSize() const { return size; }
    Color** getTable() const { return table; }
    int GetElapsedTime() const { return elapsedTime; }

    explicit ColorChangingModell(QObject *parent = nullptr);

    void newGame(const Size size = Medium, const Difficulty diff = Easy);
    void oneStep(const int x, const int y);
    bool isGameOver() const;

signals:
    void refreshTable();
    void refreshElapsedTime();
    void gameOver();

private slots:
    void on_tick();

private:
    const int differentColoursCount;

    Color** table;
    Size size;
    int elapsedTime;
    Difficulty diff;
    int clicks;
    QTimer* timer;

    void coloringNeighboringCells(const int x, const int y);

};

#endif // COLORCHANGINGMODELL_H
