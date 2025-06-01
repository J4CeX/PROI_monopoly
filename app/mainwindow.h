#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QListWidgetItem>
#include "GameController.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void loadPawns();
    QLabel* getLabelByToken(Token token) const;
    void updatePlayerLabels();
    void updatePlayerOwnedFields();
    void updateOfLabels(int fieldIndex);

private slots:

    void onSettingsSaved(bool success);

    void onValidationError(const QString& message);

    void onAddedPlayer(const QString& msg);

    void onFailAddedPlayer(const QString& msg);

    void onFail(const QString& msg);

    void onStartedGame();

    void onIsBuyableField(bool isBuyable, int cost);

    void onTriedBuyField(int code, const QString& q_field);

    void onRolledDice(const QString& results, const QString& field);

    void onBalanceChanged(int difference);

    void onCurrentEvent(const QString& eventText);

    void onFinishedGameSignal(const QString& winnerName);

    void on_push_options_clicked();

    void on_push_back_clicked();

    void on_push_exit_clicked();

    void on_push_save_clicked();

    void on_push_back_2_clicked();

    void on_push_new_game_clicked();

    void on_push_add_player_clicked();

    void on_push_start_clicked();

    void on_push_roll_dice_clicked();

    void on_push_finish_round_clicked();

    void on_push_exit_game_clicked();

    void on_push_buy_field_clicked();

    void on_list_owned_fields_itemClicked(QListWidgetItem *item);

    void on_push_of_back_clicked();

    void on_push_of_buy_house_clicked();

    void on_push_of_sell_house_clicked();

    void on_push_of_mortgage_clicked();

    void on_push_of_unmortgage_clicked();

    void on_push_go_bankrupt_clicked();

private:
    Ui::MainWindow *ui;
    GameController* controller;
};

#endif // MAINWINDOW_H
