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

#include <ctime>
#include <cstdlib>
#include <QBitmap>
#include <QButtonGroup>
#include <QInputDialog>
#include <QMessageBox>
#include "game.h"
#include "ui_game.h"

Game::Game(QWidget *parent, Data *dataSet, Highscores *settings, bool signs) :
    QWidget(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);

    Buttons = new QButtonGroup();
    Buttons->setExclusive(false);

    isSigns = signs;
    if (isSigns == true) {
        uiSigns = new Ui::Signs;
        uiSigns->setupUi(ui->widget);
        Buttons->addButton(uiSigns->pushButton, 0);
        Buttons->addButton(uiSigns->pushButton_2, 1);
        Buttons->addButton(uiSigns->pushButton_3, 2);
        Buttons->addButton(uiSigns->pushButton_4, 3);
    }
    else {
        uiMeanings = new Ui::Meanings;
        uiMeanings->setupUi(ui->widget);
        Buttons->addButton(uiMeanings->pushButton, 0);
        Buttons->addButton(uiMeanings->pushButton_2, 1);
        Buttons->addButton(uiMeanings->pushButton_3, 2);
        Buttons->addButton(uiMeanings->pushButton_4, 3);
    }

    Timer = new QTimer(this);
    connect(Timer, SIGNAL(timeout()), this, SLOT(countDown()));
    Timer->start(1000);
    Seconds = 59;
    Points = 0;
    ui->lcdNumber->display(Seconds);

    connect(this, SIGNAL(stop()), parent, SLOT(stopGame()));
    connect(Buttons, SIGNAL(buttonClicked(int)), this, SLOT(evaluateButton(int)));

    Settings = settings;

    DataSet = dataSet;
    srand(static_cast<unsigned int>(time(nullptr)));
    initRound();
}

Game::~Game()
{
    if (isSigns == true) {
        delete uiSigns;
    }
    else {
        delete uiMeanings;
    }

    delete Buttons;
    delete Timer;
    delete ui;
}

void Game::initRound()
{
    bool twice;
    int ButtonIds[4];
    RightPos = rand() % 4;

    for (int i = 0; i < 4; i++) {
        do {
            twice = false;
            ButtonIds[i] = randomNumber();
            for (int j = 0; j < i; j++) {
                if (ButtonIds[i] == ButtonIds[j]) {
                     twice = true;
                }
            }
        } while (twice == true);

        Clicked[i] = false;
        Buttons->button(i)->setChecked(false);

        if (isSigns == true) {
            Buttons->button(i)->setText("");
            Buttons->button(i)->setIconSize(QSize(120, 60));

            QPixmap tempPix(DataSet->getFilename(ButtonIds[i]));
            tempPix = tempPix.scaledToHeight(60, Qt::SmoothTransformation);
            Buttons->button(i)->setIcon(QIcon(tempPix));

            if (i == RightPos) {
                ui->label->setText(DataSet->getMeaning(ButtonIds[i]));
            }
        }
        else {
            Buttons->button(i)->setText(DataSet->getMeaning(ButtonIds[i]));

            if (i == RightPos) {
                QPixmap tempPix(DataSet->getFilename(ButtonIds[i]));
                tempPix = tempPix.scaledToHeight(60, Qt::SmoothTransformation);
                ui->label->setPixmap(tempPix);
            }
        }
    }
}

int Game::randomNumber()
{
    return rand() % DataSet->getLength();
}

void Game::evaluateButton(int number)
{
    if(number == RightPos) {
        Points += 3;
        ui->lcdNumber_2->display(Points);
        initRound();
    }
    else {
        if (Clicked[number] == false) {
            ui->lcdNumber_2->display(--Points);
        }
        Clicked[number] = true;
        Buttons->button(number)->setChecked(true);
    }
}

void Game::countDown()
{
    if (Seconds == 0) {
        for (int i = 0; i < 4; i++) {
            Buttons->button(i)->setDisabled(true);
        }
        Timer->stop();
        setHighscore();
        emit stop();
    }
    else {
        Seconds--;
        ui->lcdNumber->display(Seconds);
    }
}

void Game::setHighscore()
{
    bool ok;
    bool update = false;
    int ScorePoints;

    for (int i = 0; i < 3; i++) {
        if (isSigns == true) {
            ScorePoints = Settings->getSignsPoint(i);
        }
        else {
            ScorePoints = Settings->getMeaningsPoint(i);
        }
        if (Points >= ScorePoints) {
            update = true;
            QString name = QInputDialog::getText(this, "New Highscore", "You scored "+QString().setNum(Points)+" Points:", QLineEdit::Normal, "Your Name", &ok);
            if (ok && !name.isEmpty()) {
                insertScore(name, i);
            }
            break;
        }
    }
    if (update == false) {
        QMessageBox::information(this, "Congratulations", "You scored "+QString().setNum(Points)+" Points.");
    }
}

void Game::insertScore(QString name, int position)
{
    for (int i = 2; i >= 0; i--) {
        if (position < i) {
            if (isSigns == true) {
                Settings->setSigns(i, Settings->getSignsName(i-1), Settings->getSignsPoint(i-1));
            }
            else {
                Settings->setMeanings(i, Settings->getMeaningsName(i-1), Settings->getMeaningsPoint(i-1));
            }
        }
        else if (position == i) {
            if (isSigns == true) {
                Settings->setSigns(i, name, Points);
            }
            else {
                Settings->setMeanings(i, name, Points);
            }
            break;
        }
    }
}
