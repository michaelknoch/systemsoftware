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

print('Script started...')

# download and extract kernel

if not os.path.isfile('linux-4.2.3.tar.xz'):
	os.system('wget https://cdn.kernel.org/pub/linux/kernel/v4.x/linux-4.2.3.tar.xz')
	print('Download Success')
else:
	print('file already exists')

os.system('tar xfv linux-4.2.3.tar.xz')
print('extract Success')

# run allnoconfig & menuconfig when .config is not present
if not os.path.isfile('linux-4.2.3/.config')
	os.system('cd linux-4.2.3 && make ARCH=i386 allnoconfig')
	os.system('cd linux-4.2.3 && make ARCH=i386 menuconfig')

