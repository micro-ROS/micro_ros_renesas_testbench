sudo apt update
sudo apt install wget
echo "export PATH=/home/username/Downloads/gcc-arm-none-eabi-10.3-2021.10-aarch64-linux/gcc-arm-none-eabi-10.3-2021.10/:$PATH" >> ~/.bashrc

if [ ! -d ~/toolchain ]
then
    mkdir ~/toolchain && cd ~/toolchain
    wget https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-aarch64-linux.tar.bz2
    tar -xvjf gcc-arm-none-eabi-10.3-2021.10-aarch64-linux.tar.bz2
    echo "export PATH=~/toolchain/gcc-arm-none-eabi-10.3-2021.10/bin:$PATH" >> ~/.bashrc
else
    echo "Already installed ARM toolchain"
fi
