#include "sensor_msgs/PointCloud.h"
#include "livox_ros_driver2/CustomMsg.h"
#include <ros/ros.h>
#include <iostream>
#include "sensor_msgs/point_cloud_conversion.h"
#include <geometry_msgs/Point32.h>


ros::Subscriber PC;
ros::Publisher CM;


    void mmwHandler(const sensor_msgs::PointCloudConstPtr& rec_msg)
{
    static ros::WallTime Time_base = ros::WallTime::now();
    livox_ros_driver2::CustomMsg msg;
    msg.header.seq = rec_msg->header.seq;
    msg.header.stamp = rec_msg->header.stamp;
    msg.header.frame_id = "laser_link";
    // msg.timebase = (int)Time_base;
    msg.point_num = rec_msg->points.size();
    msg.lidar_id = 192;
    for(int i=0;i<10000;i++)
    {
        
        msg.points[i].x = rec_msg->points[i].x;
        msg.points[i].y = rec_msg->points[i].y;
        msg.points[i].z = rec_msg->points[i].z;

    }
    


    std::cout<<msg.point_num<<std::endl;
    // cout<<sizeof(msg.points)/sizeof(msg.points)<<endl;
    //ROS_INFO("%d",mmwCloudMsg.header.seq);
    // cout<<mmwCloudMsg->header.stamp<endl;
    //CM.publish(laserCloudMsg); 
}




int main(int argc, char **argv) 
{
    ros::init(argc, argv, "pc2cm_node");
    ros::NodeHandle nh;
    PC = nh.subscribe<sensor_msgs::PointCloud>("/scan1", 2000, &mmwHandler);
    CM = nh.advertise<livox_ros_driver2::CustomMsg>("/livox_scan", 2000);
    ROS_INFO("RUNING....");
    ros::Rate loop_rate(10); // 设置循环的频率，这里是10Hz
    while (ros::ok())
    {
        ros::spinOnce(); // 处理所有待处理的ROS消息
        loop_rate.sleep(); // 按照循环频率进行休眠
    }
        return 0;
}