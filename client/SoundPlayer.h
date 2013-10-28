#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <QtCore/QHash>
#include <QtCore/QStringList>

namespace GluonAudio {
    class Player;
    class Sound;
}

class SoundPlayer : public QObject
{
    Q_OBJECT
public:
    explicit SoundPlayer(QObject *parent = 0);
    ~SoundPlayer();

    QStringList soundsPlaying() const;

    void addSong(const QString &soundFile);
    void addSound(const QString &soundFile, const QString &name, bool loop = false);
    void playLoop();
    void playSound(const QString &name);
    void stopAll();
    void stopSong();
    void stopSound(const QString &name);

    // Set volume between 0.0 and 1.0
    void setVolume(qreal volume = 1.0);

private:
    GluonAudio::Player *m_player;
    QHash<QString, GluonAudio::Sound *> m_sounds;
    QStringList m_soundsPlaying;
    QStringList m_soundsPendingStop;

private slots:
    void onSoundStopped();
};

#endif // SOUNDPLAYER_H
