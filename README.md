Berikut adalah langkah-langkah detail untuk menyiapkan skrip installer OwlOS dan cara menggunakannya di Raspberry Pi:

1. Membuat Script Package Manager (owl-install) di Raspberry Pi
Masuk ke terminal Raspberry Pi Anda (OwlOS), lalu buat file skrip global baru bernama owl-install:

Bash
sudo nano /usr/local/bin/owl-install
Copy dan paste kode skrip package manager berikut ke dalam editor:

Bash
#!/bin/bash

# Pastikan file argumen diberikan
if [ -z "$1" ]; then
    echo "Penggunaan: owl-install <nama_aplikasi.owl>"
    exit 1
fi

OWL_PACKAGE=$1

# Validasi ekstensi file harus .owl
if [[ "$OWL_PACKAGE" != *.owl ]]; then
    echo "Error: File harus berekstensi .owl"
    exit 1
fi

# Validasi keberadaan file
if [ ! -f "$OWL_PACKAGE" ]; then
    echo "Error: File $OWL_PACKAGE tidak ditemukan."
    exit 1
fi

TMP_DIR="/tmp/owl_install_$(date +%s)"
mkdir -p $TMP_DIR

echo "Mengekstrak paket $OWL_PACKAGE..."
# Ekstrak file tar.gz (.owl) ke folder temporary
tar -xzvf "$OWL_PACKAGE" -C $TMP_DIR > /dev/null

# Jalankan skrip instalasi internal jika ada
if [ -f "$TMP_DIR/install.sh" ]; then
    echo "Menjalankan skrip instalasi paket..."
    cd $TMP_DIR
    sudo chmod +x install.sh
    sudo ./install.sh
else
    echo "Error: Skrip instalasi di dalam paket .owl tidak ditemukan."
fi

# Bersihkan file temporary
rm -rf $TMP_DIR
echo "Proses instalasi selesai!"
Simpan dan keluar dari editor (Ctrl + O, Enter, lalu Ctrl + X).

Setelah itu, berikan hak akses eksekusi agar perintah ini bisa dijalankan secara global di seluruh direktori OwlOS:

Bash
sudo chmod +x /usr/local/bin/owl-install
2. Cara Mendeteksi dan Menginstal File .owl di Raspberry Pi
Setelah utilitas owl-install terpasang di OwlOS, Anda dapat dengan mudah mendeteksi, mentransfer, dan menginstal aplikasi kapan saja.

Pindahkan File .owl ke Raspberry Pi
Kirim file hasil build Anda (misalnya SmartHomeApp.owl) dari komputer PC/WSL ke Raspberry Pi menggunakan scp atau media penyimpanan USB:

Bash
scp SmartHomeApp.owl pi@<IP_RASBERRY_PI>:/home/pi/
Jalankan Perintah Instalasi
Masuk ke terminal Raspberry Pi, arahkan ke direktori tempat file .owl berada, lalu cukup jalankan perintah:

Bash
owl-install SmartHomeApp.owl
Utilitas owl-install akan otomatis mendeteksi file, mengekstrak isinya, menyalin binary aplikasi ke direktori sistem (/opt/), mendaftarkannya ke systemd service, dan menjalankan aplikasi secara instan di atas framebuffer/EGLFS OwlOS Anda.
