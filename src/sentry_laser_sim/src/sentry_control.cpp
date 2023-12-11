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


std_msgs::Float64 angle_offect;

std_msgs::Float64 VEHICLE_HALF_LENGTH;
std_msgs::Float64 VEHICLE_HALF_WIDTH;

sentry_kinematics_sim::cmd_sentry cmd_sentry;

struct imu_t
{
    float yaw;
    float pitch;
    float roll;

};

imu_t imu_data;

ros::Publisher pub_h_l_f;
ros::Publisher pub_h_l_b;
ros::Publisher pub_h_r_f;
ros::Publisher pub_h_r_b;
ros::Publisher pub_d_l_f;
ros::Publisher pub_d_l_b;
ros::Publisher pub_d_r_f;
ros::Publisher pub_d_r_b;
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

void cmdvelCallback(const sentry_kinematics_sim::cmd_sentry& msg)
{
    cmd_sentry.vx = msg.vx;
    cmd_sentry.vy = msg.vy;
    cmd_sentry.wz = msg.wz;
    cmd_sentry.yaw_add = msg.yaw_add;
    cmd_sentry.pitch_add = msg.pitch_add;
    // ROS_INFO("Get Control Data!");
}

void yawcallback(const control_msgs::JointControllerState& msg)
{
    yaw_relitive_angle = msg.process_value;
    // ROS_INFO("%f",yaw_relitive_angle);
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
toEulerAngle(msg.orientation.x,msg.orientation.y,msg.orientation.z,msg.orientation.w,imu_data.roll,imu_data.pitch,imu_data.yaw);
ROS_INFO("%f,%f,%f",imu_data.yaw,imu_data.pitch,imu_data.roll);
}

void chassis_control()
{
    std_msgs::Float64 vx_set; 
    vx_set.data = cmd_sentry.vx * std::cos(yaw_relitive_angle ) - cmd_sentry.vy * std::sin(yaw_relitive_angle);
    std_msgs::Float64 vy_set; 
    vy_set.data = cmd_sentry.vx * std::sin(yaw_relitive_angle ) + cmd_sentry.vy * std::cos(yaw_relitive_angle);
    std_msgs::Float64 wz_set;
    wz_set.data  = cmd_sentry.wz;

    geometry_msgs::Twist vel_msg;
		vel_msg.linear.x = vx_set.data;
    vel_msg.linear.y = vy_set.data;
    vel_msg.angular.z = wz_set.data;

    chassis_cmd.publish(vel_msg);




    // std_msgs::Float64 para_xy, para_x,para_y;
    // para_xy.data = std::pow(vx_set.data, 2) + std::pow(vy_set.data, 2) + std::pow(VEHICLE_HALF_LENGTH.data * wz_set.data, 2) + std::pow(VEHICLE_HALF_WIDTH.data * wz_set.data, 2);
    // para_x.data = 2 * VEHICLE_HALF_WIDTH.data * wz_set.data * vx_set.data;
    // para_y.data = 2 * VEHICLE_HALF_LENGTH.data * wz_set.data * vy_set.data;

  // 解算轮角度，atan2(y, x) = atan (y/x)
  //舵轮解算
    // angle1.data = rad_format(std::atan2(vy_set.data - VEHICLE_HALF_LENGTH.data * wz_set.data, vx_set.data + VEHICLE_HALF_WIDTH.data * wz_set.data)+angle_offect.data);
    // angle2.data = rad_format(std::atan2(vy_set.data + VEHICLE_HALF_LENGTH.data * wz_set.data, vx_set.data + VEHICLE_HALF_WIDTH.data * wz_set.data)+angle_offect.data);
    // angle3.data = rad_format(std::atan2(vy_set.data - VEHICLE_HALF_LENGTH.data * wz_set.data, vx_set.data - VEHICLE_HALF_WIDTH.data * wz_set.data)+angle_offect.data);
    // angle4.data = rad_format(std::atan2(vy_set.data + VEHICLE_HALF_LENGTH.data * wz_set.data, vx_set.data - VEHICLE_HALF_WIDTH.data * wz_set.data)+angle_offect.data);
    
    // speed1.data = std::sqrt((para_xy.data + para_x.data - para_y.data)) * speed_K.data;
    // speed2.data =  std::sqrt((para_xy.data + para_x.data + para_y.data)) * speed_K.data;
    // speed3.data =  std::sqrt((para_xy.data - para_x.data - para_y.data)) * speed_K.data;
    // speed4.data = std::sqrt((para_xy.data - para_x.data + para_y.data)) * speed_K.data;

    // pub_h_l_b.publish(angle2);
    // pub_h_r_f.publish(angle3);
    // pub_h_r_b.publish(angle4);
    // pub_h_l_f.publish(angle1);
    // pub_d_l_b.publish(speed2);
    // pub_d_r_f.publish(speed3);
    // pub_d_r_b.publish(speed4);
    // pub_d_l_f.publish(speed1);
}
float pid_cal(float current, float target, float p, float i, float d, float max_i, float max_out)
{
    float error;
    static float error_last = 0.0;
    float p_out;
    float i_out;
    float d_out;
    float out;
    error = rad_format(target - current);
    p_out = p * error;
    i_out += i * error;
    d_out = d * (error - error_last);
    error_last = error;
    out = p_out + i_out + d_out;
    return out;
}

void gimbal_control()
{   
    static float absoulte_target = 0.0;
    static float absoulte_error = 0.0;
    absoulte_target = rad_format(absoulte_target + cmd_sentry.yaw_add);
    absoulte_error = rad_format(absoulte_target - imu_data.yaw);
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
    ros::Subscriber sub = nh.subscribe("/cmd_sentry", 1000, cmdvelCallback);
    ros::Subscriber sub_imu = nh.subscribe("/imu", 1000, imuCallback);
    ros::Subscriber sub_yaw = nh.subscribe("/sentry/Yaw_controller/state",1000,yawcallback);
    // pub_h_l_f = nh.advertise<std_msgs::Float64>("/sentry/Heading_Left_Front_controller/command",1000);
    // pub_h_l_b = nh.advertise<std_msgs::Float64>("/sentry/Heading_Left_Back_controller/command",1000);
    // pub_h_r_f = nh.advertise<std_msgs::Float64>("/sentry/Heading_Right_Front_controller/command",1000);
    // pub_h_r_b = nh.advertise<std_msgs::Float64>("/sentry/Heading_Right_Back_controller/command",1000);
    // pub_d_l_f = nh.advertise<std_msgs::Float64>("/sentry/Driving_Left_Front_controller/command",1000);
    // pub_d_l_b = nh.advertise<std_msgs::Float64>("/sentry/Driving_Left_Back_controller/command",1000);
    // pub_d_r_f = nh.advertise<std_msgs::Float64>("/sentry/Driving_Right_Front_controller/command",1000);
    // pub_d_r_b = nh.advertise<std_msgs::Float64>("/sentry/Driving_Right_Back_controller/command",1000);
    yaw = nh.advertise<std_msgs::Float64>("/sentry/Yaw_controller/command",1000);
    chassis_cmd = nh.advertise<geometry_msgs::Twist>("/sentry/cmd_vel", 10);

    VEHICLE_HALF_LENGTH.data = 0.178;
    VEHICLE_HALF_WIDTH.data = 0.178;
    speed_K.data = 10.0;
    angle1.data = 0;
    angle2.data = 0;
    angle3.data = 0;
    angle4.data = 0;
    speed1.data = 0;
    speed2.data = 0;
    speed3.data = 0;
    speed4.data = 0;
    Yaw_pos.data = 0;
    angle_offect.data = -my_pi / 2;

    ros::Rate loop_rate(10); // 设置循环的频率，这里是10Hz
    ROS_INFO("Start controlling your sentry!!!");
    while(ros::ok())
    {
        ros::spinOnce();
        chassis_control();
        gimbal_control();

        // pitch.publish(Pitch_pos);
        loop_rate.sleep();
    }
    return 0;
}