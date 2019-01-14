
Debian
====================
This directory contains files used to package cryptonodesd/cryptonodes-qt
for Debian-based Linux systems. If you compile cryptonodesd/cryptonodes-qt yourself, there are some useful files here.

## cryptonodes: URI support ##


cryptonodes-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install cryptonodes-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your cryptonodesqt binary to `/usr/bin`
and the `../../share/pixmaps/cryptonodes128.png` to `/usr/share/pixmaps`

cryptonodes-qt.protocol (KDE)

