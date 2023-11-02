#include <pcl_conversions/pcl_conversions.h>
// #include <sensor_msgs/PointCloud2.h>
// #include <sensor_msgs/PointCloud.h>
// #include <sensor_msgs/point_field_conversion.h>
#include <sensor_msgs/point_cloud_conversion.h>
#include "livox_ros_driver/CustomMsg.h"

 typedef pcl::PointXYZINormal PointType;
 typedef pcl::PointCloud<PointType> PointCloudXYZI;

//定义velodyne雷达的数据格式
struct VelodynePointXYZIRT
{
    PCL_ADD_POINT4D
    PCL_ADD_INTENSITY;
    uint16_t ring;
    float time;
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
} EIGEN_ALIGN16;
POINT_CLOUD_REGISTER_POINT_STRUCT (VelodynePointXYZIRT,
    (float, x, x) (float, y, y) (float, z, z) (float, intensity, intensity)
    (uint16_t, ring, ring) (float, time, time)
)
using PointXYZIRT = VelodynePointXYZIRT;

typedef pcl::PointXYZI PointType;
typedef pcl::PointCloud<PointType> PointCloudXYZI;

ros::Publisher pub_pcl_out0, pub_pcl_out1;


//将livox自定义点云数据格式转化为PointXYZINormal格式
uint64_t TO_MERGE_CNT = 1;
constexpr bool b_dbg_line = false;

std::vector<livox_ros_driver::CustomMsgConstPtr> livox_data;

void LivoxMsgcbk1(const livox_ros_driver::CustomMsgConstPtr& livox_msg_in)
{
    livox_data.push_back(livox_msg_in);

    if(livox_data.size() < TO_MERGE_CNT)
        return;
    
    pcl::PointCloud<PointType> pcl_in;
    pcl::PointCloud<PointXYZIRT> out_msg;
    for(size_t j = 0; j < livox_data.size(); j++ )
    {
        auto& livox_msg = livox_data[j];
        auto time_end = livox_msg->points.back().offset_time;

        for(unsigned i = 0; i < livox_msg->point_num; i++)
        {
            PointType pt;
            pt.x = livox_msg->points[i].x;
            pt.y = livox_msg->points[i].y;
            pt.z = livox_msg->points[i].z;
            double s = livox_msg->points[i].offset_time/ (double)time_end;

            pt.intensity = livox_msg->points[i].line + livox_msg->points[i].reflectivity / 10000.0;
            pt.curvature = s * 0.1;
            pcl_in.push_back(pt);
        }
    }
    
    unsigned long timebase_ns = livox_data[0]->timebase;
    ros::Time timestamp;
    timestamp.fromNSec(timebase_ns);
    sensor_msgs::PointCloud2 pcl_ros_msg;
    pcl::toROSMsg(pcl_in,pcl_ros_msg);
        
    pcl_ros_msg.header.stamp.fromNSec(timebase_ns);
    pcl_ros_msg.header.frame_id = "livox_frame";

    pub_pcl_out1.publish(pcl_ros_msg);

    livox_data.clear();
}

//std::vector<sensor_msgs::PointCloud2> cloud_info;
//将array type:sensor_msgs/PointField length:8 可转换为 length为4
void lasermapcbk2(sensor_msgs::PointCloud2 msg)
{
    //cloud_info.push_back(msg);
    sensor_msgs::PointCloud2 pcl_ros_msg;
    pcl::PointCloud<pcl::PointXYZI>::Ptr pcl_mid(new pcl::PointCloud<pcl::PointXYZI>());
    pcl::fromROSMsg(msg, *pcl_mid);
    pcl::toROSMsg(*pcl_mid,pcl_ros_msg);

    pub_pcl_out0.publish(pcl_ros_msg);
}

int main(int argc, char* argv[])
{   
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"livox_repub");
    ros::NodeHandle nh;

    ROS_INFO("-------发布PointXYZI格式-------");

    ros::Subscriber sub_livox_msg1 = nh.subscribe<livox_ros_driver::CustomMsg>("/livox/lidar",10,LivoxMsgcbk1);
    pub_pcl_out1 = nh.advertise<sensor_msgs::PointCloud2>("/velodyne_points",10);
    ros::Subscriber sub_laser_map = nh.subscribe<sensor_msgs::PointCloud2>("/cloud_registered",10,lasermapcbk2);
    pub_pcl_out0 = nh.advertise<sensor_msgs::PointCloud2>("/detect",10);
    ros::spin();
}