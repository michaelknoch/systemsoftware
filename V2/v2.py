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


destConfigPath = './linux-4.2.3/.config'
originConfigPath = './.config'

def initFs():
	

	os.system('rm -rf ./initfs')
	os.system('rm -rf ./initramfs_data.cpio.gz')

	os.system('gcc -static -m32 sysinfo.c -o sysinfo')

	os.makedirs('initfs/dev')
	os.makedirs('initfs/bin')
	os.makedirs('initfs/sbin')
	os.makedirs('initfs/etc')
	os.makedirs('initfs/tmp')
	os.makedirs('initfs/var')
	os.makedirs('initfs/sys')
	os.makedirs('initfs/proc')
	os.makedirs('initfs/usr/bin')
	os.system('cp init.sh initfs/init')
	os.system('cp sysinfo initfs/bin/sysinfo')
	os.system('cp busybox initfs/bin/busybox')
	os.system('find ./initfs -type f -exec chmod 777 {} \;')
	os.system('cd initfs && find . | cpio -o -H newc | gzip > ../initramfs_data.cpio.gz')
	os.system('rm -rf ./initfs')

def init():
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

def build():
	os.system('cd linux-4.2.3 && make ARCH=arm CROSS_COMPILE=armv7j-rpi-linux-gnueabihf -j4')

def copyInitFs():
	os.system('cp initfs linux-4.2.3/')	

def runQemu():
	# TODO: -dtb
	os.system('qemu-system-arm -M vexpress-a9 -kernel linux-4.2.3/arch/arm/boot/bzImage -nographic -serial stdio -append "console=ttyAMA0" -initrd ./initramfs_data.cpio.gz')

def copyConfigFile(into=False):
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
	# getting git repo busybox 1_24
	os.system('git clone http://git.busybox.net/busybox 1_24_stable')
	os.system('cp .busybox_config busybox/.config')
	os.system('cd busybox && make ARCH=arm CROSS_COMPILE=armv7j-rpi-linux-gnueabihf')
	print "lololo"

def main(argv):
	global config
	global useExistingConfig
	global generateBusyBox

	try:
		opts, args = getopt.getopt(argv, "abcde", ["dn", "pa", "cp", "co", "qe"])
	except getopt.GetoptError:
		print 'argument parse error'
		sys.exit(2)
	for opt, arg in opts:

		# Download Quellen
		if opt in ("-a", "--dn"):
			config = True
			print 'new config'

		# Patchen von Quellen
		elif opt in ("-b", "--pa"):
			config = True
			useExistingConfig = True
		# Kopieren Ihrer GitLab Sourcen
		elif opt in ("-c", "--cp"):
			generateBusyBox = True

		# Kopieren Ihrer GitLab Sourcen
		elif opt in ("-d", "--co"):
			generateBusyBox = True

		# Qemu starten + Fenster mit Terminal zur seriellen Schnittstelle
		elif opt in ("-e", "--qe"):
			generateBusyBox = True
		else:
			print 'running default'

	print opts

	return

	if generateBusyBox is True:
		buildBusyBox()
		return

	if config is True:
		makeConfig()
	else:
		init()
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
