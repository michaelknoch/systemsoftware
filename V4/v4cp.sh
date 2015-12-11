#!/bin/busybox sh

# TODO: create tar archive

cd modul-src/template/
tar -cf ../../tars/template.tar *
cd -

cd tars
mv ./* ../../V3/buildroot/dl

