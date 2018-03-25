#include "widget.h"
#include "ui_widget.h"
#include "iostream"
#include <QDebug>
using namespace std;
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //настройка таблицы плейлиста
    m_playlistmodel = new QStandardItemModel(this);

    ui->m_playlistview->setModel(m_playlistmodel);

    //устанавливаем заголовок таблицы
    m_playlistmodel->setHorizontalHeaderLabels(QStringList()<<tr("Audio Track")<<tr("File Path"));

    ui->m_playlistview->hideColumn(1);//скрываем колонку, в которой хранится путь
    ui->m_playlistview->verticalHeader()->setVisible(false);//скрываем нумерацию
    ui->m_playlistview->setSelectionBehavior(QAbstractItemView::SelectRows);//Включаем выделение строк
    ui->m_playlistview->setSelectionMode(QAbstractItemView::SingleSelection);//Разрешаем выделять только одну строку
    ui->m_playlistview->setEditTriggers(QAbstractItemView::NoEditTriggers);//отменить редактирование

    //подгоняем колонку последнего столца tableview
    ui->m_playlistview->horizontalHeader()->setStretchLastSection(true);

    ui->btn_add->setText("Add");
    ui->m_pushbutton_play->setText("Play");
    ui->m_pushbutton_next->setText("Next");
    ui->m_pushbutton_stop->setText("Stop");
    ui->m_pushbutton_prev->setText("Prev");
    //задаем параметры плеер и плейлиста
    m_player = new QMediaPlayer(this);//инициализируем плеер
    m_playlist = new QMediaPlaylist(m_player);//инициализируе плейлист
    m_player->setPlaylist(m_playlist);//устанавливаем плейлист в плеер
    m_player->setVolume(70);//устанавливаем громкость воспроизведения треков
    m_playlist->setPlaybackMode(QMediaPlaylist::Loop);//устанавливаем циклический режим воспроизведения

    //подключаем кнопки управления к слотам
    //навигация по плейлисту осуществляется через view
    //а запуск пауза остановка через плеер
    connect(ui->m_pushbutton_play,&QPushButton::clicked,m_player,&QMediaPlayer::play);
    connect(ui->m_pushbutton_stop,&QPushButton::clicked,m_player,&QMediaPlayer::stop);
    connect(ui->m_pushbutton_next,&QPushButton::clicked,m_playlist,&QMediaPlaylist::next);
    connect(ui->m_pushbutton_prev,&QPushButton::clicked,m_playlist,&QMediaPlaylist::previous);



    //при двойном клике устанавливаем трек в плейлист
    connect(ui->m_playlistview,&QTableView::doubleClicked,[this](const QModelIndex &index){m_playlist->setCurrentIndex(index.row());});
}

Widget::~Widget()
{
    delete ui;
    delete m_playlistmodel;
    delete m_playlist;
    delete m_player;
}

void Widget::on_btn_add_clicked(){
    //QMessa
    qDebug()<<"Debug()";
    // С помощью диалога выбора файлов делаем множественный выбор mp3 файлов
    QStringList files = QFileDialog::getOpenFileNames(this,
                                                      tr("Open files"),
                                                      QString(),
                                                      tr("Audio Files (*.mp3)"));
    //Далее устанавливаем данные по именам и путям файлов
    //в плейлист и таблицу отображающую плейлист
    foreach (QString filePath, files) {
        QList<QStandardItem *> items;
        items.append(new QStandardItem(QDir(filePath).dirName()));
        items.append(new QStandardItem(filePath));
        m_playlistmodel->appendRow(items);
        m_playlist->addMedia(QUrl("file://"+filePath));
        qDebug()<<filePath;
    }
}
