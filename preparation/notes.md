### ramfs
* The amount of code required to implement ramfs is tiny, because all the
work is done by the existing Linux caching infrastructure. Basically,
you're mounting the disk cache as a filesystem.  
* hat kein size limit, wächst dynamisch und kann wenn nicht kontrolliert den ganzen RAM füllen
### tmpfs
* hat ein size limit, wächst nicht dynamisch mit und daten können in den swap space geschrieben werden
### ramdisk
* virtuelles Block Device im RAM
* braucht einen filesystem driver(z.B. ext2) um Daten zu formatieren bzw. interpretieren
### rootfs
* spezielle Instanz von ramfs(oder tmpfs wenn aktiviert)
* kann nicht unmounted werde
* die meisten systeme mounten ein anderes filesystem über rootfs
### initramfs
gzipped cpio archiv welches in rootfs extracted wird wenn der kernel bootet
#### Unterschied intramfs und initrd
* initrd war immer ein seperates file, initramfs ist in das kernel image gelinked über CONFIG_INITRAMFS_SOURCE 
* initrd gzipped filesystem image(fileformat z.B. ext2, treiber notwendig), initramfs gzipped cpio archiv
* initrd: pivot_root und unmount disk. initramfs: switch_ root
#### Externes initramfs image
Wenn der kernel initrd support hat kann dem Kernel ein externes gpio.gz image übergeben werden anstatt einem initrd. Der Kernell erkennt den Typ automatisch und extrahiert das archiv in das rootfs

##Device Tree
### Ohne Device Tree
* Kernel enthält die komplette Beschreibung der Hardware
* bootloader lädt ein einziges Kernel Image (uImage oder zImage) und führt es aus
### Mit Device Tree
* Kernel enthält keine Beschreibung der Hardware mehr, Beschreibung jetzt im device tree blob(binary)
* bootloader lädt 2 binaries in den RAM, Kernel Image und dtb (aus arch/arm/boot/dts)
### Was ist der Device Tree
* Datenstruktur mit nodes welche die physikalischen devices in einem System beschreibt
 