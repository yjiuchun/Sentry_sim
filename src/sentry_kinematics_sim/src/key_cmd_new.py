#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import rospy
from sentry_kinematics_sim.msg import cmd_sentry
import sys, select, termios, tty
import pygame
import time
import math
msg = """
Control mrobot!
---------------------------
Moving around:
chassis:
   q    w    e
   a     s   d
yaw:
        i
    j   k   l


r/f : increase/decrease chassis speeds by 10%
t/g : increase/decrease yaw  speed by 10%
space key, k : force stop
anything else : stop smoothly

B to quit
"""


def getKey():
    tty.setraw(sys.stdin.fileno())
    rlist, _, _ = select.select([sys.stdin], [], [], 0.1)
    if rlist:
        key = sys.stdin.read(1)
    else:
        key = ''
    termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
    return key

def vels(speed,turn):
    return "currently:\tspeed %s\tturn %s " % (speed,turn)

def maxlimit(num,max):
    if num > max:
        num = max
    elif num < -max:
        num = -max
    return num

def set_vel(speed,k1,k2,add,_add):
    if k1:
        speed = speed + add
    if k2:
        speed = speed - add
    if (k1 == 0)&(k2 == 0):
        if speed > 0.03:
            speed = speed - _add
        elif speed < -0.03:
            speed = speed + _add
        else:
            speed = 0
    return speed

def rad_format(rad):
    if rad > math.pi:
        while rad > math.pi:
            rad = rad - 2 * math.pi
    elif rad < math.pi:
        while rad < -math.pi:
            rad = rad + math.pi
    return rad

def set_pos(pos,k1,k2,add):
    if k1:
        pos = pos + add
    if k2:
        pos = pos - add
    pos = rad_format(pos)
    return pos

def set_pos1(pos,k1,k2,add):
    if k1:
        pos = add
    if k2:
        pos = -add
    if k1==0&k2==0:
        pos = 0
    return pos


if __name__=="__main__":

    #settings = termios.tcgetattr(sys.stdin)
    rospy.init_node('sentry_cmd_key')
    pub = rospy.Publisher('/cmd_sentry', cmd_sentry, queue_size=5)
    chassis_max_speed = 1
    chassi_max_wz = 10
    yaw_max_speed = 1
    chassis_speed_add = 0.05
    
    yaw_pos_add = 0.005
    pitch_pos_add = 0.005
    speed_jian = 0.1

    vx = 0
    vy = 0
    wz = 0
    yaw = 0
    pitch = 0
    cmd_sentry_msg = cmd_sentry()
    cmd_key = ['q','w','e','a','s','d','r','f','t','g','i','j','k','l']
    pygame.init()
    pygame.display.set_mode((100,100))
    try:
        print(msg)
        while(1):
            keys = pygame.key.get_pressed()

            if keys[pygame.K_r]:
                yaw_pos_add = yaw_pos_add * 1.1
            if keys[pygame.K_f]:
                yaw_pos_add = yaw_pos_add * 0.9

            if keys[pygame.K_t]:
                chassis_speed_add = chassis_speed_add * 1.1
            if keys[pygame.K_g]:
                chassis_speed_add = chassis_speed_add * 0.9

            vx = set_vel(vx,keys[pygame.K_w],keys[pygame.K_s],chassis_speed_add,speed_jian)
            vy = set_vel(vy,keys[pygame.K_a],keys[pygame.K_d],chassis_speed_add,speed_jian)
            wz = set_vel(wz,keys[pygame.K_q],keys[pygame.K_e],chassis_speed_add,speed_jian)
            yaw = set_pos(yaw,keys[pygame.K_j],keys[pygame.K_l],yaw_pos_add)
            pitch = set_pos(pitch,keys[pygame.K_i],keys[pygame.K_k],pitch_pos_add)
            # break
            if keys[pygame.K_b]:
                break
            vx = maxlimit(vx,chassis_max_speed)
            vy = maxlimit(vy,chassis_max_speed)
            wz = maxlimit(wz,chassi_max_wz)
            cmd_sentry_msg.vx = vx
            cmd_sentry_msg.vy = vy
            cmd_sentry_msg.wz = wz
            cmd_sentry_msg.pitch_add = pitch
            cmd_sentry_msg.yaw_add = yaw
            pub.publish(cmd_sentry_msg)

            pygame.event.pump()
            time.sleep(0.01)
    except Exception as e:
        print (e)


        