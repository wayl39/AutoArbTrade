#ifndef FILESYSTEMWATCHER_H
#define FILESYSTEMWATCHER_H

#include <QObject>
#include <QMap>
#include <QFileSystemWatcher>

class FileSystemWatcher : public QObject
{
    Q_OBJECT
public:
    static void addWatchPath(QString path);

signals:

public slots:
    void directoryUpdated(const QString &path); // 目录更新时调用
    void fileUpdated(const QString& path); // 文件被修改时调用
private:
    explicit FileSystemWatcher(QObject *parent = nullptr);

    static FileSystemWatcher *m_pInstance; // 单例
    QFileSystemWatcher *m_pSystemWatcher;
    QMap<QString, QStringList> m_currentContentsMap; // 当前每个监控的内容目录列表
};

#endif // FILESYSTEMWATCHER_H
