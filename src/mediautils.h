#pragma once
#include <QAudioFormat>
#include <QCameraDevice>
#include <QJsonObject>
#include <QString>
#include <QImage>
#include <atomic>
#include "edit.h"

namespace media {
struct Format { QSize size; double minFps; double maxFps; int pixelFormat; };
int bestFormat(const QList<Format> &formats);
double targetFps(double minimum, double maximum);
// Stable identity and display text for one advertised camera format.
QString formatKey(const QSize &size, double minFps, double maxFps, int pixelFormat);
QString formatLabel(const QSize &size, double minFps, double maxFps, int pixelFormat);
// The device's formats, biggest first, so the picker reads naturally.
QList<QCameraFormat> sortedFormats(const QCameraDevice &device);
// Index into keys of the format to open: the one saved for this camera if it is
// still offered, otherwise the default pick, otherwise the first. -1 if there are none.
int chooseFormat(const QStringList &keys, const QString &saved, const QString &best);
double peak(const QByteArray &data, const QAudioFormat &format);
QString copyAtomically(const QString &source, const QString &destination);
QString normalizeMp4(const QString &path, double fps);
struct Probe { bool ok = false; QString error; QSize size; double duration = 0; bool audio = false; };
Probe probe(const QString &path);
// Re-encodes the kept ranges of a recording into one MP4, reporting progress on stdout.
QStringList exportArgs(const QString &source, const QString &destination, const QList<edit::Range> &kept, bool audio);
QImage thumbnail(const QString &path, double time, int height, const std::atomic<bool> *cancel);
}
