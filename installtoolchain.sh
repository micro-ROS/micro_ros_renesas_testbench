# https://developer.arm.com/-/media/Files/downloads/gnu-rm/9-2020q2/gcc-arm-none-eabi-9-2020-q2-update-x86_64-linux.tar.bz2
# https://developer.arm.com/-/media/Files/downloads/gnu-rm/9-2020q2/gcc-arm-none-eabi-9-2020-q2-update-aarch64-linux.tar.bz2

sudo apt update
sudo apt install wget

if [ ! -d ~/toolchain ]
then
    mkdir ~/toolchain && cd ~/toolchain
    wget https://developer.arm.com/-/media/Files/downloads/gnu-rm/9-2020q2/gcc-arm-none-eabi-9-2020-q2-update-x86_64-linux.tar.bz2
    tar -xvjf gcc-arm-none-eabi-9-2020-q2-update-x86_64-linux.tar.bz2
    echo "export PATH=$(pwd)/gcc-arm-none-eabi-9-2020-q2-update/bin:$PATH" >> ~/.bashrc
else
    echo "Already installed ARM toolchain"
fi