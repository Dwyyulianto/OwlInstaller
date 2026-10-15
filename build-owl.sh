#!/bin/bash

# Nama aplikasi target
APP_NAME="OwlInstaller"
ICON_NAME="icon.png" # Ubah menjadi icon.svg jika file Anda berformat SVG

echo "Memulai kompilasi $APP_NAME..."

# 1. Proses Build & Compile dengan CMake
mkdir -p build 
cd build 
cmake .. 
make -j4
cd ..

# 2. Siapkan Struktur Folder Packaging (pkg)
echo "Menyiapkan struktur paket..."
mkdir -p pkg/bin
cp build/$APP_NAME pkg/bin/
cp $ICON_NAME pkg/bin/ # Menyalin ikon kustom dari proyek ke dalam paket target

# 3. Buat file .desktop
echo "Membuat file shortcut desktop..."
cat <<EOF > pkg/$APP_NAME.desktop
[Desktop Entry]
Name=OwlInstaller
Comment=OwlOS Package Installer
Exec=/opt/$APP_NAME/$APP_NAME
Icon=/opt/$APP_NAME/$ICON_NAME
Terminal=false
Type=Application
Categories=System;Utility;
EOF

# 4. Buat Skrip Instalasi Internal (install.sh)
echo -e "#!/bin/bash\n\
echo \"Menyalin file aplikasi dan ikon ke /opt/$APP_NAME...\"\n\
mkdir -p /opt/$APP_NAME\n\
cp -r bin/* /opt/$APP_NAME/\n\
echo \"Mendaftarkan aplikasi ke menu desktop...\"\n\
cp $APP_NAME.desktop /usr/share/applications/\n\
chmod 644 /usr/share/applications/$APP_NAME.desktop\n\
echo \"Instalasi $APP_NAME di sistem berhasil!\"" > pkg/install.sh

chmod +x pkg/install.sh

# 5. Kompres folder pkg menjadi file .owl
echo "Membuat paket $APP_NAME.owl..."
cd pkg 
tar -czvf ../$APP_NAME.owl * 
cd ..

# 6. Bersihkan folder temporary pkg
rm -rf pkg

echo "Sukses! Berhasil membuat $APP_NAME.owl"