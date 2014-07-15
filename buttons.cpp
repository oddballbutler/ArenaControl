#include "buttons.h"

Buttons::Buttons(QObject *parent) :
    QObject(parent)
{
}

void Buttons::pressTeam1Button()
{
    emit team1ButtonPressed();
}

void Buttons::pressTeam2Button()
{
    emit team2ButtonPressed();
}
