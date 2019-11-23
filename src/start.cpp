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

#include <QFileDialog>
#include "start.h"
#include "ui_start.h"

Start::Start(QWidget *parent, Highscores *settings) :
    QWidget(parent),
    ui(new Ui::Start)
{
    ui->setupUi(this);

    SignsNames[0] = ui->signsName1;
    SignsNames[1] = ui->signsName2;
    SignsNames[2] = ui->signsName3;

    SignsPoints[0] = ui->signsPoint1;
    SignsPoints[1] = ui->signsPoint2;
    SignsPoints[2] = ui->signsPoint3;

    MeaningsNames[0] = ui->meaningsName1;
    MeaningsNames[1] = ui->meaningsName2;
    MeaningsNames[2] = ui->meaningsName3;

    MeaningsPoints[0] = ui->meaningsPoint1;
    MeaningsPoints[1] = ui->meaningsPoint2;
    MeaningsPoints[2] = ui->meaningsPoint3;

    connect(ui->pushButton, SIGNAL(clicked()), parent, SLOT(startSigns()));
    connect(ui->pushButton_2, SIGNAL(clicked()), parent, SLOT(startMeanings()));

    Settings = settings;

    showHighscore();
}

Start::~Start()
{
    delete ui;
}

void Start::showHighscore()
{
    for(int i = 0; i < 3; i++) {
        SignsNames[i]->setText("    "+QString().setNum(i+1)+". "+Settings->getSignsName(i));
        SignsPoints[i]->setText("    "+QString().setNum(Settings->getSignsPoint(i))+" Points");
        MeaningsNames[i]->setText("    "+QString().setNum(i+1)+". "+Settings->getMeaningsName(i));
        MeaningsPoints[i]->setText("    "+QString().setNum(Settings->getMeaningsPoint(i))+" Points");
    }
}
