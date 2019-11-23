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

#ifndef START_H
#define START_H

#include <QLabel>
#include <QSettings>
#include <QWidget>
#include "highscores.h"

namespace Ui {
    class Start;
}

class Start : public QWidget
{
    Q_OBJECT

public:
    explicit Start(QWidget *parent = nullptr, Highscores *settings = nullptr);
    ~Start();

private:
    void showHighscore();
    Ui::Start *ui;
    Highscores *Settings;
    QLabel *SignsNames[4];
    QLabel *SignsPoints[4];
    QLabel *MeaningsNames[4];
    QLabel *MeaningsPoints[4];
};

#endif // START_H
