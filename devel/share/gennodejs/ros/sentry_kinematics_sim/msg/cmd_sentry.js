// Auto-generated. Do not edit!

// (in-package sentry_kinematics_sim.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class cmd_sentry {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.vx = null;
      this.vy = null;
      this.wz = null;
      this.yaw_add = null;
      this.pitch_add = null;
    }
    else {
      if (initObj.hasOwnProperty('vx')) {
        this.vx = initObj.vx
      }
      else {
        this.vx = 0.0;
      }
      if (initObj.hasOwnProperty('vy')) {
        this.vy = initObj.vy
      }
      else {
        this.vy = 0.0;
      }
      if (initObj.hasOwnProperty('wz')) {
        this.wz = initObj.wz
      }
      else {
        this.wz = 0.0;
      }
      if (initObj.hasOwnProperty('yaw_add')) {
        this.yaw_add = initObj.yaw_add
      }
      else {
        this.yaw_add = 0.0;
      }
      if (initObj.hasOwnProperty('pitch_add')) {
        this.pitch_add = initObj.pitch_add
      }
      else {
        this.pitch_add = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type cmd_sentry
    // Serialize message field [vx]
    bufferOffset = _serializer.float32(obj.vx, buffer, bufferOffset);
    // Serialize message field [vy]
    bufferOffset = _serializer.float32(obj.vy, buffer, bufferOffset);
    // Serialize message field [wz]
    bufferOffset = _serializer.float32(obj.wz, buffer, bufferOffset);
    // Serialize message field [yaw_add]
    bufferOffset = _serializer.float32(obj.yaw_add, buffer, bufferOffset);
    // Serialize message field [pitch_add]
    bufferOffset = _serializer.float32(obj.pitch_add, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type cmd_sentry
    let len;
    let data = new cmd_sentry(null);
    // Deserialize message field [vx]
    data.vx = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [vy]
    data.vy = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [wz]
    data.wz = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [yaw_add]
    data.yaw_add = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [pitch_add]
    data.pitch_add = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 20;
  }

  static datatype() {
    // Returns string type for a message object
    return 'sentry_kinematics_sim/cmd_sentry';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '009b0f5c0eb3c6a488f257c56e4d4fe2';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 vx
    float32 vy
    float32 wz
    float32 yaw_add
    float32 pitch_add
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new cmd_sentry(null);
    if (msg.vx !== undefined) {
      resolved.vx = msg.vx;
    }
    else {
      resolved.vx = 0.0
    }

    if (msg.vy !== undefined) {
      resolved.vy = msg.vy;
    }
    else {
      resolved.vy = 0.0
    }

    if (msg.wz !== undefined) {
      resolved.wz = msg.wz;
    }
    else {
      resolved.wz = 0.0
    }

    if (msg.yaw_add !== undefined) {
      resolved.yaw_add = msg.yaw_add;
    }
    else {
      resolved.yaw_add = 0.0
    }

    if (msg.pitch_add !== undefined) {
      resolved.pitch_add = msg.pitch_add;
    }
    else {
      resolved.pitch_add = 0.0
    }

    return resolved;
    }
};

module.exports = cmd_sentry;
