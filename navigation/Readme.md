# 驱动robosense 16线激光雷达
## 1.下载源码
```
cd ~/catkin_ws/src
git clone https://github.com/RoboSense-LiDAR/ros_rslidar
```
## 2.安装libpcap-dev
```
sudo apt-get install libpcap-dev
```
## 3.更改源码属性
```
cd ~/catkin_ws/src/ros_rslidar/rslidar_drvier
chmod 777 cfg/*
```
```
cd ~/catkin_ws/src/ros_rslidar/rslidar_pointcloud
chmod 777 cfg/*
```
## 4.编译源码
```
cd ~/catkin_ws
catkin_make
```
## 5.设置静态ip地址
将本地ip地址改为192.168.1.102，子网掩码设置为255.255.255.0

## 6.运行节点
```
roslaunch rslidar_pointcloud rs_lidar_16.launch
```
即可见到扫描结果

# 驱动Kinect v2与ROS下的测试
## 1.安装依赖项,默认安装好opencv
```
sudo apt-get install build-essential cmake pkg-config libturbojpeg libjpeg-turbo8-dev mesa-common-dev freeglut3-dev libxrandr-dev libxi-dev
```
## 2.下载libfreenect2驱动：
```
cd ~
git clone https://github.com/OpenKinect/libfreenect2.git
cd libfreenect2
cd depends; ./download_debs_trusty.sh
```
## 3.buit tools安装
```
sudo apt-get install build-essential cmake pkg-config
```
```
sudo apt-get install libusb-1.0-0-dev
```
## Ubuntu 14.04和16.04
```
sudo apt-get install libturbojpeg libjpeg-turbo8-dev
```
## 更高版本
```
sudo apt-get install libturbojpeg0-dev
```
```
sudo apt-get install libglfw3-dev
```
## 4.编译libfreenect2
```
cd ~/libfreenect2
mkdir build && cd build
cmake .. 
make
sudo make install
```
确定以上安装成功

## 5.设定udev rules
```
sudo cp platform/linux/udev/90-kinect2.rules /etc/udev/rules.d/
sudo udevadm control --reload
```
## 6.连接Kinect v2的电源线和usb转接线(注意Kinect v2只能用于USB3的接口！！！),运行kinect2
```
cd ~/libfreenect2/build
./bin/Protonect
```
无错误,显示图像

## 7.iai_kinect2安装
```
cd ~/catkin_ws/src/
git clone https://github.com/code-iai/iai_kinect2.git
cd iai_kinect2
rosdep install -r --from-paths .
cd ~/catkin_ws
catkin_make -DCMAKE_BUILD_TYPE="Release"
```
## 8.测试iai_kinect2包

新终端，执行roscore
```
roscore
```
新终端，执行
```
roslaunch kinect2_bridge kinect2_bridge.launch
```
新终端，执行
```
rosrun kinect2_viewer save_seq hd cloud

```
# 基于激光雷达的slam与导航
## slam建图
### 启动激光雷达：
```
roslaunch scout_bringup open_rslidar.launch 
```
### 启动gmapping建图：
```
roslaunch scout_bringup scout_gmapping.launch 
```
### 用手柄操控下车在场景中走动，扫描建图，完成建图之后保存在scout _description目录下的maps文件夹中
```
cd ~/catkin_ws/src/scout_ros/scout_description/maps/
rosrun map_server map_saver -f map
```
## 导航
### 启动激光雷达：
```
roslaunch scout_bringup open_rslidar.launch 
```
### 启动底盘(can口)：
```
roslaunch scout_bringup scout_minimal.launch 
```
### 或者启动底盘(串口)：
```
roslaunch scout_bringup scout_minimal_uart.launch 
```
### 启动导航：
```
roslaunch scout_bringup navigation_4wd.launch
```
### 在地图上指定2d nav goal

