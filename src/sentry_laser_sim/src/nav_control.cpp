#include<ros/ros.h>
// #include<geometry_msgs/Twist.h>
#include<math.h>
#include<std_msgs/Float64.h>
#include<std_msgs/Float64MultiArray.h>
#include <iostream> 
#include<sentry_kinematics_sim/cmd_sentry.h>
#include<sensor_msgs/Imu.h>
#include<control_msgs/JointControllerState.h>
#include <geometry_msgs/Twist.h>


std_msgs::Float64 Yaw_pos;


std_msgs::Float64 angle_offect;


geometry_msgs::Twist cmd_sentry;

struct imu_t
{
    float yaw;
    float pitch;
    float roll;
};

imu_t imu_data;

ros::Publisher yaw;
ros::Publisher chassis_cmd;


float my_pi = 3.141592653589793238462643383279;
float target_yaw;
float yaw_relitive_angle;

float rad_format(float rad)
{ 
  if (rad > my_pi)
  {
    while(rad > my_pi)
    { 
      rad = rad - 2*my_pi;
    }
  }
  if(rad < -my_pi)
  {
    while(rad < -my_pi)
    {
      rad = rad + 2*my_pi;
    }
  }
  return rad;
}

float max_limit(float data,float max)
{
  if(data > max)
  {
    data = max;
  }
  else if(data < -max)
  {
    data = -max;
  }
  return data;
}

// 获取nav发布的cmd_vel
void cmdvelCallback(const geometry_msgs::Twist& msg)
{
    cmd_sentry.linear.x = msg.linear.x;
    cmd_sentry.linear.y = msg.linear.y;
    cmd_sentry.angular.z = msg.angular.z;
}

// 获取yaw轴相对角度
void yawcallback(const control_msgs::JointControllerState& msg)
{
    yaw_relitive_angle = msg.process_value;
}
// imu四元数转为欧拉角
void toEulerAngle(float x,float y,float z,float w,float &roll,float &pitch,float &yaw)
{
  double sinr_cosp = +2.0 * (w * x + y * z);
  double cosr_cosp = +1.0 - 2.0 * (x * x + y * y);
  roll = std::atan2(sinr_cosp, cosr_cosp);
  double sinp = +2.0 * (w * y - z * x);
  if (std::fabs(sinp) >= 1)
pitch = copysign(M_PI / 2, sinp); // use 90 degrees if out of rang
else
pitch = asin(sinp);
double siny_cosp = +2.0 * (w * z + x * y);
double cosy_cosp = +1.0 - 2.0 * (y * y + z * z);
yaw = std::atan2(siny_cosp, cosy_cosp);
}

void imuCallback(const sensor_msgs::Imu& msg)
{
toEulerAngle(msg.orientation.x,msg.orientation.y,msg.orientation.z,msg.orientation.w,imu_data.roll,imu_data.pitch,imu_data.yaw);
// ROS_INFO("%f,%f,%f",imu_data.yaw,imu_data.pitch,imu_data.roll);
}

void chassis_control()
{
    std_msgs::Float64 vx_set; 
    vx_set.data = cmd_sentry.linear.x * std::cos(yaw_relitive_angle ) - cmd_sentry.linear.y * std::sin(yaw_relitive_angle );
    std_msgs::Float64 vy_set; 
    vy_set.data = cmd_sentry.linear.x * std::sin(yaw_relitive_angle ) + cmd_sentry.linear.y * std::cos(yaw_relitive_angle );
    std_msgs::Float64 wz_set;
    wz_set.data  = 0.0;
    geometry_msgs::Twist vel_msg;
	  vel_msg.linear.x = vx_set.data;
    vel_msg.linear.y = vy_set.data;
    vel_msg.angular.z = wz_set.data;
    chassis_cmd.publish(vel_msg);
}



void gimbal_control()
{   
    static float absoulte_target = 0.0;
    static float absoulte_error = 0.0;
    absoulte_target = rad_format(absoulte_target + cmd_sentry.angular.z);
    absoulte_error = rad_format(absoulte_target - imu_data.yaw );
    absoulte_error = max_limit(absoulte_error,0.4);
    target_yaw = rad_format(yaw_relitive_angle + absoulte_error);
    Yaw_pos.data = target_yaw;
    ROS_INFO("absoulte_angle:%f target_angle:%f relitive_angle:%f target_relitive:%f",imu_data.yaw,absoulte_target,yaw_relitive_angle,target_yaw);
    yaw.publish(Yaw_pos);
}





int main(int argc, char **argv)
{
    ros::init(argc, argv, "sentry_chassis_control");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("/cmd_vel", 1000, cmdvelCallback);
    ros::Subscriber sub_imu = nh.subscribe("/imu", 1000, imuCallback);

    ros::Subscriber sub_yaw = nh.subscribe("/sentry/Yaw_controller/state",1000,yawcallback);
    yaw = nh.advertise<std_msgs::Float64>("/sentry/Yaw_controller/command",1000);
    chassis_cmd = nh.advertise<geometry_msgs::Twist>("/sentry/cmd_vel", 10);

    ros::Rate loop_rate(10); // 设置循环的频率，这里是10Hz
    ROS_INFO("Start controlling your sentry!!!");
    while(ros::ok())
    {
        ros::spinOnce();
        chassis_control();
        gimbal_control();
        loop_rate.sleep();
    }
    return 0;
}