#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QMainWindow>

#include "GUI/gamewindow.h"

namespace Ui {
class menuWindow;
}
/*!
 * \brief The menuWindow class - класс виджета меню
 */
class menuWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit menuWindow(QWidget *parent = 0);
    ~menuWindow();

private slots:
    void on_options_clicked();

    void on_ai1_clicked();

    void on_ai2_clicked();

    void on_humen1_clicked();

    void on_humen2_clicked();

    void on_cansle_clicked();

    void on_save_clicked();

    void on_newGame_clicked();

    void on_exit_clicked();

private:
    /*!
     * \brief ui - указатель на виджет
     */
    Ui::menuWindow *ui;
    /*!
     * \brief game - указатель на игру
     */
    gameWindow *game;
    /*!
     * \brief opt - указатель на текущие конфигурации
     */
    options *opt;
};

#endif // MENUWINDOW_H
