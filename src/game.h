/*
    Copyright 2019 Martin Scherer

    This file is part of FlagQuiz.

    FlagQuiz is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    FlagQuiz is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FlagQuiz.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAME_H
#define GAME_H

#include <QPushButton>
#include <QSettings>
#include <QTimer>
#include <QWidget>
#include <data.h>
#include "highscores.h"
#include "ui_meanings.h"
#include "ui_signs.h"

namespace Ui {
    class Game;
}

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = 0, Data *dataSet = 0, Highscores *settings = 0, bool signs = false);
    ~Game();

private slots:
    void countDown();
    void evaluateButton(int number);

signals:
    void stop();

private:
    void initRound();
    int randomNumber();
    void setHighscore();
    void insertScore(QString name, int position);
    Ui::Game *ui;
    Ui::Signs *uiSigns;
    Ui::Meanings *uiMeanings;
    Data *DataSet;
    int RightPos;
    bool Clicked[4];
    bool isSigns;
    int Seconds;
    int Points;
    QButtonGroup *Buttons;
    QTimer *Timer;
    Highscores *Settings;
};

#endif // GAME_H
