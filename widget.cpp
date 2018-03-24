#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //******инициализируем tableView***//
    m_playlistview = new QTableView;
    //******инициализируем кнопки******//
    m_pushbutton_add = new QPushButton("add");
    m_pushbutton_play = new QPushButton("play");
    m_pushbutton_stop = new QPushButton("stop");
    m_pushbutton_next = new QPushButton("next");
    m_pushbutton_prvw = new QPushButton("prev");

    //*******Инициализируем layout*****//
    m_hlayout = new QHBoxLayout;
    m_vlayout = new QVBoxLayout;

    //*******Добавим кнопки в layout***//
    m_hlayout->addWidget(m_pushbutton_add);
    m_hlayout->addWidget(m_pushbutton_play);
    m_hlayout->addWidget(m_pushbutton_stop);
    m_hlayout->addWidget(m_pushbutton_next);
    m_hlayout->addWidget(m_pushbutton_prvw);
    m_vlayout->addLayout(m_hlayout);
    m_vlayout->addWidget(m_playlistview);

    //добавим layout на widget
    this->setLayout(m_vlayout);

    //настройка таблицы плейлиста
    m_playlistmodel = new QStandardItemModel(this);

    m_playlistmodel->setHorizontalHeaderLabels(QStringList()<<tr("Audio Track")<<tr("File Path"));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btn_add_clicked(){

}
