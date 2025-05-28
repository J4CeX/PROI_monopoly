#include <QMessageBox>
#include <QPixmap>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    controller = new GameController(this);

    ui->stackedInterface->setCurrentIndex(0);
    QPixmap pix1(":/board/monopoly_map.png");
    ui->label_board->setPixmap(pix1.scaled(600, 600, Qt::KeepAspectRatio));
    QPixmap pix2(":/board/pawn.png");
    ui->label_pawn->setPixmap(pix2);
    ui->label_pawn->move(645, 510);

    connect(controller, &GameController::settingsSaved, this, &MainWindow::onSettingsSaved);
    connect(controller, &GameController::validationError, this, &MainWindow::onValidationError);
    connect(controller, &GameController::addedPlayer, this, &MainWindow::onAddedPlayer);
    connect(controller, &GameController::failAddedPlayer, this, &MainWindow::onFailAddedPlayer);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onSettingsSaved(bool success) {
    if (success) {
        QMessageBox::information(this, "Success", "Settings saved!");
    }
}

void MainWindow::onValidationError(const QString& message) {
    QMessageBox::warning(this, "Error", message);
}

void MainWindow::onAddedPlayer(const QString& msg)
{
    QMessageBox::information(this, "Success", msg);
    ui->label_player_amount->setText(controller->getPlayerAmount());
    ui->input_p_name->clear();
    ui->list_players->clear();
    ui->list_players->addItems(controller->playerNamesList());
}

void MainWindow::onFailAddedPlayer(const QString& msg)
{
    QMessageBox::warning(this, "Error", msg);
}

void MainWindow::on_push_options_clicked()
{
    ui->stackedInterface->setCurrentIndex(1);
}

void MainWindow::on_push_back_clicked()
{
    ui->stackedInterface->setCurrentIndex(0);
}


void MainWindow::on_push_exit_clicked()
{
    QApplication::quit();
}


void MainWindow::on_push_save_clicked()
{
    QString value1 = ui->input_maxCash->text();
    QString value2 = ui->input_startCash->text();
    controller->saveSettings(value1, value2);
}


void MainWindow::on_push_back_2_clicked()
{
    ui->stackedInterface->setCurrentIndex(0);
}


void MainWindow::on_push_new_game_clicked()
{
    ui->stackedInterface->setCurrentIndex(2);
    controller->startNewGame();
    ui->label_player_amount->setText(controller->getPlayerAmount());
    ui->list_players->clear();
}


void MainWindow::on_push_add_player_clicked()
{
    QString player_name = ui->input_p_name->text();
    QString token_text = ui->combo_box_p_token->currentText();
    controller->addPlayer(player_name, token_text);
}


void MainWindow::on_push_start_clicked()
{
    ui->stackedInterface->setCurrentIndex(3);
}

