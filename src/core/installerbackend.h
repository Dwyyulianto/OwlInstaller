#ifndef INSTALLERBACKEND_H
#define INSTALLERBACKEND_H

#include <QObject>
#include <QString>
#include <QProcess>

class InstallerBackend : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString logText READ logText NOTIFY logTextChanged)
    Q_PROPERTY(bool isInstalling READ isInstalling NOTIFY isInstallingChanged)

public:
    explicit InstallerBackend(QObject *parent = nullptr);

    QString logText() const;
    bool isInstalling() const;

    // Fungsi yang dipanggil dari tombol QML
    Q_INVOKABLE void startInstall(const QString &filePath);

signals:
    void logTextChanged();
    void isInstallingChanged();

private slots:
    void onProcessReadyRead();
    void onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);

private:
    void appendLog(const QString &message);

    QString m_logText;
    bool m_isInstalling;
    QProcess *m_process;
};

#endif // INSTALLERBACKEND_H