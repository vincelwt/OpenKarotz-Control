#!/bin/bash

RED=FF0000
GREEN=00FF00
BLUE=0000FF
VIOLET=660099
CYAN=00FFFF
YELLOW=FFFF00
PINK=FFC0CB
ORANGE=FFA500



# ---------------------------------------------------------------------------            
# DBUS_LED_FIXED                                                                   
# ---------------------------------------------------------------------------            
# Sets the color of the led                                                              
#   args : the color, in hexadecimal form (ex: FF0000 for red) we want to                
#          pulse in                                                                      
#   return : nothing                                                                     
# ---------------------------------------------------------------------------            
function dbus_led_fixed {                                                                
    UUID=`cat /proc/sys/kernel/random/uuid`                                              
    dbus-send  --system --dest=com.mindscape.karotz.Led                                  \
       /com/mindscape/karotz/Led com.mindscape.karotz.KarotzInterface.light    \
       string:"$UUID" string:"$1"                                               
}  

# ---------------------------------------------------------------------------
# DBUS_LED_PULSE                                                             
# ---------------------------------------------------------------------------
# Make the led pulse.                                                        
#   args : the color, in hexadecimal form (ex: FF0000 for red) we want to    
#          pulse in                                                          
#   return : nothing                                                         
# ---------------------------------------------------------------------------            
function dbus_led_pulse {                                                                
    if [ "$3" == "" ]; then
      SPEED=700
    else
      SPEED=$3
    fi
    UUID=`cat /proc/sys/kernel/random/uuid`                                              
    dbus-send --system --dest=com.mindscape.karotz.Led                                  \
            /com/mindscape/karotz/Led com.mindscape.karotz.KarotzInterface.pulse    \
            string:"$UUID" string:"$1" string:"$2" int32:$SPEED int32:-1            
} 

# ---------------------------------------------------------------------------
#
#   args : 
#   MainColor   : in hexadecimal form (ex: FF0000 for red)    
#   PulseMode   : 0-1
#   PulseColor  : in hexadecimal form (ex: FF0000 for red)
#   ColorMemory : 0-1 
# ---------------------------------------------------------------------------
function Leds {
   /bin/killall led  >>/dev/null 2>>/dev/null 
   
   LED_COLOR=$1
   LED_COLOR_PULSE=$2
   LED_PULSE=$3
   LED_NO_MEMORY=$4
   LED_SPEED=$5
   
   if [ "$LED_PULSE" == "" ]; then
     LED_PULSE=0 
   fi
   
   if [ "$LED_NO_MEMORY" == "" ]; then                                           
      LED_NO_MEMORY=0                                                             
   fi  
   
   # Led pulse
   if [ $LED_PULSE -eq 1 ]; then
      dbus_led_pulse $LED_COLOR $LED_COLOR_PULSE $LED_SPEED
      echo "1" > "$CNF_DATADIR/Run/led.pulse"
    else
      # Led Fixe
      if [ -e "$CNF_DATADIR/Run/led.pulse" ]; then                               
         rm "$CNF_DATADIR/Run/led.pulse"                                         
      fi
      dbus_led_fixed $LED_COLOR                              	
   fi 
	
   if [ $LED_NO_MEMORY -ne 1 ]; then   
      echo $LED_COLOR > $CNF_DATADIR/Run/led.color 
   fi
} 

# ---------------------------------------------------------------------------
#                                                                            
# ---------------------------------------------------------------------------
function LedsRestore {                                                       
                                                              
    if [ -e "$CNF_DATADIR/Run/led.pulse" ]; then                               
        LED_PULSE=1                                                           
    else                                                                      
        LED_PULSE=0                                                           
    fi                                                                        
                                                                                                                                                                                 
    if [ -e "$CNF_DATADIR/Run/led.color" ]; then                               
       LED_COLOR=`cat $CNF_DATADIR/Run/led.color`                             
    else                                                                      
       LED_COLOR=00FF00                                                      
    fi                                                                        
    Leds $LED_COLOR 000000 $LED_PULSE                                                
 }                                                                                                                                                                                                                                                                                                                                           


