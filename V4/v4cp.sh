#!/bin/busybox sh

# TODO: create tar archive

cd modul-src/
tar -cvzf ../tars/template-1.0.tar.gz template
tar -cvzf ../tars/openclose-1.0.tar.gz openclose
tar -cvzf ../tars/access-1.0.tar.gz access
cd -


cd tars
mv ./* ../../V3/buildroot/dl

