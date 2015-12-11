#!/bin/busybox sh

# TODO: create tar archive

cd modul-src/template/
tar -cf ../../tars/template-1.0.tar.gz *
cd -

cd tars
mv ./* ../../V3/buildroot/dl

