#include "menuwindow.h"
#include "ui_menuwindow.h"

menuWindow::menuWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::menuWindow)
{
    ui->setupUi(this);
    opt = new options;
    on_cansle_clicked();
}

menuWindow::~menuWindow()
{
    delete ui;
}

void menuWindow::on_options_clicked()
{
    ui->widgetOpt->show();
    ui->menu->hide();
}

void menuWindow::on_ai1_clicked()
{
    ui->cofW1->show();
    ui->humen2->setChecked(true);
    ui->cofW2->hide();
}

void menuWindow::on_ai2_clicked()
{
    ui->cofW2->show();
    ui->humen1->setChecked(true);
    ui->cofW1->hide();
}

void menuWindow::on_humen1_clicked()
{
    ui->cofW1->hide();
}

void menuWindow::on_humen2_clicked()
{
    ui->cofW2->hide();
}

void menuWindow::on_cansle_clicked()
{
    ui->menu->show();
    ui->widgetOpt->hide();
    if (opt->getPlayer1() == "AI"){
        ui->ai1->setChecked(true);
        ui->humen1->setChecked(false);
        ui->cofW1->show();

    }
    else{
        ui->ai1->setChecked(false);
        ui->humen1->setChecked(true);
        ui->cofW1->hide();
    }
    ui->kof1->setCurrentIndex(opt->getAiCof1());

    if (opt->getPlayer2() == "AI"){
        ui->ai2->setChecked(true);
        ui->humen2->setChecked(false);
        ui->cofW2->show();

    }
    else{
        ui->ai2->setChecked(false);
        ui->humen2->setChecked(true);
        ui->cofW2->hide();
    }
    ui->kof2->setCurrentIndex(opt->getAiCof2());
}

void menuWindow::on_save_clicked()
{
    ui->menu->show();
    ui->widgetOpt->hide();
    opt->setPlayer1(ui->humen1->isChecked() ? "human" : "AI");
    opt->setPlayer2(ui->humen2->isChecked() ? "human" : "AI");
    opt->setAiCof1(ui->kof1->currentIndex() + 1);
    opt->setAiCof2(ui->kof2->currentIndex() + 1);
}

void menuWindow::on_newGame_clicked()
{
    game = new gameWindow(opt, (QWidget *)this);
    game->show();
    hide();
}

void menuWindow::on_exit_clicked()
{
    close();
}
