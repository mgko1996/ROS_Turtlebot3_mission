#include "midterm_kmg/msg_3.h"
#include "ros/ros.h"

// Publisher

// input angle (0~359)

int main(int argc, char **argv)
{
  ros::init(argc,argv,"midterm_pub3");
  ros::NodeHandle nh;
  ros::Publisher midterm_ang = nh.advertise<midterm_kmg::msg_3>("midterm_ang",100);
  ros::Rate loop_rate(10);
  midterm_kmg::msg_3 msg;
  //num1 = angle1, num2 = angle2
  int num1 = 0;
  int num2 = 0;
  
  while(ros::ok())
  {
    ROS_INFO("input [number1 , number2] (0~359) number1: angle1, number2: angle2");
    scanf("%d %d",&num1,&num2);
    msg.angle1 = num1;
    msg.angle2 = num2;

    midterm_ang.publish(msg);

    loop_rate.sleep();

  }

  return 0;
}