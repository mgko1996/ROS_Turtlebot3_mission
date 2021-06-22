#include "midterm_kmg/msg_2.h"
#include "ros/ros.h"

// Publisher

// input velocity (0~1)
// 0 = low speed
// 1 = fast speed

int main(int argc, char **argv)
{
  ros::init(argc,argv,"midterm_pub2");
  ros::NodeHandle nh;
  ros::Publisher midterm_vel = nh.advertise<midterm_kmg::msg_2>("midterm_vel",100);
  ros::Rate loop_rate(10);
  midterm_kmg::msg_2 msg;
  
  // num1 = velocity
  float num1 = 0;
  
  while(ros::ok())
  {
    ROS_INFO("input [number] velocity : 0~1");
    scanf("%f",&num1);
    msg.velocity = num1;

    midterm_vel.publish(msg);

    loop_rate.sleep();

  }

  return 0;
}