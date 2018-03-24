#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QDir>
#include <QTableView>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    QStandardItemModel *m_playlistmodel;
    QMediaPlayer *m_player;
    QMediaPlaylist *m_playlist;


    QTableView *m_playlistview;
    //***********************************************************************************
    QPushButton *m_pushbutton_play;
    QPushButton *m_pushbutton_stop;
    QPushButton *m_pushbutton_next;
    QPushButton *m_pushbutton_prvw;

    QPushButton *m_pushbutton_add;

    QHBoxLayout *m_hlayout;
    QVBoxLayout *m_vlayout;
private slots:
    void on_btn_add_clicked();
};

#endif // WIDGET_H
