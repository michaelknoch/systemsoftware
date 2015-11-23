#!/usr/bin/env python
# coding: utf8

#============================================================================
#   Assignment: v2.py SYSO
#
#       Author:  Timo Weiß, Michael Knoch
#
#   Instructor:  Michael Maechtel, Michael Offergeld
#         Date:  03.11.2015
#
#============================================================================

import os
import sys
import getopt

config = False
useExistingConfig = False
generateBusyBox = False

downloadSources = False
patchSources = False
compileSources = False
checkoutSources = False
startQemu = False
experimentell = False


destConfigPath = './linux-4.2.3/.config'
originConfigPath = './.config'

def initFs():
	

	#os.system('rm -rf ./initfs')
	os.system('rm -rf ./initramfs_data.cpio.gz')

	#os.system('/group/SYSO_WS1516/armv6j-rpi-linux-gnueabihf/bin/armv6j-rpi-linux-gnueabihf-gcc -static sysinfo.c -o sysinfo')
	os.system('make cc=/group/SYSO_WS1516/armv6j-rpi-linux-gnueabihf/bin/armv6j-rpi-linux-gnueabihf-gcc sysinfo')

	os.makedirs('initfs/dev')
	os.makedirs('initfs/bin')
	os.makedirs('initfs/sbin')
	os.makedirs('initfs/etc/udhcp')
	os.makedirs('initfs/tmp')
	os.makedirs('initfs/var')
	os.makedirs('initfs/sys')
	os.makedirs('initfs/dev/pts')
	os.makedirs('initfs/proc')
	os.makedirs('initfs/usr/bin')
	os.makedirs('initfs/usr/share/udhcp')
	os.system('cp init.sh initfs/init')
	os.system('cp sysinfo initfs/bin/sysinfo')
	os.system('cp busybox/busybox initfs/bin/busybox')
	os.system('cp udhcp/simple.script initfs/etc/udhcp/simple.script')
	#os.system('cp -r udhcp/ initfs/usr/share/udhcpc/')
	#os.system('cp -r udhcp/ initfs/etc/udhcpc/')
	os.system('find ./initfs -type f -exec chmod 777 {} \;')
	os.system('cd initfs && find . | cpio -o -H newc | gzip > ../initramfs_data.cpio.gz')
	os.system('mkimage -A arm -O linux -T ramdisk -C none -n "U-Boot RamFS" -d initramfs_data.cpio.gz rootfs.cpio.uboot')
	#os.system('rm -rf ./initfs')

def doNewBuildRootStuff():
	os.system('cp -R buildroot/output/images/ ./brImages')
	os.system('mkimage -A arm -O linux -T ramdisk -C none -n "U-Boot RamFS" -d ./brImages/rootfs.tar ./brImages/rootfs.cpio.uboot')
	os.system('mkimage -A arm -O linux -T script -C none -d ./tftpinit.scr.txt ./brImages/tftpboot.scr')
	os.system('cp -R ./brImages/ /srv/tftp/rpi/7/')

def downloadAndExtractKernel():
	print('Script started...')
	# download and extract kernel

	if not os.path.isfile('linux-4.2.3.tar.xz'):
		os.system('wget https://cdn.kernel.org/pub/linux/kernel/v4.x/linux-4.2.3.tar.xz')
		print('Download Success')
	else:
		print('file already exists')

	# TODO check if linux-4.2.3/ already exists
	if not os.path.exists('linux-4.2.3'):
		os.system('tar xfv linux-4.2.3.tar.xz')
		print('extract Success')

def downloadAndExtractBusybox():
	os.system('git clone http://git.busybox.net/busybox')
	os.system('cd busybox && git checkout 1_24_stable')

def makeConfig():
	global config
	global useExistingConfig
	# run allnoconfig & menuconfig when .config is not present
	if config:
		if not useExistingConfig:
			os.system('cd linux-4.2.3 && make ARCH=arm allnoconfig')
		else:
			copyConfigFile(True)
		os.system('cd linux-4.2.3 && make ARCH=arm menuconfig')

def buildKernel():
	os.system('cd linux-4.2.3 && make ARCH=arm CROSS_COMPILE=/group/SYSO_WS1516/armv6j-rpi-linux-gnueabihf/bin/armv6j-rpi-linux-gnueabihf- -j4')

def copyInitFs():
	os.system('cp initfs linux-4.2.3/')

def generateDtbFiles():
	# TODO vexpress
	os.system('cd linux-4.2.3 && make bcm2835-rpi-b.dtb')
	os.system('cp linux-4.2.3/arch/arm/boot/dts/bcm2835-rpi-b.dtb ./')

def runQemu():
	# TODO: -dtb
	os.system('qemu-system-arm -M vexpress-a9 -kernel linux-4.2.3/arch/arm/boot/zImage -nographic -serial stdio -dtb linux-4.2.3/arch/arm/boot/dts/vexpress-v2p-ca9.dtb -monitor telnet:127.0.0.1:2222,server,nowait -append "console=ttyAMA0" -initrd ./initramfs_data.cpio.gz -net nic,macaddr=00:00:00:00:F1:01,vlan=0 -net vde,sock="/tmp/vde2-tap0.ctl",vlan=0')

def patchKernel(into=True):
	# if into True copy config file from current directory into linux-4.2.3
	# otherwise from linux-4.2.3 to current directory
	_from = originConfigPath
	_to = destConfigPath

	if into is False:
		_from = destConfigPath
		_to = originConfigPath
	
	if not os.path.isfile(_from):
		print 'error opening ' + _from + ' file'
		sys.exit(2)
	print 'cp ' + _from + ' ' + _to
	os.system('cp ' + _from + ' ' + _to)
		

def buildBusyBox():
	os.system('cd busybox && make ARCH=arm CROSS_COMPILE=/group/SYSO_WS1516/armv6j-rpi-linux-gnueabihf/bin/armv6j-rpi-linux-gnueabihf-')

def patchBusybox():
	print 'cp .busybox_config busybox/.config'
	os.system('cp .busybox_config busybox/.config')

def patchPatch():
	print 'patch -p1 < linux-smsc95xx_allow_mac_setting.patch'
	os.system('cd linux-4.2.3 && patch -p1 < ../linux-smsc95xx_allow_mac_setting.patch')

def gitCheckoutSources():
	os.system('git checkout HEAD')

def main(argv):
	global config, downloadSources, patchSources, compileSources, checkoutSources, useExistingConfig, generateBusyBox, startQemu, experimentell

	print 'exporting values'
	os.system('export ARCH=arm')
	os.system('export CROSS_COMPILE=/group/SYSO_WS1516/armv6j-rpi-linux-gnueabihf/bin/armv6j-rpi-linux-gnueabihf-')
	os.system('export QEMU_AUDIO_DRV=none')

	try:
		opts, args = getopt.getopt(argv, "abcdefg", ["dn", "pa", "cp", "co", "qe", "cleanall", "exp"])
	except getopt.GetoptError:
		print 'argument parse error'
		sys.exit(2)
	for opt, arg in opts:

		# Download Quellen
		if opt in ("-a", "--dn"):
			
			print 'downloading sources'
			downloadSources = True
			

		# Patchen von Quellen
		elif opt in ("-b", "--pa"):
			patchSources = True
		# Kopieren Ihrer GitLab Sourcen
		elif opt in ("-c", "--cp"):
			checkoutSources = True

		# compile
		elif opt in ("-d", "--co"):
			compileSources = True

		# Qemu starten + Fenster mit Terminal zur seriellen Schnittstelle
		elif opt in ("-e", "--qe"):
			print 'todo --qe'
			startQemu = True

		# cleanup
		elif opt in ("-f", "--cleanall"):
			os.system('rm -rf linux-4.2.3/ linux-4.2.3.tar.xz busybox/')

		# Patchen von Quellen
		elif opt in ("-g", "--exp"):
			experimentell = True


		else:
			print 'running default'

	print opts
	stepIdx = 1

	if experimentell:
		doNewBuildRootStuff()
		return


	if checkoutSources:
		print 'Step ' + str(stepIdx) + ': checkout repo'
		gitCheckoutSources()
		stepIdx = stepIdx + 1		

	if downloadSources:
		print 'Step ' + str(stepIdx) + ': downloading sources'
		downloadAndExtractKernel()
		downloadAndExtractBusybox()
		stepIdx = stepIdx + 1

	if patchSources:
		print 'Step ' + str(stepIdx) + ': patching sources'
		patchKernel()
		patchBusybox()
		patchPatch()
		stepIdx = stepIdx + 1

	if compileSources:
		print 'Step ' + str(stepIdx) + ': compiling sources'
		buildBusyBox()
		initFs()
		buildKernel()
		stepIdx = stepIdx + 1

	if startQemu:
		print 'Step ' + str(stepIdx) + ': run qemu'
		runQemu()
		stepIdx = stepIdx + 1

	return
	if generateBusyBox is True:
		buildBusyBox()
		return

	if config is True:
		makeConfig()
	else:
		downloadAndExtractKernel()
		initFs()
		copyConfigFile(True)
		build()
		runQemu()

	

	#initFs()
	#return

	#print 'start default'
	#init()
	sys.exit(0)			

if __name__ == "__main__":
	main(sys.argv[1:])
