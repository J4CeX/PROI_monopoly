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

    this->loadPawns();

    connect(controller, &GameController::settingsSaved, this, &MainWindow::onSettingsSaved);
    connect(controller, &GameController::validationError, this, &MainWindow::onValidationError);
    connect(controller, &GameController::addedPlayer, this, &MainWindow::onAddedPlayer);
    connect(controller, &GameController::failAddedPlayer, this, &MainWindow::onFailAddedPlayer);
    connect(controller, &GameController::fail, this, &MainWindow::onFail);
    connect(controller, &GameController::startedGame, this, &MainWindow::onStartedGame);
    connect(controller, &GameController::rolledDice, this, &MainWindow::onRolledDice);
    connect(controller, &GameController::isBuyableField, this, &MainWindow::onIsBuyableField);
    connect(controller, &GameController::triedBuyField, this, &MainWindow::onTriedBuyField);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadPawns()
{
    QPixmap pixRaceCar(":/board/racecar.png");
    ui->label_pawn_raceCar->setPixmap(pixRaceCar);
    ui->label_pawn_raceCar->hide();

    QPixmap pixTopHat(":/board/tophat.png");
    ui->label_pawn_topHat->setPixmap(pixTopHat);
    ui->label_pawn_topHat->hide();

    QPixmap pixThimble(":/board/thimble.png");
    ui->label_pawn_thimble->setPixmap(pixThimble);
    ui->label_pawn_thimble->hide();

    QPixmap pixScottTerr(":/board/scottishterrier.png");
    ui->label_pawn_scottTerr->setPixmap(pixScottTerr);
    ui->label_pawn_scottTerr->hide();
}

QLabel* MainWindow::getLabelByToken(Token token) const
{
    std::map<Token, QLabel*> token_label_map = {{Token::raceCar, ui->label_pawn_raceCar},
                                                {Token::topHat, ui->label_pawn_topHat},
                                                {Token::thimble, ui->label_pawn_thimble},
                                                {Token::scottishTerrier, ui->label_pawn_scottTerr}};
    return token_label_map[token];
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

void MainWindow::onFail(const QString& msg)
{
    QMessageBox::warning(this, "Error", msg);
}

void MainWindow::onIsBuyableField(bool isBuyable, int cost)
{
    ui->push_buy_field->setEnabled(isBuyable);
    if(isBuyable)
    {
        ui->label_field_cost->setText("Cost: " + QString::number(cost));
    }
    else
    {
        ui->label_field_cost->setText("This field is owned");
    }
}

void MainWindow::onTriedBuyField(int code, const QString& q_field)
{
    if(code==1)
    {
        QString msg = "'" + q_field + "' bought successfully!";
        QMessageBox::information(this, "Success", msg);
        ui->push_buy_field->setEnabled(false);
    }
    else if(code==-1)
    {
        QString msg = "'" + q_field + "' is already owned!";
        QMessageBox::warning(this, "Error", msg);
        ui->push_buy_field->setEnabled(false);
    }
    else if(code==-2)
    {
        QString msg = "Not enough money to buy '" + q_field + "'";
        QMessageBox::warning(this, "Error", msg);
        ui->push_buy_field->setEnabled(false);
    }
    else
    {
        QMessageBox::warning(this, "Error", "ERROR Something went wrong");
    }
}

void MainWindow::onStartedGame()
{
    ui->stackedInterface->setCurrentIndex(3);
    ui->push_finish_round->setEnabled(false);
    ui->push_buy_field->setEnabled(false);
    ui->push_roll_dice->setEnabled(true);
    this->loadPawns();
    this->updatePlayerLabels();
    ui->label_turn_number->setText(controller->getGameTurn());
}

void MainWindow::on_push_options_clicked()
{
    ui->stackedInterface->setCurrentIndex(1);
}

void MainWindow::on_push_back_clicked()
{
    ui->stackedInterface->setCurrentIndex(0);
}

void MainWindow::onRolledDice(const QString& results, const QString& field)
{
    this->updatePlayerLabels();
    ui->label_dice_result->setText(results);
    ui->label_field_p->setText(field);
    ui->push_roll_dice->setEnabled(false);
    ui->push_finish_round->setEnabled(true);
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

void MainWindow::updatePlayerLabels()
{
    ui->list_players_2->clear();
    ui->list_players_2->addItems(controller->playerNamesList());
    ui->label_current_p->setText(controller->currentPlayerName());
    ui->label_balance_p->setText(controller->currentPlayerBalance());
    ui->label_position_p->setText(controller->currentPlayerPosition());
    ui->label_token_p->setText(controller->currentPlayerToken());
    ui->label_index_p->setText(controller->currentPlayerIndex());
    ui->list_owned_fields->clear();
    ui->list_owned_fields->addItems(controller->currentPlayerOwnedFields());
                                           
    for(Player player : controller->getPlayers())
    {
        int pos = player.getPosition();
        std::pair<int, int> currentField = controller->fieldCoords(pos);
        Token token = player.getToken();
        int idx = player.getPlayerId();
        QLabel* label = this->getLabelByToken(token);
        label->show();
        label->move(currentField.first+idx*10, currentField.second+idx*10);
    }
}

void MainWindow::on_push_start_clicked()
{
    controller->tryStartGame();
}


void MainWindow::on_push_roll_dice_clicked()
{
    controller->rollDice();
}


void MainWindow::on_push_finish_round_clicked()
{
    controller->findNextPlayer();
    this->updatePlayerLabels();
    ui->label_dice_result->clear();
    ui->label_position_p->setText(controller->currentPlayerPosition());
    ui->label_field_p->setText(controller->currentPlayerField());
    ui->push_roll_dice->setEnabled(true);
    ui->push_finish_round->setEnabled(false);
    ui->push_buy_field->setEnabled(false);
    ui->label_field_cost->clear();
    ui->label_turn_number->setText(controller->getGameTurn());
}


void MainWindow::on_push_exit_game_clicked()
{
    ui->stackedInterface->setCurrentIndex(0);
}


void MainWindow::on_push_buy_field_clicked()
{
    controller->buyField();
    this->updatePlayerLabels();
}


void MainWindow::on_push_manage_fields_clicked()
{
    ui->stacked_game_options->setCurrentIndex((ui->stacked_game_options->currentIndex()+1)%2);
}

