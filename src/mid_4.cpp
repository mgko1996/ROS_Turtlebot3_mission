#include "ros/ros.h"
#include "midterm_kmg/msg_1.h"
#include "midterm_kmg/msg_2.h"
#include "midterm_kmg/msg_3.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/Bool.h" 
#include "sensor_msgs/Imu.h"
#include "math.h"

// Subscriber

// power = Variable to hold information from msg_1
// velocity = Variable to hold information from msg_2
// angle1, angle2 = Variable to hold information from msg_3
// distance = Variable to hold information from LIDAR
// q0, q1, q2, q3 = Variable to calculating quaternion
// ang_pitch = Variable to hold data of angle tilted forward, backward
// ang_roll = Variable to hlod data of angle tilted right, left

int angle1;
int angle2;
int power;
float velocity = 0;
float distance[360];
float q0;
float q1;
float q2;
float q3;
float ang_pitch;
float ang_roll;

void msgCallback1(const midterm_kmg::msg_1::ConstPtr& msg)
{
    //power
    ROS_INFO("power: %d [0:off,1:on]", msg->power);
    printf("\n\n\n");
    power = msg->power;
}

void msgCallback2(const midterm_kmg::msg_2::ConstPtr& msg)
{
    //velocity
    ROS_INFO("velocity = %f [0~1]", msg->velocity);
    printf("\n\n\n");
    velocity = msg->velocity;
}

void msgCallback3(const midterm_kmg::msg_3::ConstPtr& msg)
{
    //angle
    ROS_INFO("number 1 = %d , number 2 = %d", msg->angle1, msg->angle2);
    printf("\n\n\n");
    angle1 = msg->angle1;
    angle2 = msg->angle2;
}

void laser_scan_Callback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
    for (int i = 0; i < 360; i++)
    {   
        // Handling exception for distances
        if ((msg->ranges[i])==0)
        {
            distance[i] = 99;
        }
        else
        {
            distance[i] = msg->ranges[i];
        }
    }    
}

void imu_Callback(const sensor_msgs::Imu::ConstPtr& imu_msg)
{
    q0 = imu_msg->orientation.x;
    q1 = imu_msg->orientation.y;
    q2 = imu_msg->orientation.z;
    q3 = imu_msg->orientation.w;
}

int main(int argc, char **argv)
{
    ros::init(argc,argv,"midterm_sub1");
    ros::NodeHandle nh;
    ros::Subscriber mid_pow = nh.subscribe("midterm_power",100,msgCallback1);
    ros::Subscriber mid_vel  = nh.subscribe("midterm_vel",100,msgCallback2);
    ros::Subscriber mid_ang = nh.subscribe("midterm_ang",100,msgCallback3);
    ros::Subscriber mid_lidar = nh.subscribe("/scan",100,laser_scan_Callback);
    ros::Subscriber practice4_sub2 = nh.subscribe("/imu",1000,imu_Callback);
    ros::Publisher mid_power = nh.advertise<std_msgs::Bool>("/motor_power",100);
    ros::Publisher mid_velocity = nh.advertise<geometry_msgs::Twist>("/cmd_vel",100);
    midterm_kmg::msg_1 msg1;
    midterm_kmg::msg_2 msg2;
    midterm_kmg::msg_3 msg3;
    sensor_msgs::LaserScan ls;
    geometry_msgs::Twist ko_velocity;
    std_msgs::Bool kmg_power;
    ros::Rate loop_rate(1);

    while(ros::ok())
    {   
        ros::spinOnce();
        
        // Convert Quaternion to Euler
        ang_roll = atan2(2*((q0*q3)+(q1*q2)),1-2*((q2*q2)+(q3*q3)))*180/M_PI;
        ang_pitch = asin(2*((q0*q2)-(q3*q1)))*180/M_PI;

        if (ang_roll < 0)
        {
            ang_roll = ang_roll+180;
        }
        else if(ang_roll > 0)
        {
            ang_roll = ang_roll-180;
        }

        // if (motor power on[ power =1 ]) => motor on
        if (power == 1)
        {
            kmg_power.data=true;
            mid_power.publish(kmg_power);
            
            // if (angle1 <= angle2) => Extract value for anlgle 1 through 2
            //   => find minimum value of distance value between angle1 , angle2
            //      and Store information about index
            //      => if (minimum distance < 0.3) or (absolute value of tilted angle >= 45) => motor stop
            //      => else if (minimum distance >= 0.3) or (absolute value of tilted angle < 45) => motor on
            // Show information about angle index of minimum distance and its value
            if (angle1 < angle2)
            {
                int size = angle2 + 1;
                float min = distance[angle1];
                int index;
                for (int i = angle1; i < size; i++)
                {
                    if (min > distance[i])
                    {
                        min = distance[i];
                        index = i;
                    }
                }
                if ((min < 0.3))
                {
                    kmg_power.data=false;
                    mid_power.publish(kmg_power);
                }
                if ((abs(ang_pitch) >= 45.0) || (abs(ang_roll) >= 45.0))
                {
                    kmg_power.data=false;
                    mid_power.publish(kmg_power);
                }
                if ((velocity == 0))
                {
                    kmg_power.data=false;
                    mid_power.publish(kmg_power);
                }
                
                if ((min >= 0.3))
                {
                    if ((abs(ang_pitch) < 45.0) && (abs(ang_roll) < 45.0))
                    {
                        if ((velocity != 0))
                        {
                            ko_velocity.linear.x = velocity;
                            mid_velocity.publish(ko_velocity);
                        }
                    }
                }
            ROS_INFO("[%d]degree : minimum value of distance = %f",index,min);
            }

            // if (angle1 > angle2) => Extract value for anlgle 2 through 1
            //   => find minimum value of distance value between angle1 , angle2
            //      and Store information about indexc
            //      => if (minimum distance < 0.3) or (absolute value of tilted angle >= 45) => motor stop
            //      => else if (minimum distance >= 0.3) or (absolute value of tilted angle < 45) => motor on
            // Show information about angle index of minimum distance and its value
            else if(angle1 > angle2)
            {
                int size = angle2 + 360 + 1;
                float min = distance[angle2];
                int index;
                for (int i = angle1; i < size; i++)
                {
                    int kmg = i % 360;
                    if(min > distance[kmg])
                    {
                        min = distance[kmg];
                        index = kmg;
                    }
                }
                if ((min < 0.3))
                {
                    kmg_power.data=false;
                    mid_power.publish(kmg_power);
                }
                if ((abs(ang_pitch) >= 45.0) || (abs(ang_roll) >= 45.0))
                {
                    kmg_power.data=false;
                    mid_power.publish(kmg_power);
                }
                if ((velocity == 0))
                {
                    kmg_power.data=false;
                    mid_power.publish(kmg_power);
                }
                
                if ((min >= 0.3))
                {
                    if ((abs(ang_pitch) < 45.0) && (abs(ang_roll) < 45.0))
                    {
                        if ((velocity != 0))
                        {
                            ko_velocity.linear.x = velocity;
                            mid_velocity.publish(ko_velocity);
                        }
                    }
                }
            ROS_INFO("[%d]degree : minimum value of distance = %f",index,min);
            }
            else if((angle1 == 0 && (angle2 ==0)))
            {
                kmg_power.data=false;
                mid_power.publish(kmg_power);
            }
        }

        // if (power ==0) => motor stop
        else if (power == 0)
        {
            kmg_power.data=false;
            mid_power.publish(kmg_power);
        }

        // because I define loop_rate as 1
        // Drive once / 1 sec
        loop_rate.sleep();
    }
    return 0;
}