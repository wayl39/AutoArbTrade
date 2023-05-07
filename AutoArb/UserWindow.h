#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileInfo>
#include <QTimer>
#include <QDateTime>

namespace Ui {
class UserWindow;
}

class UserWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserWindow(QWidget *parent = nullptr);
    ~UserWindow();

    QString clientId() const;
    void setClientId(const QString &clientId);

    void requestLog();

    QString getFilePath() const;
    void setFilePath(const QString &filePath);

public slots:
    void slotAddStragetyClicked();

    void slotDeleteStragetyClicked();

    void slotAddRiskClicked();

    void slotDeleteRiskClicked();

    void slotLogRspMsg(const QVariantMap& dataMap);
private slots:
    void slotTimeOut();
private:
    void createWidget();
    void createLayout();
    void createConncet();

    void getFileLog();

private:
    Ui::UserWindow *ui;
    QString m_clientId;
    QString m_filePath;
    QFile *m_logFile{Q_NULLPTR};
    QTimer *m_timer{Q_NULLPTR};
    qlonglong m_fileSize;
    QFileInfo m_fileInfo;
    QDateTime m_passTime;

};

#endif // USERWINDOW_H
