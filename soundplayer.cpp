#include "soundplayer.h"

SoundPlayer::SoundPlayer(QObject* parent)
    : QObject(parent)
{
    //    m_playerCurrent = 0;
    //    m_playerCount = 2;
    //    for (int i = 0; i < m_playerCount; i++) {
    //        QSharedPointer<QMediaPlayer> player(
    //            new QMediaPlayer(this, QMediaPlayer::LowLatency));
    //        m_playerList.append(player);
    //        player->setMedia(QUrl::fromLocalFile("a.mp3"));
    //    }
    QDir dir("sounds");
    QFileInfoList files = dir.entryInfoList(QDir::Files | QDir::Readable);
    QSet<QString> supportedSuffixes;
    supportedSuffixes << "mp3"
                      << "wav"
                      << "aac";
    for (int i = 0; i < files.size(); ++i) {
        if (!supportedSuffixes.contains(files.at(i).suffix())) {
            continue;
        }
        int code = files.at(i).baseName().toInt();
        if (0 == code) {
            continue;
        }
        QFile file(files.at(i).absoluteFilePath());
        if (!file.open(QIODevice::ReadOnly)) {
            continue;
        }
        QSharedPointer<QBuffer> buffer(new QBuffer(this));
        buffer->setData(file.readAll());
        buffer->open(QIODevice::ReadOnly);
        m_soundBuffers.insert(code, buffer);
    }
}

SoundPlayer& SoundPlayer::getInstance()
{
    static SoundPlayer instance;
    return instance;
}

void SoundPlayer::playByCode(int kCode)
{
    //    m_player.stop();
    QMediaPlayer& player = m_playAorB ? m_playerA : m_playerB;
    m_playAorB = !m_playAorB;
    player.setMedia(QMediaContent(), m_soundBuffers.value(kCode).data());
    player.play();
    //    m_playerList[m_playerCurrent]->play();
    //    m_playerCurrent++;
    //    if (m_playerCurrent >= m_playerCount) {
    //        m_playerCurrent = 0;
    //    }
}
