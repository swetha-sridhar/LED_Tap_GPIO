# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\Users\swetha.sridhar\Desktop\Projects\Attocam\Play-around\LED_Tap_GPIO\LED_Tap_GPIO\Tap\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\Users\swetha.sridhar\Desktop\Projects\Attocam\Play-around\LED_Tap_GPIO\LED_Tap_GPIO\Tap\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {Tap}\
-hw {C:\Users\swetha.sridhar\Desktop\Projects\Attocam\Play-around\LED_Tap_GPIO\LED_Tap_GPIO\design_1_wrapper.xsa}\
-proc {microblaze_0} -os {standalone} -fsbl-target {psu_cortexa53_0} -out {C:/Users/swetha.sridhar/Desktop/Projects/Attocam/Play-around/LED_Tap_GPIO/LED_Tap_GPIO}

platform write
platform generate -domains 
platform active {Tap}
platform generate
