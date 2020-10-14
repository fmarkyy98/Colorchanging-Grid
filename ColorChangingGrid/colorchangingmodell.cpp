#include "colorchangingmodell.h"



ColorChangingModell::ColorChangingModell(QObject *parent) : QObject(parent), differentColoursCount(4)
{
    this->size = Medium;
    qsrand(QTime::currentTime().msec());
    this->timer = new QTimer();
    connect(this->timer, SIGNAL(timeout()), this, SLOT(on_tick()));

}

void ColorChangingModell::newGame(const Size size, const Difficulty diff)
{
    this->size = size;
    this->diff = diff;
    table = new Color*[this->size];
    for(int i = 0; i < this->size; ++i)
    {
        table[i] = new Color[this->size];
        for(int j = 0; j < this->size; ++j)
        {
            table[i][j] = Red;
        }
    }
    for(int i = 0; i < this->size; ++i)
        coloringNeighboringCells(qrand() % size, qrand() % size);

    this->clicks = 0;
    this->elapsedTime = 0;
    this->timer->start(1000);
    emit refreshTable();
    emit refreshElapsedTime();
}

void ColorChangingModell::coloringNeighboringCells(const int x, const int y)
{
    for(int i = x - 1; i <= x + 1; ++i)
        for(int j = y - 1; j <= y + 1; ++j)
            if(0 <= i && i < this->size && 0 <= j && j < this->size)
                this->table[i][j] = (Color)((this->table[i][j] + 1) % differentColoursCount);
}

void ColorChangingModell::oneStep(const int x, const int y)
{
    coloringNeighboringCells(x, y);
    ++clicks;
    elapsedTime += 10;
    if(diff != 0 && clicks % diff == 0)
        coloringNeighboringCells(qrand() % size, qrand() % size);
    emit refreshTable();
    emit refreshElapsedTime();
    if(isGameOver())
        emit gameOver();
}

bool ColorChangingModell::isGameOver() const
{
    for(int i = 0; i < size; ++i)
        for(int j = 0; j < size; ++j)
            if(table[0][0] != table[i][j])
                return false;
    return true;
}

void ColorChangingModell::on_tick()
{
    ++elapsedTime;
    emit refreshElapsedTime();
}
