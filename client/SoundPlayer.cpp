#include "SoundPlayer.h"

#include <QtCore/QObject>
#include <QDebug>
#include <gluon/audio/player.h>
#include <gluon/audio/sound.h>

SoundPlayer::SoundPlayer(QObject *parent)
    : QObject(parent)
{
    m_player = new GluonAudio::Player(this);
    m_player->setVolume(1.0);
}

SoundPlayer::~SoundPlayer()
{
    delete m_player;
    qDeleteAll(m_sounds);
}

QStringList SoundPlayer::soundsPlaying() const
{
    return m_soundsPlaying;
}

void SoundPlayer::addSong(const QString &soundFile)
{
    m_player->append(soundFile);
}

void SoundPlayer::addSound(const QString &soundFile, const QString &name, bool loop)
{
    GluonAudio::Sound *sound = new GluonAudio::Sound(soundFile);
    sound->setLoop(loop);
    m_sounds[name] = sound;

    connect(sound, SIGNAL(stopped()), this, SLOT(onSoundStopped()));
}

void SoundPlayer::stopSong()
{
    m_player->stop();
}

void SoundPlayer::stopSound(const QString &name)
{
    GluonAudio::Sound *sound = m_sounds[name];

    if (sound && sound->isPlaying())
    {
        m_soundsPlaying.removeAll(name);
        m_soundsPendingStop.append(name);
        sound->stop();
    }
}

void SoundPlayer::stopAll()
{
    stopSong();

    foreach (const QString &sound, m_soundsPlaying)
    {
        stopSound(sound);
    }
}

void SoundPlayer::onSoundStopped()
{
    GluonAudio::Sound *sound = (GluonAudio::Sound *)sender();

    QString name = m_sounds.key(sound);
    m_soundsPlaying.removeAll(name);
}

void SoundPlayer::playLoop()
{
    m_player->setLoop(true);
    m_player->play();
}

void SoundPlayer::playSound(const QString &name)
{
    GluonAudio::Sound *sound = m_sounds[name];

    if (sound && !sound->isPlaying())
    {
        m_soundsPlaying.append(name);
        sound->play();
    }
}

void SoundPlayer::setVolume(qreal volume)
{
    m_player->setVolume(volume);
}
