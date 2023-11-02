;; Auto-generated. Do not edit!


(when (boundp 'sentry_kinematics_sim::cmd_sentry)
  (if (not (find-package "SENTRY_KINEMATICS_SIM"))
    (make-package "SENTRY_KINEMATICS_SIM"))
  (shadow 'cmd_sentry (find-package "SENTRY_KINEMATICS_SIM")))
(unless (find-package "SENTRY_KINEMATICS_SIM::CMD_SENTRY")
  (make-package "SENTRY_KINEMATICS_SIM::CMD_SENTRY"))

(in-package "ROS")
;;//! \htmlinclude cmd_sentry.msg.html


(defclass sentry_kinematics_sim::cmd_sentry
  :super ros::object
  :slots (_vx _vy _wz _yaw_add _pitch_add ))

(defmethod sentry_kinematics_sim::cmd_sentry
  (:init
   (&key
    ((:vx __vx) 0.0)
    ((:vy __vy) 0.0)
    ((:wz __wz) 0.0)
    ((:yaw_add __yaw_add) 0.0)
    ((:pitch_add __pitch_add) 0.0)
    )
   (send-super :init)
   (setq _vx (float __vx))
   (setq _vy (float __vy))
   (setq _wz (float __wz))
   (setq _yaw_add (float __yaw_add))
   (setq _pitch_add (float __pitch_add))
   self)
  (:vx
   (&optional __vx)
   (if __vx (setq _vx __vx)) _vx)
  (:vy
   (&optional __vy)
   (if __vy (setq _vy __vy)) _vy)
  (:wz
   (&optional __wz)
   (if __wz (setq _wz __wz)) _wz)
  (:yaw_add
   (&optional __yaw_add)
   (if __yaw_add (setq _yaw_add __yaw_add)) _yaw_add)
  (:pitch_add
   (&optional __pitch_add)
   (if __pitch_add (setq _pitch_add __pitch_add)) _pitch_add)
  (:serialization-length
   ()
   (+
    ;; float32 _vx
    4
    ;; float32 _vy
    4
    ;; float32 _wz
    4
    ;; float32 _yaw_add
    4
    ;; float32 _pitch_add
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _vx
       (sys::poke _vx (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _vy
       (sys::poke _vy (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _wz
       (sys::poke _wz (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _yaw_add
       (sys::poke _yaw_add (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _pitch_add
       (sys::poke _pitch_add (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _vx
     (setq _vx (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _vy
     (setq _vy (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _wz
     (setq _wz (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _yaw_add
     (setq _yaw_add (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _pitch_add
     (setq _pitch_add (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get sentry_kinematics_sim::cmd_sentry :md5sum-) "009b0f5c0eb3c6a488f257c56e4d4fe2")
(setf (get sentry_kinematics_sim::cmd_sentry :datatype-) "sentry_kinematics_sim/cmd_sentry")
(setf (get sentry_kinematics_sim::cmd_sentry :definition-)
      "float32 vx
float32 vy
float32 wz
float32 yaw_add
float32 pitch_add


")



(provide :sentry_kinematics_sim/cmd_sentry "009b0f5c0eb3c6a488f257c56e4d4fe2")


