#!/bin/busybox sh

# TODO: create tar archive

cd modul-src/
tar -cvzf ../tars/template-1.0.tar.gz template/
cd -

cd tars
mv ./* ../../V3/buildroot/dl

