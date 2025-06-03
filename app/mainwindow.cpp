#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    controller = new GameController(this);

    ui->stackedInterface->setCurrentIndex(0);
    this->board = new BoardWidget(ui->widget_board);
    this->board->setGeometry(ui->widget_board->rect());
    this->board->show();

    QPixmap logo(":/board/monopoly_logo.png");
    ui->label_logo->setPixmap(logo);

    this->setStyleSheet("background-image: url(:/board/background.png); background-repeat: no-repeat; background-position: center;");

    this->loadButtons();

    connect(controller, &GameController::settingsSaved, this, &MainWindow::onSettingsSaved);
    connect(controller, &GameController::validationError, this, &MainWindow::onValidationError);
    connect(controller, &GameController::addedPlayer, this, &MainWindow::onAddedPlayer);
    connect(controller, &GameController::failAddedPlayer, this, &MainWindow::onFailAddedPlayer);
    connect(controller, &GameController::fail, this, &MainWindow::onFail);
    connect(controller, &GameController::startedGame, this, &MainWindow::onStartedGame);
    connect(controller, &GameController::rolledDice, this, &MainWindow::onRolledDice);
    connect(controller, &GameController::isBuyableField, this, &MainWindow::onIsBuyableField);
    connect(controller, &GameController::triedBuyField, this, &MainWindow::onTriedBuyField);
    connect(controller, &GameController::balanceChanged, this, &MainWindow::onBalanceChanged);
    connect(controller, &GameController::currentEvent, this, &MainWindow::onCurrentEvent);
    connect(controller, &GameController::finishedGameSignal, this, &MainWindow::onFinishedGameSignal);
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
    ui->label_dice_result->setText("");
    ui->label_field_cost->setText("");
    ui->frame_field_info->hide();
    ui->push_finish_round->setEnabled(false);
    ui->push_buy_field->setEnabled(false);
    ui->push_roll_dice->setEnabled(true);
    ui->label_turn_number->setText(controller->getGameTurn());
    this->board->setPlayers(controller->getPlayers());
    this->updatePlayerLabels();
    this->updatePlayersPositions();
}

void MainWindow::onBalanceChanged(int difference)
{
    QMessageBox::information(this, "Info", "Balance changed: " + QString::number(difference));
}

void MainWindow::onCurrentEvent(const QString& eventText)
{
    QMessageBox::information(this, "info", eventText);
}

void MainWindow::on_push_options_clicked()
{
    ui->stackedInterface->setCurrentIndex(1);
}

void MainWindow::on_push_back_clicked()
{
    ui->stackedInterface->setCurrentIndex(0);
}

void MainWindow::onRolledDice(const QString& results)
{
    this->updatePlayerLabels();
    std::cout << "updated player labels, popup should show now" << std::endl;
    this->updatePlayersPositions();
    ui->label_dice_result->setText(results);
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

void MainWindow::updatePlayerOwnedFields()
{
    auto owned_fields = controller->currentPlayerOwnedFields();
    ui->list_owned_fields->clear();

    for (const auto& [label, position] : owned_fields)
    {
        QListWidgetItem* item = new QListWidgetItem(label);
        item->setData(Qt::UserRole, static_cast<int>(position));
        ui->list_owned_fields->addItem(item);
    }

}

void MainWindow::updatePlayerLabels()
{
    ui->list_players_2->clear();
    ui->list_players_2->addItems(controller->playerNamesList());
    ui->label_current_p->setText(controller->currentPlayerName());
    ui->label_balance_p->setText(controller->currentPlayerBalance() + " zł");
    ui->label_token_p->setText(controller->currentPlayerToken());
    ui->label_field_p->setText(controller->currentPlayerField());
    this->updatePlayerOwnedFields();
}

void MainWindow::updatePlayersPositions()
{
    for(Player player : controller->getPlayers())
    {
        int idx = player.getPlayerId()-1;
        int pos = player.getPosition();
        this->board->updatePawnPosition(idx, pos);
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
    std::cout << "pushed finish round, popup shouldnt show" << std::endl;
    ui->frame_field_info->hide();
    ui->label_dice_result->clear();
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
    std::cout<<"2"<<std::endl;
}

void MainWindow::on_list_owned_fields_itemClicked(QListWidgetItem *item)
{
    int fieldIndex = item->data(Qt::UserRole).toInt();
    controller->selectedFieldIndex = fieldIndex;
    ui->frame_field_info->show();
    this->updateOfLabels(fieldIndex);
}

void MainWindow::updateOfLabels(int fieldIndex)
{
    QStringList of_info = controller->getOwnedFieldInfo(fieldIndex);
    QString q_type = of_info[2];
    QString q_houses = of_info[3];
    QString q_mortgaged = of_info[5];
    ui->label_of_name->setText(of_info[0]);
    ui->label_of_pos->setText(of_info[1]);
    ui->label_of_type->setText(q_type);
    ui->label_of_houses->setText(of_info[3]);
    ui->label_of_rent->setText(of_info[4]);
    ui->label_of_mortgaged->setText(q_mortgaged);
    if(q_type=="STATION" || q_type=="UTILITY")
    {
        ui->push_of_buy_house->setEnabled(false);
        ui->push_of_sell_house->setEnabled(false);
        if(q_mortgaged=="Yes")
        {
            ui->push_of_mortgage->setEnabled(false);
            ui->push_of_unmortgage->setEnabled(true);
        }
        else
        {
            ui->push_of_mortgage->setEnabled(true);
            ui->push_of_unmortgage->setEnabled(false);
        }
    }
    else
    {
        if(q_mortgaged=="Yes")
        {
            ui->push_of_mortgage->setEnabled(false);
            ui->push_of_unmortgage->setEnabled(true);
            ui->push_of_buy_house->setEnabled(false);
            ui->push_of_sell_house->setEnabled(false);
        }
        else
        {
            ui->push_of_mortgage->setEnabled(true);
            ui->push_of_unmortgage->setEnabled(false);
            ui->push_of_buy_house->setEnabled(true);
            ui->push_of_sell_house->setEnabled(true);
        }
    }
    if(q_houses == "5")
    {
        ui->push_of_buy_house->setEnabled(false);
        ui->label_of_houses->setText("5 (max)");
    }
    this->updatePlayerLabels();
    std::cout<<"1"<<std::endl;
}

void MainWindow::on_push_of_back_clicked()
{
    ui->frame_field_info->hide();
}


void MainWindow::on_push_of_buy_house_clicked()
{
    int fieldIndex = controller->selectedFieldIndex;
    int code = controller->buyOfHouse(fieldIndex);
    this->updateOfLabels(fieldIndex);
    if(code==2) QMessageBox::information(this, "success", "Successfully bought a house!");
    else QMessageBox::warning(this, "fail", "Couldn't buy the house!");
}


void MainWindow::on_push_of_sell_house_clicked()
{
    int fieldIndex = controller->selectedFieldIndex;
    int code = controller->sellOfHouse(fieldIndex);
    this->updateOfLabels(fieldIndex);
    if(code==1) QMessageBox::information(this, "success", "Successfully sold a house!");
    else QMessageBox::warning(this, "fail", "Couldn't sell the house!");
}


void MainWindow::on_push_of_mortgage_clicked()
{
    int fieldIndex = controller->selectedFieldIndex;
    int code = controller->ofMortgage(fieldIndex);
    this->updateOfLabels(fieldIndex);
    if(code==2) QMessageBox::information(this, "success", "Successfully mortgaged the field!");
    else if(code==-1) QMessageBox::warning(this, "fail", "House count must be 0!");
    else QMessageBox::warning(this, "fail", "Couldn't mortgage the field.");
}


void MainWindow::on_push_of_unmortgage_clicked()
{
    int fieldIndex = controller->selectedFieldIndex;
    int code = controller->ofUnmortgage(fieldIndex);
    this->updateOfLabels(fieldIndex);
    if(code==1) QMessageBox::information(this, "success", "Successfully unmortgaged the field!");
    else if(code==-1) QMessageBox::warning(this, "fail", "House count must be 0!");
    else QMessageBox::warning(this, "fail", "Couldn't unmortgage the field.");
}

void MainWindow::onFinishedGameSignal(const QString& winnerName)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Game Over");
    msgBox.setText("Game over!\nWinner: " + winnerName +"\n Congratulations!");

    QPushButton* backButton = msgBox.addButton("Back to menu", QMessageBox::AcceptRole);
    msgBox.exec();

    if (msgBox.clickedButton() == backButton) {
        ui->stackedInterface->setCurrentIndex(0);
    }
}

void MainWindow::loadButtons()
{
    ui->push_new_game->setFixedSize(300, 75);
    ui->push_new_game->setStyleSheet(
        "QPushButton {"
        "   border: none;"
        "   background-image: url(:/board/button_start);"
        "}"
        "QPushButton:hover {"
        "   background-image: url(:/board/button_start_hover);"
        "}"
        "QPushButton:pressed {"
        "   background-image: url(:/board/button_start);"
        "}"
    );
    ui->push_options->setFixedSize(300, 75);
    ui->push_options->setStyleSheet(
        "QPushButton {"
        "   border: none;"
        "   background-image: url(:/board/button_options);"
        "}"
        "QPushButton:hover {"
        "   background-image: url(:/board/button_options_hover);"
        "}"
        "QPushButton:pressed {"
        "   background-image: url(:/board/button_options);"
        "}"
    );
    ui->push_load->setFixedSize(300, 75);
    ui->push_load->setStyleSheet(
        "QPushButton {"
        "   border: none;"
        "   background-image: url(:/board/button_load);"
        "}"
        "QPushButton:hover {"
        "   background-image: url(:/board/button_load_hover);"
        "}"
        "QPushButton:pressed {"
        "   background-image: url(:/board/button_load);"
        "}"
    );
    ui->push_exit->setFixedSize(300, 75);
    ui->push_exit->setStyleSheet(
        "QPushButton {"
        "   border: none;"
        "   background-image: url(:/board/button_exit);"
        "}"
        "QPushButton:hover {"
        "   background-image: url(:/board/button_exit_hover);"
        "}"
        "QPushButton:pressed {"
        "   background-image: url(:/board/button_exit);"
        "}"
    );
}