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
      QMediaPlayer m_playerA;
      QMediaPlayer m_playerB;
      bool m_playAorB;
      QHash<int, QSharedPointer<QBuffer>> m_soundBuffers;

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
