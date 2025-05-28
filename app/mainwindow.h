#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private slots:
    void onSettingsSaved(bool success);

    void onValidationError(const QString& message);

    void onAddedPlayer(const QString& msg);

    void onFailAddedPlayer(const QString& msg);

    void on_push_options_clicked();

    void on_push_back_clicked();

    void on_push_exit_clicked();

    void on_push_save_clicked();

    void on_push_back_2_clicked();

    void on_push_new_game_clicked();

    void on_push_add_player_clicked();

    void on_push_start_clicked();

private:
    Ui::MainWindow *ui;
    GameController* controller;
};

#endif // MAINWINDOW_H
