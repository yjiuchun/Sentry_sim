#include<ros/ros.h>
// #include<geometry_msgs/Twist.h>
#include<math.h>
#include<std_msgs/Float64.h>
#include<std_msgs/Float64MultiArray.h>
#include <iostream> 
#include<sentry_kinematics_sim/cmd_sentry.h>
#include<sensor_msgs/Imu.h>
#include<control_msgs/JointControllerState.h>


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

std_msgs::Float64 Yaw_pos;
std_msgs::Float64 Pitch_pos;


std_msgs::Float64 angle_offect;

std_msgs::Float64 VEHICLE_HALF_LENGTH;
std_msgs::Float64 VEHICLE_HALF_WIDTH;

float yaw;
float pitch;
float roll;

float my_pi = 3.141592653589793238462643383279;
float target_yaw;
float yaw_relitive_angle;

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

float rad_format(float rad)
{ 
  if (rad > 3.141592653589793238462643383279)
  {
    while(rad > 3.141592653589793238462643383279)
    { 
      rad = rad - 2*3.141592653589793238462643383279;
    }
  }
  if(rad < -3.141592653589793238462643383279)
  {
    while(rad < -3.141592653589793238462643383279)
    {
      rad = rad + 2*3.141592653589793238462643383279;
    }
  }
  return rad;
}

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
  //ROS_INFO("四元数:%f,%f,%f,%f",msg.orientation.x,msg.orientation.y,msg.orientation.z,msg.orientation.w);
toEulerAngle(msg.orientation.x,msg.orientation.y,msg.orientation.z,msg.orientation.w,roll,pitch,yaw);
//ROS_INFO("%f,%f,%f",yaw,pitch,roll);
}

void yawcallback(const control_msgs::JointControllerState& msg)
{
    yaw_relitive_angle = msg.process_value;
}

void cmdvelCallback(const sentry_kinematics_sim::cmd_sentry& cmd_sentry)
{
	//ROS_INFO("Linear Components:[%f,%f,%f]",cmd_vel.linear.x,cmd_vel.linear.y,cmd_vel.linear.z);
    std_msgs::Float64 vx_set; 
    vx_set.data = cmd_sentry.vx * std::cos(yaw_relitive_angle ) - cmd_sentry.vy * std::sin(yaw_relitive_angle);
    std_msgs::Float64 vy_set; 
    vy_set.data = cmd_sentry.vx * std::sin(yaw_relitive_angle ) + cmd_sentry.vy * std::cos(yaw_relitive_angle);
    std_msgs::Float64 wz_set;
    wz_set.data  = cmd_sentry.wz;
    std_msgs::Float64 para_xy, para_x,para_y;
  para_xy.data = std::pow(vx_set.data, 2) + std::pow(vy_set.data, 2) + std::pow(VEHICLE_HALF_LENGTH.data * wz_set.data, 2) + std::pow(VEHICLE_HALF_WIDTH.data * wz_set.data, 2);
  para_x.data = 2 * VEHICLE_HALF_WIDTH.data * wz_set.data * vx_set.data;
  para_y.data = 2 * VEHICLE_HALF_LENGTH.data * wz_set.data * vy_set.data;

  // 解算轮角度，atan2(y, x) = atan (y/x)
  angle1.data = std::atan2(vy_set.data - VEHICLE_HALF_LENGTH.data * wz_set.data, vx_set.data + VEHICLE_HALF_WIDTH.data * wz_set.data)+angle_offect.data;
  angle2.data = std::atan2(vy_set.data + VEHICLE_HALF_LENGTH.data * wz_set.data, vx_set.data + VEHICLE_HALF_WIDTH.data * wz_set.data)+angle_offect.data ;
  angle3.data = std::atan2(vy_set.data - VEHICLE_HALF_LENGTH.data * wz_set.data, vx_set.data - VEHICLE_HALF_WIDTH.data * wz_set.data)+angle_offect.data ;
  angle4.data = std::atan2(vy_set.data + VEHICLE_HALF_LENGTH.data * wz_set.data, vx_set.data - VEHICLE_HALF_WIDTH.data * wz_set.data)+angle_offect.data  ;
  
  speed1.data = std::sqrt((para_xy.data + para_x.data - para_y.data)) * speed_K.data;
  speed2.data =  std::sqrt((para_xy.data + para_x.data + para_y.data)) * speed_K.data;
  speed3.data =  std::sqrt((para_xy.data - para_x.data - para_y.data)) * speed_K.data;
  speed4.data = std::sqrt((para_xy.data - para_x.data + para_y.data)) * speed_K.data;


    static float absoulte_target = 0.0;
    static float absoulte_error = 0.0;
    absoulte_target = rad_format(absoulte_target + cmd_sentry.yaw_add);
    absoulte_error = rad_format(absoulte_target - yaw);
    absoulte_error = max_limit(absoulte_error,0.4);
    target_yaw = rad_format(yaw_relitive_angle + absoulte_error);
    ROS_INFO("absoulte_angle:%f target_angle:%f relitive_angle:%f target_relitive:%f",yaw,absoulte_target,yaw_relitive_angle,target_yaw);

    Yaw_pos.data = rad_format(target_yaw);
    Pitch_pos.data = cmd_sentry.pitch_add;

}




int main(int argc, char **argv)
{
    ros::init(argc, argv, "sentry_chassis_control");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("/cmd_sentry", 1000, cmdvelCallback);
    ros::Subscriber sub_imu = nh.subscribe("/imu", 1000, imuCallback);
    ros::Subscriber sub_yaw = nh.subscribe("/sentry/Yaw_controller/state",1000,yawcallback);

    ros::Publisher pub_h_l_f = nh.advertise<std_msgs::Float64>("/sentry/Heading_Left_Front_controller/command",1000);
    ros::Publisher pub_h_l_b = nh.advertise<std_msgs::Float64>("/sentry/Heading_Left_Back_controller/command",1000);
    ros::Publisher pub_h_r_f = nh.advertise<std_msgs::Float64>("/sentry/Heading_Right_Front_controller/command",1000);
    ros::Publisher pub_h_r_b = nh.advertise<std_msgs::Float64>("/sentry/Heading_Right_Back_controller/command",1000);
    ros::Publisher pub_d_l_f = nh.advertise<std_msgs::Float64>("/sentry/Driving_Left_Front_controller/command",1000);
    ros::Publisher pub_d_l_b = nh.advertise<std_msgs::Float64>("/sentry/Driving_Left_Back_controller/command",1000);
    ros::Publisher pub_d_r_f = nh.advertise<std_msgs::Float64>("/sentry/Driving_Right_Front_controller/command",1000);
    ros::Publisher pub_d_r_b = nh.advertise<std_msgs::Float64>("/sentry/Driving_Right_Back_controller/command",1000);
    ros::Publisher yawp = nh.advertise<std_msgs::Float64>("/sentry/Yaw_controller/command",1000);
    ros::Publisher pitchp = nh.advertise<std_msgs::Float64>("/sentry/Pitch_controller/command",1000);

  VEHICLE_HALF_LENGTH.data = 0.178;
  VEHICLE_HALF_WIDTH.data = 0.178;
  speed_K.data =20.0;
  angle1.data = 0;
  angle2.data = 0;
  angle3.data = 0;
  angle4.data = 0;
  speed1.data = 0;
  speed2.data = 0;
  speed3.data = 0;
  speed4.data = 0;
  Yaw_pos.data = 0;
  Pitch_pos.data = 0;
  angle_offect.data = 0.19;
  target_yaw = 0;

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
        yawp.publish(Yaw_pos);
        pitchp.publish(Pitch_pos);
        loop_rate.sleep();
    }
    return 0;
}