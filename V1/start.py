#!/usr/bin/env python3
# coding: utf8

#============================================================================
#   Assignment: start.py SYSO
#
#       Author:  Timo Weiß, Michael Knoch
#
#   Instructor:  Michael Maechtel, Michael Offergeld
#         Date:  20.10.2015
#
#============================================================================

import os
import sys
import getopt

config = False

destConfigPath = './linux-4.2.3/.config'
originConfigPath = './.config'


def init():
	print('Script started...')
	# download and extract kernel

	if not os.path.isfile('linux-4.2.3.tar.xz'):
		os.system('wget https://cdn.kernel.org/pub/linux/kernel/v4.x/linux-4.2.3.tar.xz')
		print('Download Success')
	else:
		print('file already exists')

	# TODO check if linux-4.2.3/ already exists
	os.system('tar xfv linux-4.2.3.tar.xz')
	print('extract Success')

	# run allnoconfig & menuconfig when .config is not present
	if config:
		os.system('cd linux-4.2.3 && make ARCH=i386 allnoconfig')
		os.system('cd linux-4.2.3 && make ARCH=i386 menuconfig')

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
		

def main(argv):
	try:
		opts, args = getopt.getopt(argv,"c", ["config"])
	except getopt.GetoptError:
		print 'argument parse error'
		sys.exit(2)
	for opt, arg in opts:
		if opt in ("-c", "--config"):
			config = True
			print 'new config'
	
	print 'start default'
	init()
	sys.exit(0)			

if __name__ == "__main__":
	main(sys.argv[1:])
