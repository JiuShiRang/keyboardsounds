#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <QDir>
#include <QHash>
#include <QMediaPlayer>
#include <QObject>
#include <QSharedPointer>
#include <QString>
#include <QUrl>
#include <QVector>
#include <QFile>
#include <QBuffer>

class SoundPlayer : public QObject {
    Q_OBJECT
      QMediaPlayer m_player;
//      QMediaContent m_defaultContent;  // beep?
      QHash<int, QSharedPointer<QBuffer>> m_soundBuffers;

//    QVector<QSharedPointer<QMediaPlayer>> m_playerList;
//    int m_playerCount;
//    int m_playerCurrent;

public:
    explicit SoundPlayer(QObject* parent = nullptr);

    static SoundPlayer& getInstance();

    void playByCode(int kCode);

signals:

public slots:
};

#endif // SOUNDPLAYER_H
