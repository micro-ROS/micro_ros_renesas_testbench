sudo apt update
sudo apt install wget
echo "export PATH=/home/username/Downloads/gcc-arm-none-eabi-10-2020-q4-major-x86_64-linux/gcc-arm-none-eabi-10-2020-q4-major/:$PATH" >> ~/.bashrc

if [ ! -d ~/toolchain ]
then
    mkdir ~/toolchain && cd ~/toolchain
    # wget https://developer.arm.com/-/media/Files/downloads/gnu-rm/9-2020q2/gcc-arm-none-eabi-9-2020-q2-update-x86_64-linux.tar.bz2
    # tar -xvjf gcc-arm-none-eabi-9-2020-q2-update-x86_64-linux.tar.bz2
    wget https://developer.arm.com/-/media/Files/downloads/gnu-rm/9-2020q2/gcc-arm-none-eabi-9-2020-q2-update-aarch64-linux.tar.bz2
    tar -xvjf gcc-arm-none-eabi-9-2020-q2-update-aarch64-linux.tar.bz2
    echo "export PATH=~/toolchain/gcc-arm-none-eabi-9-2020-q2-update/bin:$PATH" >> ~/.bashrc
else
    echo "Already installed ARM toolchain"
fi
