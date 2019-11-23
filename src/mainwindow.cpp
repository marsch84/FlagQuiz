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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent) :
        QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    QString errorMsg;
    int errorLine;
    int errorColumn;
    QFile file(":/xml/flags.xml");
    QDomDocument Document("flags");

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Error", "The file \"flags.xml\" can not be opened.");
        exit(-1);
    }

    if (!Document.setContent(&file, &errorMsg, &errorLine, &errorColumn)) {
        file.close();
        QMessageBox::critical(this, "Error", errorMsg+" in file flags.xml (line "+QString().setNum(errorLine)+", column "+QString().setNum(errorColumn)+")");
        exit(-1);
    }

    DataSet = new Data(&Document);

    ui->setupUi(this);
    Settings = new Highscores();
    StartWidget = new Start(this, Settings);
    setCentralWidget(StartWidget);
}

MainWindow::~MainWindow(){
    delete centralWidget();
    delete Settings;
    delete DataSet;
    delete ui;
}

void MainWindow::handleOpenBrowser(){
    emit sigOpenBrowser(QString());
}

void MainWindow::handleStartNativeApp(){
    emit sigStartNativeApp(QString(), QStringList(QString()));
}

void MainWindow::handleOnlineModeChanged(bool){

}

void MainWindow::setAppDataPath(QDir path){
    appDataPath = path;
}

void MainWindow::startSigns()
{
    startGame(true);
}

void MainWindow::startMeanings()
{
    startGame(false);
}

void MainWindow::startGame(bool signs)
{
    if(!checkFiles()) {
        return;
    }

    GameWidget = new Game(this, DataSet, Settings, signs);
    setCentralWidget(GameWidget);
}

void MainWindow::stopGame()
{
    StartWidget = new Start(this, Settings);
    setCentralWidget(StartWidget);
}

bool MainWindow::checkFiles()
{
    for (int i = 0; i < DataSet->getLength(); i++) {
        if (!QFileInfo(DataSet->getFilename(i)).exists()) {
            QMessageBox::critical(this, "Error", "The file \""+DataSet->getFilename(i)+"\" can not be opened.");
            return false;
        }
    }
    return true;
}
