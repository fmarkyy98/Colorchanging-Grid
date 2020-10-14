#ifndef COLORCHANGINGGRID_H
#define COLORCHANGINGGRID_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QGridLayout>
#include "colorchangingmodell.h"

class ColorChangingGrid : public QWidget
{
    Q_OBJECT

public:
    ColorChangingGrid(QWidget *parent = nullptr);
    ~ColorChangingGrid();

private slots:
    void on_smallButtonClicked();
    void on_mediumButtonClicked();
    void on_bigButtonClicked();
    void on_colorButtonClicked();
    void on_refreshTable();
    void on_refreshElapsedTime();
    void on_gameOver();

private:
    const int sizeButtonsCount;
    QPushButton** sizeButtons;
    QVector<QPushButton*> colorButtonVector;
    QLabel* time_label;
    QLabel* difficoultyText_label;
    QSpinBox* difficoultyValue_spinBox;
    ColorChangingModell* modell;
    QGridLayout* colorButton_gLayout;

    void newGame(Size size = Medium);
    void setupTable(Size size);
    void deleteTable();
};
#endif // COLORCHANGINGGRID_H
