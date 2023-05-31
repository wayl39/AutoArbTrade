#include "FileSystemWatcher.h"
#include <QDir>
#include <QFileInfo>
#include <QDebug>

FileSystemWatcher* FileSystemWatcher::m_pInstance = Q_NULLPTR;

void FileSystemWatcher::addWatchPath(QString path)
{
    qDebug() << __FUNCTION__ << QString("add to watch %1").arg(path);
    // 添加监控路径
    m_pInstance->m_pSystemWatcher->addPath(path);

    // 如果添加路径是一个目录，保存当前内容列表
    QFileInfo file(path);
    if (file.isDir()){
        const QDir dirw(path);
        m_pInstance->m_currentContentsMap[path] = dirw.entryList(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files, QDir::DirsFirst);
    }
}

// 只要任何监控的目录更新（添加、删除、重命名）
void FileSystemWatcher::directoryUpdated(const QString &path)
{
    qDebug() << __FUNCTION__ << QString("Directory updated %1").arg(path);
    // 比较最新的内容和保存的内容找出区别（变化）
    QStringList currEntryList = m_currentContentsMap[path];
    const QDir dir(path);

    QStringList newEntryList = dir.entryList(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files, QDir::DirsFirst);

    QSet<QString> newDirSet = QSet<QString>(newEntryList.begin(), newEntryList.end());
    QSet<QString> currentDirSet = QSet<QString>(currEntryList.begin(), currEntryList.end());

    // 添加了文件
    QSet<QString> newFiles = newDirSet - currentDirSet;
    QStringList newFile = newFiles.values();

    // 文件已被移除
    QSet<QString> deletedFiles = currentDirSet - newDirSet;
    QStringList deleteFile = deletedFiles.values();

    // 更新当前设置
    m_currentContentsMap[path] = newEntryList;

    if (!newFile.isEmpty() && !deleteFile.isEmpty()){
        // 文件、目录重命名
        if ((newFile.count() == 1) && (deleteFile.count() == 1)){
            qDebug() << __FUNCTION__ << QString("File Renamed from %1 to %2").arg(deleteFile.first()).arg(newFile.first());
        }
    }
    else {
        // 添加新文件、目录至Dir
        if (!newFile.isEmpty()){
            qDebug() << __FUNCTION__ <<"New Files/Dirs added: " << newFile;

            foreach(QString file, newFile){
                // 处理操作每个新文件...
            }
        }
    }

    // 从Dir中删除文件/目录
    if (!deleteFile.isEmpty()){
        qDebug() << __FUNCTION__ << "Files/Dirs deleted:" << deleteFile;

        foreach(QString file, deleteFile){
            // 处理操作每个被删除的文件...
        }
    }
}

void FileSystemWatcher::fileUpdated(const QString &path)
{
    QFileInfo file(path);
    QString strPath = file.absolutePath();
    QString strName = file.fileName();

    qDebug() << __FUNCTION__ << QString("The file %1 at path %2 is updated").arg(strName).arg(strPath);
    emit signalFileChange(file.absoluteFilePath());
}

FileSystemWatcher::FileSystemWatcher(QObject *parent) : QObject(parent)
{

}

FileSystemWatcher *FileSystemWatcher::pInstance()
{
    if (m_pInstance == Q_NULLPTR){
        m_pInstance = new FileSystemWatcher();
        m_pInstance->m_pSystemWatcher = new QFileSystemWatcher();
        // 连接 QFileSysteWatcher的directoryChange和fileChanged信号到相应的槽
        connect(m_pInstance->m_pSystemWatcher, &QFileSystemWatcher::directoryChanged, m_pInstance, &FileSystemWatcher::directoryUpdated);
        connect(m_pInstance->m_pSystemWatcher, &QFileSystemWatcher::fileChanged, m_pInstance, &FileSystemWatcher::fileUpdated);
    }
    return m_pInstance;
}
