
(cl:in-package :asdf)

(defsystem "sentry_kinematics_sim-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "cmd_sentry" :depends-on ("_package_cmd_sentry"))
    (:file "_package_cmd_sentry" :depends-on ("_package"))
  ))