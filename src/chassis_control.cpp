#include<ros/ros.h>
#include<geometry_msgs/Twist.h>
#include<math.h>
#include<std_msgs/Float64.h>
#include<std_msgs/Float64MultiArray.h>
#include <iostream> 

std_msgs::Float64MultiArray wheel_angle;
std_msgs::Float64MultiArray wheel_speed;

std_msgs::Float64 speed_K ;

std_msgs::Float64 angle1;
std_msgs::Float64 angle2;
std_msgs::Float64 angle3;
std_msgs::Float64 angle4;

std_msgs::Float64 speed1;
std_msgs::Float64 speed2;
std_msgs::Float64 speed3;
std_msgs::Float64 speed4;


std_msgs::Float64 VEHICLE_HALF_LENGTH;
std_msgs::Float64 VEHICLE_HALF_WIDTH;



void cmdvelCallback(const geometry_msgs::Twist& cmd_vel)
{

	//ROS_INFO("Linear Components:[%f,%f,%f]",cmd_vel.linear.x,cmd_vel.linear.y,cmd_vel.linear.z);
    std_msgs::Float64 vx_set; 
    vx_set.data = cmd_vel.linear.x;
    std_msgs::Float64 vy_set; 
    vy_set.data = cmd_vel.linear.y;
    std_msgs::Float64 wz_set;
    wz_set.data  = cmd_vel.angular.z;
    std_msgs::Float64 para_xy, para_x,para_y;
  para_xy.data = std::pow(vx_set.data, 2) + std::pow(vy_set.data, 2) + std::pow(VEHICLE_HALF_LENGTH.data * wz_set.data, 2) + std::pow(VEHICLE_HALF_WIDTH.data * wz_set.data, 2);
  para_x.data = 2 * VEHICLE_HALF_WIDTH.data * wz_set.data * vx_set.data;
  para_y.data = 2 * VEHICLE_HALF_LENGTH.data * wz_set.data * vy_set.data;

	// 注意电机安装方向的不同
  speed1.data = std::sqrt((para_xy.data - para_x.data + para_y.data)) * 100;
  speed2.data =  std::sqrt((para_xy.data - para_x.data - para_y.data)) * 100;
  speed3.data =  std::sqrt((para_xy.data + para_x.data - para_y.data)) * 100;
  speed4.data = std::sqrt((para_xy.data + para_x.data + para_y.data)) * 100;
  

  // 解算轮角度，atan2(y, x) = atan (y/x)
  angle1.data = -std::atan2(vy_set.data + VEHICLE_HALF_LENGTH.data * wz_set.data, vx_set.data + VEHICLE_HALF_WIDTH.data * wz_set.data) + 0.19;
  angle2.data = -std::atan2(vy_set.data + VEHICLE_HALF_LENGTH.data * wz_set.data, vx_set.data - VEHICLE_HALF_WIDTH.data * wz_set.data) + 0.19;
  angle3.data = -std::atan2(vy_set.data - VEHICLE_HALF_LENGTH.data * wz_set.data, vx_set.data - VEHICLE_HALF_WIDTH.data * wz_set.data) + 0.19;
  angle4.data = std::atan2(vy_set.data - VEHICLE_HALF_LENGTH.data * wz_set.data, vx_set.data + VEHICLE_HALF_WIDTH.data * wz_set.data) + 0.19;
  ROS_INFO("Wheel_angle:[%f,%f,%f,%f]-----Wheel_speed:[%f,%f,%f,%f]", angle1.data, angle2.data, angle3.data, angle4.data,speed1.data, speed2.data, speed3.data, speed4.data);


}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "sentry_chassis_control");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("/cmd_vel", 1000, cmdvelCallback);
    ros::Publisher pub_h_l_f = nh.advertise<std_msgs::Float64>("/sentry/Heading_Left_Front_controller/command",1000);
    ros::Publisher pub_h_l_b = nh.advertise<std_msgs::Float64>("/sentry/Heading_Left_Back_controller/command",1000);
    ros::Publisher pub_h_r_f = nh.advertise<std_msgs::Float64>("/sentry/Heading_Right_Front_controller/command",1000);
    ros::Publisher pub_h_r_b = nh.advertise<std_msgs::Float64>("/sentry/Heading_Right_Back_controller/command",1000);
    ros::Publisher pub_d_l_f = nh.advertise<std_msgs::Float64>("/sentry/Driving_Left_Front_controller/command",1000);
    ros::Publisher pub_d_l_b = nh.advertise<std_msgs::Float64>("/sentry/Driving_Left_Back_controller/command",1000);
    ros::Publisher pub_d_r_f = nh.advertise<std_msgs::Float64>("/sentry/Driving_Right_Front_controller/command",1000);
    ros::Publisher pub_d_r_b = nh.advertise<std_msgs::Float64>("/sentry/Driving_Right_Back_controller/command",1000);

  VEHICLE_HALF_LENGTH.data = 0.178;
  VEHICLE_HALF_WIDTH.data = 0.178;
  speed_K.data =1000.0;
  angle1.data = 0;
  angle2.data = 0;
  angle3.data = 0;
  angle4.data = 0;

    ros::Rate loop_rate(10); // 设置循环的频率，这里是10Hz
    while(ros::ok())
    {
        ros::spinOnce();
        pub_h_l_b.publish(angle2);
        pub_h_r_f.publish(angle3);
        pub_h_r_b.publish(angle4);
        pub_h_l_f.publish(angle1);
        pub_d_l_b.publish(speed2);
        pub_d_r_f.publish(speed3);
        pub_d_r_b.publish(speed4);
        pub_d_l_f.publish(speed1);

        loop_rate.sleep();
    }
    return 0;
}