

make
mv sysinfo ./7

./../V3/buildroot/package/ipkg/ipkg-build ./7/

cp 7/CONTROL/control /srv/http/syso/7/Packages
cp syso-systeminfo_0.1_arm.ipk /srv/http/syso/7/syso_systeminfo.ipkg 
