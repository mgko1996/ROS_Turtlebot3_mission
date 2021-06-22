#include "midterm_kmg/msg_1.h"
#include "ros/ros.h"

// Publisher

// input power (0,1)
// 0 = power off
// 1 = power on

int main(int argc, char **argv)
{
  ros::init(argc,argv,"midterm_pub1");
  ros::NodeHandle nh;
  ros::Publisher midterm_power = nh.advertise<midterm_kmg::msg_1>("midterm_power",100);
  ros::Rate loop_rate(10);
  midterm_kmg::msg_1 msg;
  
  // num1 = power
  int num1;
   
   
  while(ros::ok())
  {
    ROS_INFO("input [number] 1:on , 0:off");
    scanf("%d",&num1);
    msg.power = num1;

    midterm_power.publish(msg);

    loop_rate.sleep();

  }

  return 0;
}