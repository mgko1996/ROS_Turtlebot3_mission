#include "ros/ros.h"
#include "sensor_msgs/Imu.h"
#include "math.h"

// Subscriber

// q0, q1, q2, q3 = Variable to calculating quaternion
// ang_pitch = Variable to hold data of angle tilted forward, backward
// ang_roll = Variable to hlod data of angle tilted right, left

float ang_pitch;
float ang_roll;
float q0;
float q1;
float q2;
float q3;


void imu_Callback(const sensor_msgs::Imu::ConstPtr& imu_msg)
{
    q0 = imu_msg->orientation.x;
    q1 = imu_msg->orientation.y;
    q2 = imu_msg->orientation.z;
    q3 = imu_msg->orientation.w;
}

int main(int argc, char **argv)
{
    ros::init(argc,argv,"midterm_sub2");
    ros::NodeHandle nh;
    ros::Subscriber mid_ang2 = nh.subscribe("/imu",100,imu_Callback);
    ros::Rate loop_rate(10);

    while(ros::ok())
    {   
        ros::spinOnce();

        // Convert Quaternion to Euler
        ang_roll = atan2(2*((q0*q3)+(q1*q2)),1-2*((q2*q2)+(q3*q3)))*180/M_PI;
        ang_pitch = asin(2*((q0*q2)-(q3*q1)))*180/M_PI;

        // if pitch angle < 0 => robot tilts forward
        //    pitch angle >= 0 => robot tilts  backward
        // if roll angle < 0 => robot tilts left
        //    roll angle >= 0 => robot tilts right
        // because (atan2 => -180~180) 
        //    if (roll angle) < 0   => roll angle + 180
        //       (roll angle) > 180 => roll angle - 180
        if(ang_pitch < 0 )
        {
            ROS_INFO("front : [%f] degree",abs(ang_pitch));
        }
        else if(ang_pitch >= 0)
        {
            ROS_INFO("back : [%f] degree",ang_pitch);
        }

        if (ang_roll < 0)
        {
            ROS_INFO("left : [%f] degree",ang_roll+180);
        }
        else if(ang_roll > 0)
        {
            ROS_INFO("right : [%f] degree",abs(ang_roll-180));
        }
        else if(ang_roll == 0)
        {
            ROS_INFO("right = [%f] degree",ang_roll);
        }

        // because I define loop_rate as 10
        // Drive once / 100 msec
        loop_rate.sleep();
    }
    return 0;
}
