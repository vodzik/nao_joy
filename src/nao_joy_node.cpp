#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/Joy.h"
#include "naoqi_msgs/JointAnglesWithSpeedActionGoal.h"
#include "geometry_msgs/Twist.h"


#include <sstream>
#include <iostream>
#include <string>
#include <vector>


ros::Publisher publisher;     //publish informations about joint state goal
ros::Publisher publisher2;    //bublish information about velovity goal
naoqi_msgs::JointAnglesWithSpeedActionGoal msg1;
geometry_msgs::Twist msg2;
double pitch;
double yaw;
double forward;
double turn;
int lathelar;
bool ries_hand;

void react(const sensor_msgs::Joy& msg)   //function that handle changes in /Joy topic       msg hold information abouth axes and buttons ststes
{
    std::cout<<msg.axes[0]<<"  "<<msg.axes[1]<<std::endl;
    yaw=msg.axes[0]*1.5;
    pitch=-msg.axes[1];
    forward = msg.axes[3];
    turn=msg.axes[2];
    lathelar=msg.buttons[6];
    lathelar-=msg.buttons[7];
    ries_hand =msg.buttons[0];

    msg1.goal.joint_angles.joint_angles[0]=pitch;
    msg1.goal.joint_angles.joint_angles[1]=yaw;

    if(ries_hand)
    {
        msg1.goal.joint_angles.joint_angles[2]=-1;
        msg1.goal.joint_angles.speed=1;
    }

    else
    {

            msg1.goal.joint_angles.joint_angles[2]=2;
            msg1.goal.joint_angles.speed=0.3;


    }

    publisher.publish(msg1);
    msg2.linear.x=forward;
    msg2.linear.y=lathelar;
    msg2.angular.z=turn;
    publisher2.publish(msg2);

}

int main(int argc, char **argv)
{
ros::init(argc, argv, "nao_joy_node");
ros::NodeHandle node;
ros::Rate rate(20.0);

pitch=0;
yaw=0;

publisher = node.advertise<naoqi_msgs::JointAnglesWithSpeedActionGoal>("/joint_angles_action/goal", 1000);
publisher2 = node.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);


// initialization of msg1 goal vectors

msg1.goal.joint_angles.joint_names.push_back("HeadPitch");
msg1.goal.joint_angles.joint_names.push_back("HeadYaw");
msg1.goal.joint_angles.joint_names.push_back("RShoulderPitch");
msg1.goal.joint_angles.joint_angles.push_back(0);
msg1.goal.joint_angles.joint_angles.push_back(0);
msg1.goal.joint_angles.joint_angles.push_back(0);

msg1.goal.joint_angles.speed=0.3;



ros::Subscriber sub = node.subscribe("joy", 1000, react);

//ros::spin();

    while (node.ok())
    {

        ros::spinOnce();
        rate.sleep();
    }



}
