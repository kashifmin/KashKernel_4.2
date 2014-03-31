#Export CROSS_COMPILE to point toolchain
export CROSS_COMPILE=/root/android/toolchain-4.6.3/bin/arm-linux-androideabi-

sudo TARGET_PRODUCT=wiko TARGET_BUILD_VARIANT=user MTK_ROOT_CUSTOM=../mediatek/custom/ make

../mediatek/build/tools/mkimage arch/arm/boot/zImage KERNEL > out/wiko/zImage_p

#Modules part
make TARGET_BUILD_VARIANT=user INSTALL_MOD_STRIP=1 INSTALL_MOD_PATH=./out/wiko/system INSTALL_MOD_DIR=./out/wiko/system android_modules_install

#Repack part - You need to set PATH var correctly poiting to a directory with https://github.com/bgcngm/mtk-tools.git and chmod +x mkbootimg
#You need ramdisk directory too
cd ../../../mtktools
./repack-MT65xx.pl -boot ../android/4.2_kernel/kernel/out/wiko/zImage_p ramdisk ../android/4.2_kernel/kernel/out/wiko/boot.img
