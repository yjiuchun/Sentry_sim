#include "sensor_msgs/PointCloud.h"
#include "sensor_msgs/PointCloud2.h"
#include "sensor_msgs/point_cloud_conversion.h"
#include <ros/ros.h>
#include <iostream>

ros::Subscriber subMMWCloud;
ros::Publisher pubLaserCloud;





    void mmwHandler(const sensor_msgs::PointCloudConstPtr& mmwCloudMsg)
    {
        // rawMMWCloudQueue.push_back(mmwCloudMsg);
        sensor_msgs::PointCloud2 laserCloudMsg;
        convertPointCloudToPointCloud2(*mmwCloudMsg, laserCloudMsg);
        laserCloudMsg.header.stamp = mmwCloudMsg->header.stamp;
        laserCloudMsg.header.frame_id = "laser_link";
        pubLaserCloud.publish(laserCloudMsg);
        std::cout << "hello LASER: " << laserCloudMsg.header.stamp << std::endl;
    }


int main(int argc, char **argv) 
{
    ros::init(argc, argv, "cp2cp_2_node");
    ros::NodeHandle nh;
    subMMWCloud = nh.subscribe<sensor_msgs::PointCloud>("/scan1", 2000, &mmwHandler);
    pubLaserCloud = nh.advertise<sensor_msgs::PointCloud2>("/scan2", 2000);
    ROS_INFO("RUNING....");
    ros::Rate loop_rate(10); // 设置循环的频率，这里是10Hz
    while (ros::ok())
    {
        ros::spinOnce(); // 处理所有待处理的ROS消息
        loop_rate.sleep(); // 按照循环频率进行休眠
    }
        return 0;
}