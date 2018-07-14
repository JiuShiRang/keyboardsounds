#include "soundplayer.h"

SoundPlayer::SoundPlayer(QObject* parent) {
  //     m_player.setMedia(QUrl::fromLocalFile("a.mp3"));
  //     m_player.stop();
  m_playerCurrent = 0;
  m_playerCount = 2;
  for (int i = 0; i < m_playerCount; i++) {
    QSharedPointer<QMediaPlayer> player(
        new QMediaPlayer(this, QMediaPlayer::LowLatency));
    m_playerList.append(player);
    player->setMedia(QUrl::fromLocalFile("a.mp3"));
  }
}

SoundPlayer& SoundPlayer::getInstance() {
  static SoundPlayer instance;
  return instance;
}

void SoundPlayer::playByCode(int kCode) {
  //    m_player.stop();
  //      m_player.play();
  m_playerList[m_playerCurrent]->play();
  m_playerCurrent++;
  if (m_playerCurrent >= m_playerCount) {
    m_playerCurrent = 0;
  }
}
