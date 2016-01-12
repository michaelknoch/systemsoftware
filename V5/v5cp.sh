#!/bin/busybox sh

# TODO: create tar archive

cd modul-src/
tar -cvzf ../tars/template-1.0.tar.gz template
tar -cvzf ../tars/access-1.0.tar.gz access
tar -cvzf ../tars/buf-1.0.tar.gz buf
tar -cvzf ../tars/kthread-1.0.tar.gz kthread
tar -cvzf ../tars/lock-1.0.tar.gz lock
tar -cvzf ../tars/myzero-1.0.tar.gz myzero
tar -cvzf ../tars/open_once-1.0.tar.gz open_once
tar -cvzf ../tars/tasklet-1.0.tar.gz tasklet
tar -cvzf ../tars/timer-1.0.tar.gz timer
tar -cvzf ../tars/wq-1.0.tar.gz wq
cd -


cd tars
mv ./* ../../V3/buildroot/dl

