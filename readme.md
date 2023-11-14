测试环境:ubuntu 18.04 melodic 
注意修改:/sentry_sim_ws/src/sentry_laser_sim/world/rmuc_23.world 文件中的路径 107 & 129 行

1.livox_laser_simulation
    livox雷达仿真功能包
    运行官方提供的雷达仿真环境:
		roslauch livox_laser_simulation livox_simulation.launch 

2.sentry_kinematics_sim
    sp重装云台哨兵仿真,具有舵轮八自由度,yaw,pitch,左右拨弹轮.
    运行仿真:
		roslaunch sentry_kinematics_sim gazebo_xacro.launch 

    加载底盘.yaw.pitch controller:
		roslaunch sentry_kinematics_sim start.launch 

    加载sentry控制节点, 接收 /cmd_vel 转换为底盘运动 & yaw,pitch运动:
		rosrun sentry_kinematics_sim chassis_control 

    加载键盘控制节点,通过键盘发布 /cmd_vel:
		rosrun sentry_kinematics_sim key_cmd_new 

3.sentry_laser_sim 
    使用2中的哨兵在rm场地中作仿真对硬件要求较高,仿真跑的很慢,此功能包搭建简单四轮小车,用以模拟哨兵.
    小车搭载mid_360仿真雷达. 具体参数修改可在/xacro/laser.xacro修改
    运行gazebo仿真环境 & rviz 雷达仿真发布cloudpoint(/scan1),经过转换节点转为cloudpoint2(/scan2):
		roslaunch sentry_laser_sim gazebo.launch 

    配有imu插件,与pointcloud2不是同一个frame,在/xacro/imu.xacro配置
    使用gmapping建图,目前没跑明白维哥代码,先跑个gmapping玩玩:
	1)运行仿真
		roslaunch sentry_laser_sim gazebo.launch

	2)将三维点云 /scan2 转化为 Laserscan /scan
	    安装cloudpoint2转Laserscan功能包:  (注意更改ros版本)
		sudo apt-get install ros-melodic-pointcloud-to-laserscan 

	    运行将cloudpoint2转为Laserscan:
		roslaunch sentry_laser_sim cloutpoint2laserscan.launch

	3)运行gmapping建图
	    安装gmapping功能包:
		sudo apt-get install ros-melodic-gmapping

	    安装map_server功能包:
		sudo apt install ros-melodic-map-server
	  
	    运行gmapping建图:
		roslaunch sentry_laser_sim gmapping.launch
	4)运行键盘节点
		rosurn sentry_laser_sim key_cmd

	5)说明
	    执行完上述指令,可以在rviz里订阅map话题,可以看到建出的二维珊格地图,通过键盘移动小车可以进一步建图
	    实测小车上坡时定位很容易飘
	    保存地图:
		rosrun map_server map_saver save_path map_name

	    /map文件夹 有个地图

    有了地图可以跑一下定位算法:amcl. 定位算法主要发布map->odom 矫正机器人位姿
	1)安装amcl功能包

		sudo apt-get install ros-kinetic-amcl

	2)运行仿真环境

		roslaunch sentry_laser_sim gazebo.launch

	3)运行将cloudpoint2转为Laserscan:

		roslaunch sentry_laser_sim cloutpoint2laserscan.launch

	4)运行amcl:

		roslaunch sentry_laser_sim amcl_test.launch

    使用amcl做导航,move_base框架官方图就使用了amcl做定位.基于以上建立的二维地图 & amcl简单使用move_base框架.
	1)安装move_base功能包
		
		sudo apt-get install ros-melodic-move-base

	2)运行仿真环境

		roslaunch sentry_laser_sim gazebo.launch

	3)运行将cloudpoint2转为Laserscan:

		roslaunch sentry_laser_sim cloutpoint2laserscan.launch

	4)运行导航框架
	
		roslaunch sentry_laser_sim navigation_amcl.launch

	5)说明
	    rviz订阅map,里面点击2D NavGoal 再在地图上点一下,拖一下,确定目标位姿,小车会自动导航.
	    相关参数在/config/navigation里面修改


    跑通维哥代码:
             
		To be continued.........
	




    
    
