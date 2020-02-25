#Permisos USB
sudo usermod -a -G dialout $USER
sudo cp ./*.rules /etc/udev/rules.d/

sudo udevadm control --reload-rules


#Librerías necesarias OpenOCD
sudo apt -y install make
sudo apt -y install libtool
sudo apt -y install pkg-config
sudo apt -y install libusb-0.1
sudo apt -y install aclocal
sudo apt -y install autotools-dev
sudo apt -y install automake

#Open OCD
sudo apt -y purge openocd

git clone https://github.com/ntfreak/openocd.git openocd
cd openocd
./bootstrap
./configure
make
sudo make install
