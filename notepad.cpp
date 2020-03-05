#include "notepad.h"
#include "ui_notepad.h"
#include <QKeyEvent>

Notepad::Notepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Notepad)
{
    ui->setupUi(this);
    prepareColorMapping();
    setPressedButtonsColor();
}

void Notepad::prepareColorMapping()
{
    colorsLut[ui->team1] = QString("yellow");
    colorsLut[ui->team2] = QString("green");
}

void Notepad::setPressedButtonsColor()
{
    for (auto& button : colorsLut)
    {
        const auto style = QString("QPushButton:pressed { background-color: %1 }").arg(button.second);
        button.first->setStyleSheet(style);
    }
}

void Notepad::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_1:
        handleTeamSignal(ui->team1);
        break;
    case Qt::Key_0:
        handleTeamSignal(ui->team2);
        break;
    case Qt::Key_R:
        resetResult();
        break;
    }
}

void Notepad::handleTeamSignal(QPushButton* team)
{
    if(resultLock == false)
    {
        const auto teamName = team->text();
        const auto teamColor = colorsLut[team];
        const auto style = QString("background-color: %1").arg(teamColor);

        ui->result->setText(teamName);
        ui->result->setStyleSheet(style);
        resultLock = true;
    }
    team->animateClick();
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

