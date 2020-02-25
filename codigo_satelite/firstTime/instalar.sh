sudo usermod -a -G dialout $USER
sudo cp ./*.rules /etc/udev/rules.d/

sudo udevadm control --reload-rules
