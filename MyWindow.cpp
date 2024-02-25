#include "MyWindow.h"
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>
#include <QFont>
#include <QList>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "SongColection.h"
#include "Controller.h"
#include "qdialog.h"
#include "qdialogbuttonbox.h"
#include "qwindow.h"
#include "qkeysequence.h"
#include "qshortcut.h"
#include <QKeyEvent>
#include "qtablewidget.h"
#include "assert.h"
#include "SongException.h"
#include <QMessageBox>
#include "Utility.h"
#include <QDesktopServices>
#include <QUrl>
#include <qapplication.h>


MyWindow::MyWindow(Controller& c,QWidget* parent)
    :cont{ c },QMainWindow(parent)
{
        /*QGridLayout *grd = new QGridLayout(this);*/
    setWindowTitle("My Window");
    //this->ui.setupUi(this);
    //VARIABLE DECLARATIONS
    QLabel* label1 = new QLabel("All songs", this);
    QLabel* label2 = new QLabel("Playlist", this);
    QLabel* label3 = new QLabel("Title:", this);
    QLabel* label4 = new QLabel("Artist:", this);
    QLabel* label6 = new QLabel("Link:", this);
    this->list2 = new QTableWidget(this);
    QPushButton* midButton = new QPushButton("Add to playlist",this);
    QPushButton* Button1 = new QPushButton("Add",this);
    QPushButton* Button2 = new QPushButton("Delete",this);
    QPushButton* Button5 = new QPushButton("Play",this);
    QPushButton* Button6 = new QPushButton("Next",this);
    this->list1 = new QTableWidget(this);
    this->left1 = new QLineEdit(this);
    this->left2 = new QLineEdit(this);
    this->randomEl = new QLabel("No. of Songs:", this);
    this->left4 = new QLineEdit(this);
    this->get_random_button = new QPushButton("Random", this);
    this->mid_button2 = new QPushButton("Delete from playlist", this);
    this->search_label = new QLabel("Search", this);
    this->search1 = new QLineEdit(this);
    this->search2 = new QLineEdit(this);
    this->randomNr = new QLineEdit(this);
    this->sort_ascending = new QPushButton("Sort songs ascending", this);
    this->sort_descending = new QPushButton("Sort songs descending", this);
    this->view_lyrics = new QPushButton("View lyrics", this);
    this->lyrics_box = new QLineEdit(this);
    this->lyrics_label = new QLabel("Lyrics", this);

    //LAYOUT
    QVBoxLayout* leftLayout = new QVBoxLayout(this);
    QGridLayout* midLayout = new QGridLayout(this);
    leftLayout->setAlignment(Qt::AlignTop);
    QGridLayout* left_bot_grid1 = new QGridLayout(this);
    QGridLayout* left_bot_grid2 = new QGridLayout(this);
    QGridLayout* right_bot_grid = new QGridLayout(this);
    this->searchLayout = new QGridLayout(this);
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    QVBoxLayout* rightLayout = new QVBoxLayout(this);
    rightLayout->setAlignment(Qt::AlignTop);

    //mid layout
    midLayout->addWidget(midButton, 1, 0, 1, 2);
    midLayout->addWidget(mid_button2,0,0,1,2);
    midLayout->addWidget(get_random_button,2,0,1,2);
    midLayout->addWidget(randomEl,3,0);
    midLayout->addWidget(randomNr, 3, 1);
    midLayout->setAlignment(Qt::AlignCenter);
    
    //midLayout->addStretch();

    //left_bot_grid1
    left_bot_grid1->setAlignment(Qt::AlignLeft);
    left_bot_grid1->addWidget(label4, 0, 0);
    left_bot_grid1->addWidget(label3, 1, 0);
    left_bot_grid1->addWidget(label6, 3, 0);
    left_bot_grid1->addWidget(lyrics_label,4, 0);
    left_bot_grid1->addWidget(left1, 0, 1);
    left_bot_grid1->addWidget(left2, 1,1);
    left_bot_grid1->addWidget(left4, 3, 1);
    left_bot_grid1->addWidget(lyrics_box, 4, 1);
    left_bot_grid1->columnStretch(0);
    left_bot_grid1->columnStretch(1);

    //left_bot_grid2
    left_bot_grid2->addWidget(Button1, 0, 0);
    left_bot_grid2->addWidget(Button2, 0, 1);
  

    //searchLayout
    searchLayout->addWidget(new QLabel("Title:",this), 0, 0);
    searchLayout->addWidget(new QLabel("Artist:",this), 1, 0);
    searchLayout->addWidget(search1, 0, 1);
    searchLayout->addWidget(search2, 1, 1);

    //Left layout
    leftLayout->setAlignment(Qt::AlignLeft);
    leftLayout->addWidget(label1);
    leftLayout->addWidget(list1);
    leftLayout->addLayout(left_bot_grid1);
    leftLayout->addLayout(left_bot_grid2);
    leftLayout->addWidget(search_label);
    leftLayout->addLayout(searchLayout);
    leftLayout->addWidget(sort_ascending);
    leftLayout->addWidget(sort_descending);
    leftLayout->addWidget(view_lyrics);
    //leftLayout->addStretch();

    //right_bot_grid
    right_bot_grid->addWidget(Button5,0,0);
    right_bot_grid->addWidget(Button6,0,1);

    //Right layout
    rightLayout->addWidget(label2);
    rightLayout->addWidget(list2);
    rightLayout->addLayout(right_bot_grid);
    //rightLayout->addStretch();


    //Assembling main layout
    mainLayout->addLayout(leftLayout);
    //mainLayout->addWidget(midButton);
    mainLayout->addLayout(midLayout);
    mainLayout->addLayout(rightLayout);
    mainLayout->setAlignment(Qt::AlignTop);
    //mainLayout->addStretch();
    list1->setSelectionBehavior(QAbstractItemView::SelectRows);
    list2->setSelectionBehavior(QAbstractItemView::SelectRows);

    QWidget* leftWidget = new QWidget(this);
    leftWidget->setLayout(leftLayout);
    this->mainWidget = new QWidget(this);
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);

    reload_list_data();
    connect(Button1, &QPushButton::clicked, this, &MyWindow::addSong);
    connect(Button2, &QPushButton::clicked, this, &MyWindow::removeSong);
    connect(Button1, &QPushButton::clicked, this, &MyWindow::reload_list_data);
    connect(midButton, &QPushButton::clicked, this, &MyWindow::add_To_Playlist);
    connect(get_random_button,&QPushButton::clicked, this, &MyWindow::randomPlaylist);
    connect(sort_ascending, &QPushButton::clicked, this, &MyWindow::sort_ascending_);
    connect(view_lyrics, &QPushButton::clicked, this, &MyWindow::view_lyrics_);
    connect(Button5, &QPushButton::clicked, this, &MyWindow::play_song);
    //connect(search_button, &QPushButton::clicked, this, &MyWindow::search_screen);

}

void MyWindow::addSong()
{
    reload_list_data();
    QString artist = this->left1->text();
    QString title = this->left2->text();
    QString link = this->left4->text();
    QString lyrics = this->lyrics_box->text();
    try {
        this->cont.addSong(artist.toStdString(), title.toStdString(), link.toStdString(), lyrics.toStdString());
    }
    catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void MyWindow::removeSong()
{
    QString artist = this->left1->text();
    QString title = this->left2->text();
    QString link = this->left4->text();
    QString lyrics = this->lyrics_box->text();
    try {
        this->cont.remove(artist.toStdString(), title.toStdString(), link.toStdString(),lyrics.toStdString());
    }
    catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
    reload_list_data();
}


void MyWindow::reload_list_data()
{
    this->list1->clear();
    this->list1->setColumnCount(3);
    this->list1->setRowCount(this->cont.getSongs().getSongs().size());
    int row = 0;
    for (auto i : this->cont.getSongs().getSongs())
    {
        QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(i.getArtist()));
        list1->setItem(row, 0, item);
        item = new QTableWidgetItem(QString::fromStdString(i.getTitle()));
        list1->setItem(row, 1, item);
        item = new QTableWidgetItem(QString::fromStdString(i.getLink()));
        list1->setItem(row, 2, item);
        row++;
        delete item;
    }
}

void MyWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_U) {
        qDebug() << "key pressed U";
        cont.undo();
        reload_list_data();
    }
    if (event->key() == Qt::Key_R) {
        qDebug() << "key pressed R";
        cont.redo();
        reload_list_data();
    }
}
void MyWindow::add_To_Playlist()
{   
    //write the code for adding to playlist by clicking the button and selecting the song from the list
    this->list2->clear();
    this->list2->setColumnCount(3);
    this->list2->setRowCount(1);
    QItemSelectionModel* select = list1->selectionModel();
    QModelIndexList indexList=  select->selectedRows();
    QModelIndex index= indexList.at(0);
    int row = index.row();
    Song i = this->cont.getSongs().getSongs().at(row);
    QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(i.getArtist()));
    list2->setItem(row, 0, item);
    item = new QTableWidgetItem(QString::fromStdString(i.getTitle()));
    list2->setItem(row, 1, item);
    item = new QTableWidgetItem(QString::fromStdString(i.getLink()));
    list2->setItem(row, 2, item);
    delete item;
}

void MyWindow::randomPlaylist()
{
    this->list2->clear();
    this->list2->setColumnCount(3);
    int nr = this->randomNr->text().toInt();
    this->list2->setRowCount(nr);
    std::vector<int> indices = getRandomInts(0, this->cont.getSongs().getSongs().size(), nr);
    for (int i=0;i<indices.size();i++)
    {
        Song s = this->cont.getSongs().getSongs().at(indices.at(i));
        QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(s.getArtist()));
        list2->setItem(i, 0, item);
        item = new QTableWidgetItem(QString::fromStdString(s.getTitle()));
        list2->setItem(i, 1, item);
        item = new QTableWidgetItem(QString::fromStdString(s.getLink()));
        list2->setItem(i, 2, item);
        delete item;

    }

}

void MyWindow::view_lyrics_()
{
    QItemSelectionModel* select = list1->selectionModel();
    QModelIndexList indexList = select->selectedRows();
    QModelIndex index = indexList.at(0);
    int row = index.row();
    Song i = this->cont.getSongs().getSongs().at(row);
    QDialog* lyrics_window = new QDialog();
    lyrics_window->setWindowTitle("Lyrics");
    QLabel* lyrics = new QLabel();
    lyrics->setParent(lyrics_window);
    QString str = QString::fromStdString(i.getLyrics());
    lyrics->setText(str);
    lyrics->show();
    lyrics_window->setFixedHeight(750);
    lyrics_window->setFixedWidth(750);
    lyrics_window->open();


}

void MyWindow::sort_ascending_()
{
    this->cont.sort("asc");
    reload_list_data();
}

void MyWindow::play_song()
{
    QItemSelectionModel* select = list1->selectionModel();
    QModelIndexList indexList = select->selectedRows();
    QModelIndex index = indexList.at(0);
    int row = index.row();
    Song s = this->cont.getSongs().getSongs().at(row);
    std::string str = s.getLink();
    std::size_t firstQuotePos = str.find("\"");
    std::size_t lastQuotePos = str.rfind("\"");

    if (firstQuotePos != std::string::npos && lastQuotePos != std::string::npos) {
        std::string extractedText = str.substr(firstQuotePos + 1, lastQuotePos - firstQuotePos - 1);


        QString youtubeLink = QString::fromStdString(extractedText);
        QDesktopServices::openUrl(QUrl(youtubeLink));

    }
    else
    {
        QString youtubeLink = QString::fromStdString(s.getLink());
        QDesktopServices::openUrl(QUrl(youtubeLink));
    }
}

MyWindow::~MyWindow()
{}
