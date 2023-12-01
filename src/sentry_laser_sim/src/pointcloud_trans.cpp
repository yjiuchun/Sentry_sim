#include "sensor_msgs/PointCloud2.h"
#include <ros/ros.h>
#include <iostream>
#include "sensor_msgs/PointCloud.h"


ros::Subscriber PC2;
ros::Subscriber PC;
ros::Publisher CM;

void PointCloudCallBack(const sensor_msgs::PointCloud2::ConstPtr& rec_msg)
{
    for (int f=0; f<rec_msg->fields.size(); f++)
	{
        // ROS_INFO("Runing !");
		// if (rec_msg->fields[f].name == "intensity")
				std::cout << "intensity lidar->fields[f].name = " << rec_msg->fields.size() << std::endl;

				// std::cout << "intensity lidar->fields[f].datatype = " << (int)rec_msg->fields[f].datatype << std::endl;
	 }
}
void mmwHandler(const sensor_msgs::PointCloudConstPtr& msg)
{
    std::cout<< "Pc"<<msg->channels.size()<<std::endl;
}


int main(int argc, char **argv) 
{
    ros::init(argc, argv, "pointcloud_trans_node");
    ros::NodeHandle nh;
    //PC2 = nh.subscribe<sensor_msgs::PointCloud2>("/scan2", 2000, &PointCloudCallBack);
    PC = nh.subscribe<sensor_msgs::PointCloud>("/scan1", 2000, &mmwHandler);

    ROS_INFO("RUNING....");
    ros::Rate loop_rate(10); // 设置循环的频率，这里是10Hz
    while (ros::ok())
    {
        ros::spinOnce(); // 处理所有待处理的ROS消息
        loop_rate.sleep(); // 按照循环频率进行休眠
    }
        return 0;
}