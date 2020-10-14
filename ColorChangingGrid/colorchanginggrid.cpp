#include "colorchanginggrid.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

ColorChangingGrid::ColorChangingGrid(QWidget *parent): QWidget(parent), sizeButtonsCount(3)
{
    QHBoxLayout* sizeButtons_hLayout = new QHBoxLayout();
    sizeButtons = new QPushButton*[sizeButtonsCount];
    for(int i = 0; i < sizeButtonsCount; ++i)
    {
        sizeButtons[i] = new QPushButton(QString::number((i + 1) * 4) + "x" + QString::number((i + 1) * 4));
        sizeButtons_hLayout->addWidget(sizeButtons[i]);
    }

    QHBoxLayout* timeDiff_hLayout = new QHBoxLayout();
    time_label = new QLabel("Time: 0 sec(s)");
    difficoultyText_label = new QLabel("Difficoulty:");
    difficoultyValue_spinBox = new QSpinBox();
    difficoultyValue_spinBox->setMinimum(1);
    difficoultyValue_spinBox->setMaximum(3);
    timeDiff_hLayout->addWidget(time_label);
    timeDiff_hLayout->addWidget(difficoultyText_label);
    timeDiff_hLayout->addWidget(difficoultyValue_spinBox);

    colorButton_gLayout = new QGridLayout();

    QVBoxLayout* main_vLayout = new QVBoxLayout();
    main_vLayout->addLayout(sizeButtons_hLayout);
    main_vLayout->addLayout(colorButton_gLayout);
    main_vLayout->addLayout(timeDiff_hLayout);
    this->setLayout(main_vLayout);



    this->modell = new ColorChangingModell();
    connect(this->modell, SIGNAL(refreshTable()),       this, SLOT(on_refreshTable()));
    connect(this->modell, SIGNAL(refreshElapsedTime()), this, SLOT(on_refreshElapsedTime()));
    connect(this->modell, SIGNAL(gameOver()),           this, SLOT(on_gameOver()));
    connect(this->sizeButtons[0], SIGNAL(clicked()), this, SLOT(on_smallButtonClicked()));
    connect(this->sizeButtons[1], SIGNAL(clicked()), this, SLOT(on_mediumButtonClicked()));
    connect(this->sizeButtons[2], SIGNAL(clicked()), this, SLOT(on_bigButtonClicked()));
    newGame();
}

ColorChangingGrid::~ColorChangingGrid()
{
}

void ColorChangingGrid::newGame(Size size)
{
    /*
if(size != this->modell->getSize())
    {
    */
    this->deleteTable();
    this->setupTable(size);
    int diffID = difficoultyValue_spinBox->value();
    Difficulty diff = (Difficulty)(diffID == 1 ? Easy : diffID == 2 ? Medium : Hard);
    this->modell->newGame(size, diff);
    //}
}

void ColorChangingGrid::setupTable(Size size)
{
    for(int i = 0; i < size; ++i)
        for(int j = 0; j < size; ++j)
        {
            QPushButton* curr = new QPushButton();
            colorButtonVector.push_back(curr);
            colorButton_gLayout->addWidget(curr, i, j);
            connect(curr, SIGNAL(clicked()), this, SLOT(on_colorButtonClicked()));
        }
}

void ColorChangingGrid::deleteTable()
{
    for(QPushButton* item : colorButtonVector)
        delete item;
    colorButtonVector.clear();
}


void ColorChangingGrid::on_smallButtonClicked()
{
    newGame(Small);
}

void ColorChangingGrid::on_mediumButtonClicked()
{
    newGame(Medium);
}

void ColorChangingGrid::on_bigButtonClicked()
{
    newGame(Big);
}

void ColorChangingGrid::on_colorButtonClicked()
{
    QPushButton* senderButton = (QPushButton*)sender();
    int index = colorButtonVector.indexOf(senderButton);
    int x = index / this->modell->getSize();
    int y = index % this->modell->getSize();
    this->modell->oneStep(x, y);
}

void ColorChangingGrid::on_refreshTable()
{
    Color** table = this->modell->getTable();
    int n = this->modell->getSize();
    for(int i = 0; i < n * n; ++i)
        switch (table[i / n][i % n])
        {
        case Red:
            colorButtonVector[i]->setStyleSheet("background-color:red;");
            break;
        case Yelow:
            colorButtonVector[i]->setStyleSheet("background-color:yellow;");
            break;
        case Green:
            colorButtonVector[i]->setStyleSheet("background-color:green;");
            break;
        case Blue:
            colorButtonVector[i]->setStyleSheet("background-color:blue;");
            break;
        default:
            break;
        }
}

void ColorChangingGrid::on_refreshElapsedTime()
{
    this->time_label->setText("Time: " + QString::number(this->modell->GetElapsedTime()) + " sec(s)");
}

void ColorChangingGrid::on_gameOver()
{
    QMessageBox* msg = new QMessageBox();
    msg->setText("Nyertél");
    msg->show();
    newGame();
}
