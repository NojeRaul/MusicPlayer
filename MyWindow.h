#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_QTAppooplab9.h"
#include "Controller.h"
#include <QLineEdit>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QFormLayout>
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QList>
#include "qtablewidget.h"


class MyWindow : public QMainWindow
{
    Q_OBJECT

public:
    MyWindow(Controller& c,QWidget *parent = nullptr);
    //friend class Controller;
    void addSong();
    void removeSong();
    void reload_list_data();
    void add_To_Playlist();
    void randomPlaylist();
    void keyPressEvent(QKeyEvent* event);
    void search();
    void sort_ascending_();
    void sort_descending_();
    void view_lyrics_();
    void play_song();

    ~MyWindow();

private:
    QLineEdit* left1;
    QLineEdit* left2;
    QLineEdit* left4;
    QLineEdit* left3;
    QTableWidget* list1;
    QPushButton* search_button;
    QPushButton* get_random_button;
    QPushButton* mid_button2;
    QLabel* search_label;
    QWidget* mainWidget;
    QGridLayout* searchLayout;
    QLineEdit* search1;
    QLineEdit* search2;
    QLabel* randomEl;
    QLineEdit* randomNr;
    QTableWidget* list2;
    QTableWidgetItem* selectedTableWidget;
    QPushButton* sort_ascending;
    QPushButton* sort_descending;
    QPushButton* view_lyrics;
    QLineEdit* lyrics_box;
    QLabel* lyrics_label;
    Controller& cont;
    std::vector<int> playlist;
    Ui::QTAppooplab9Class ui;
};

