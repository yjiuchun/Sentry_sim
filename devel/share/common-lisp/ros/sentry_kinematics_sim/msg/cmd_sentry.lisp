; Auto-generated. Do not edit!


(cl:in-package sentry_kinematics_sim-msg)


;//! \htmlinclude cmd_sentry.msg.html

(cl:defclass <cmd_sentry> (roslisp-msg-protocol:ros-message)
  ((vx
    :reader vx
    :initarg :vx
    :type cl:float
    :initform 0.0)
   (vy
    :reader vy
    :initarg :vy
    :type cl:float
    :initform 0.0)
   (wz
    :reader wz
    :initarg :wz
    :type cl:float
    :initform 0.0)
   (yaw_add
    :reader yaw_add
    :initarg :yaw_add
    :type cl:float
    :initform 0.0)
   (pitch_add
    :reader pitch_add
    :initarg :pitch_add
    :type cl:float
    :initform 0.0))
)

(cl:defclass cmd_sentry (<cmd_sentry>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <cmd_sentry>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'cmd_sentry)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name sentry_kinematics_sim-msg:<cmd_sentry> is deprecated: use sentry_kinematics_sim-msg:cmd_sentry instead.")))

(cl:ensure-generic-function 'vx-val :lambda-list '(m))
(cl:defmethod vx-val ((m <cmd_sentry>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader sentry_kinematics_sim-msg:vx-val is deprecated.  Use sentry_kinematics_sim-msg:vx instead.")
  (vx m))

(cl:ensure-generic-function 'vy-val :lambda-list '(m))
(cl:defmethod vy-val ((m <cmd_sentry>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader sentry_kinematics_sim-msg:vy-val is deprecated.  Use sentry_kinematics_sim-msg:vy instead.")
  (vy m))

(cl:ensure-generic-function 'wz-val :lambda-list '(m))
(cl:defmethod wz-val ((m <cmd_sentry>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader sentry_kinematics_sim-msg:wz-val is deprecated.  Use sentry_kinematics_sim-msg:wz instead.")
  (wz m))

(cl:ensure-generic-function 'yaw_add-val :lambda-list '(m))
(cl:defmethod yaw_add-val ((m <cmd_sentry>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader sentry_kinematics_sim-msg:yaw_add-val is deprecated.  Use sentry_kinematics_sim-msg:yaw_add instead.")
  (yaw_add m))

(cl:ensure-generic-function 'pitch_add-val :lambda-list '(m))
(cl:defmethod pitch_add-val ((m <cmd_sentry>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader sentry_kinematics_sim-msg:pitch_add-val is deprecated.  Use sentry_kinematics_sim-msg:pitch_add instead.")
  (pitch_add m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <cmd_sentry>) ostream)
  "Serializes a message object of type '<cmd_sentry>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vx))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vy))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'wz))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'yaw_add))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'pitch_add))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <cmd_sentry>) istream)
  "Deserializes a message object of type '<cmd_sentry>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vx) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vy) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'wz) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'yaw_add) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'pitch_add) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<cmd_sentry>)))
  "Returns string type for a message object of type '<cmd_sentry>"
  "sentry_kinematics_sim/cmd_sentry")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'cmd_sentry)))
  "Returns string type for a message object of type 'cmd_sentry"
  "sentry_kinematics_sim/cmd_sentry")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<cmd_sentry>)))
  "Returns md5sum for a message object of type '<cmd_sentry>"
  "009b0f5c0eb3c6a488f257c56e4d4fe2")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'cmd_sentry)))
  "Returns md5sum for a message object of type 'cmd_sentry"
  "009b0f5c0eb3c6a488f257c56e4d4fe2")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<cmd_sentry>)))
  "Returns full string definition for message of type '<cmd_sentry>"
  (cl:format cl:nil "float32 vx~%float32 vy~%float32 wz~%float32 yaw_add~%float32 pitch_add~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'cmd_sentry)))
  "Returns full string definition for message of type 'cmd_sentry"
  (cl:format cl:nil "float32 vx~%float32 vy~%float32 wz~%float32 yaw_add~%float32 pitch_add~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <cmd_sentry>))
  (cl:+ 0
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <cmd_sentry>))
  "Converts a ROS message object to a list"
  (cl:list 'cmd_sentry
    (cl:cons ':vx (vx msg))
    (cl:cons ':vy (vy msg))
    (cl:cons ':wz (wz msg))
    (cl:cons ':yaw_add (yaw_add msg))
    (cl:cons ':pitch_add (pitch_add msg))
))
