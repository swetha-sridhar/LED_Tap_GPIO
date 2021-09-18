# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: C:\Users\swetha.sridhar\Desktop\Projects\Attocam\Play-around\LED_Tap_GPIO\LED_Tap_GPIO\led_tap_system\_ide\scripts\systemdebugger_led_tap_system_standalone.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source C:\Users\swetha.sridhar\Desktop\Projects\Attocam\Play-around\LED_Tap_GPIO\LED_Tap_GPIO\led_tap_system\_ide\scripts\systemdebugger_led_tap_system_standalone.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -filter {jtag_cable_name =~ "Digilent JTAG-SMT1 210203823954A" && level==0 && jtag_device_ctx=="jsn-JTAG-SMT1-210203823954A-13636093-0"}
fpga -file C:/Users/swetha.sridhar/Desktop/Projects/Attocam/Play-around/LED_Tap_GPIO/LED_Tap_GPIO/led_tap/_ide/bitstream/download.bit
targets -set -nocase -filter {name =~ "*microblaze*#0" && bscan=="USER2" }
loadhw -hw C:/Users/swetha.sridhar/Desktop/Projects/Attocam/Play-around/LED_Tap_GPIO/LED_Tap_GPIO/Tap/export/Tap/hw/design_1_wrapper.xsa -regs
configparams mdm-detect-bscan-mask 2
targets -set -nocase -filter {name =~ "*microblaze*#0" && bscan=="USER2" }
rst -system
after 3000
targets -set -nocase -filter {name =~ "*microblaze*#0" && bscan=="USER2" }
dow C:/Users/swetha.sridhar/Desktop/Projects/Attocam/Play-around/LED_Tap_GPIO/LED_Tap_GPIO/led_tap/Debug/led_tap.elf
targets -set -nocase -filter {name =~ "*microblaze*#0" && bscan=="USER2" }
con
