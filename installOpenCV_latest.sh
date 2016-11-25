#!/bin/bash

sudo apt install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
sudo apt install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev

#git clone https://github.com/Itseez/opencv.git
#git clone https://github.com/Itseez/opencv_contrib.git

mkdir ./opencv/release/
cd ./opencv/release/

cmake -D CMAKE_BUILD_TYPE=RELEASE \
      -D CMAKE_INSTALL_PREFIX=/usr/local \
      -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules \
       ..

make -j 7 # runs 7 jobs in parallel

sudo make install
