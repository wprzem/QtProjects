#include "notepad.h"
#include "ui_notepad.h"
#include <QKeyEvent>

Notepad::Notepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Notepad)
{
    ui->setupUi(this);
    setButtonsColorMapping();
    setPressedButtonsColor();
    setButtonsMapping();
}

void Notepad::setButtonsColorMapping()
{
    colorsLut[ui->team1] = QString("yellow");
    colorsLut[ui->team2] = QString("green");
}

void Notepad::setButtonsMapping()
{
    connect(ui->reset, &QPushButton::clicked, this, &Notepad::resetResult);
    for (auto& button : colorsLut)
    {
        connect(button.first, &QPushButton::clicked, this, &Notepad::setResult);
    }
}

void Notepad::setPressedButtonsColor()
{
    ui->reset->setStyleSheet("QPushButton:pressed { background-color: red }");
    for (auto& button : colorsLut)
    {
        const auto style = QString("QPushButton:pressed { background-color: %1 }").arg(button.second);
        button.first->setStyleSheet(style);
    }
}

void Notepad::keyPressEvent(QKeyEvent *event)
{
    const int animateLenInMs = 50;
    switch(event->key())
    {
    case Qt::Key_1:
        ui->team1->animateClick(animateLenInMs);
        break;
    case Qt::Key_0:
        ui->team2->animateClick(animateLenInMs);
        break;
    case Qt::Key_R:
        ui->reset->animateClick(animateLenInMs);
        break;
    }
}

void Notepad::setResult()
{
    if(resultLock == false)
    {
        const auto team = dynamic_cast<QPushButton*>(sender());
        const auto teamName = team->text();
        const auto teamColor = colorsLut[team];
        const auto style = QString("background-color: %1").arg(teamColor);

        ui->result->setText(teamName);
        ui->result->setStyleSheet(style);
        resultLock = true;
    }
}

void Notepad::resetResult()
{
    ui->result->setStyleSheet("");
    ui->result->setText("");
    resultLock = false;
}

Notepad::~Notepad()
{
    delete ui;
}

