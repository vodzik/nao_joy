REQUIREMENTS

Ths paskage reqiure NaoQI SDK, and basic nao/naoqi packages, and joy package. It was made for ROS hydro release. It haven't been tested on other versions. 




PREPERING NAO ----

Before you use nao_joy node, you must first start topics that connect NAO to ROS.
The easyest way to do this is type:

LD_LIBRATY_PATH=~usr/naoqi-sdk-2.1.3.3-linux64/lib:$LD_LIBRARY_PATH NAO_IP=10.104.16.52 roslaunch nao_bringup nao_full.launch force_python:=true

But first you must change LD_LIBRATY_PATH value to directory of naoqisdk liblary on your computer and NAO_IP to ip adress of your NAO.

You can propably also start ROS nodes on NAO, but this metod wasnt tested with this package 

NAO_JOY_NODE ----

nao_joy_node allows you to controll velocity of NAO movement, head orientatnin, and to trigger some action (like rise a hand)


Below is a list of controll bindings.

axis1    yaw of head
axis2    pitch od head
axis3    turning speed
axis4    moveing forward/backward speed

button1  riseing hand
button7  move left
button8  move right


nao_joy_node require informations from topic /joy

You can run joy_node from joy package, separatly, or launch nao_joy.launch. That file open both packages. 
