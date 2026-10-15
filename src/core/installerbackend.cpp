#include "installerbackend.h"
#include <QFile>

InstallerBackend::InstallerBackend(QObject *parent) : QObject(parent), m_isInstalling(false) {
    m_process = new QProcess(this);
    m_process->setProcessChannelMode(QProcess::MergedChannels);

    // Hubungkan sinyal QProcess untuk membaca log terminal secara real-time
    connect(m_process, &QProcess::readyReadStandardOutput, this, &InstallerBackend::onProcessReadyRead);
    connect(m_process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &InstallerBackend::onProcessFinished);
    
    appendLog("Sistem Siap. Masukkan lokasi file .owl untuk diinstal.");
}

QString InstallerBackend::logText() const { return m_logText; }
bool InstallerBackend::isInstalling() const { return m_isInstalling; }

void InstallerBackend::appendLog(const QString &message) {
    m_logText += message + "\n";
    emit logTextChanged();
}

void InstallerBackend::startInstall(const QString &filePath) {
    if (m_isInstalling) return;

    // Menghilangkan prefix "file://" jika file di-drag & drop dari GUI
    QString cleanPath = filePath;
    if (cleanPath.startsWith("file://")) cleanPath = cleanPath.mid(7);

    if (!QFile::exists(cleanPath) || !cleanPath.endsWith(".owl")) {
        appendLog("[ERROR] File .owl tidak valid atau tidak ditemukan di: " + cleanPath);
        return;
    }

    m_isInstalling = true;
    emit isInstallingChanged();
    
    m_logText = ""; // Bersihkan log sebelumnya
    appendLog("[INFO] Memulai instalasi paket: " + cleanPath);

    // Memanggil CLI owl-install yang sebelumnya sudah kita buat di sistem
    QString command = QString("sudo owl-install \"%1\"").arg(cleanPath);
    m_process->start("bash", QStringList() << "-c" << command);
}

void InstallerBackend::onProcessReadyRead() {
    QString output = m_process->readAllStandardOutput().trimmed();
    if (!output.isEmpty()) {
        appendLog(output);
    }
}

void InstallerBackend::onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus) {
    m_isInstalling = false;
    emit isInstallingChanged();
    
    if (exitCode == 0 && exitStatus == QProcess::NormalExit) {
        appendLog("\n[SUKSES] Instalasi Selesai!");
    } else {
        appendLog("\n[GAGAL] Instalasi berhenti dengan kode error: " + QString::number(exitCode));
    }
}