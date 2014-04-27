#!/bin/bash

usedbus=0
uuid=$(uuidgen)

function EarsReset {
  if [ ! -e "$CNF_DATADIR/Run/ears.disabled" ]; then
     /karotz/bin/ears >>/dev/null 2>>/dev/null
  fi
}
    
function dbus_EarsReset {  
    dbus-send --system --type=method_call --dest=com.mindscape.karotz.Ears /com/mindscape/karotz/Ears \
com.mindscape.karotz.KarotzInterface.reset string:$uuid string:1
}


function EarsMove {   
   if [ ! -e "$CNF_DATADIR/Run/ears.disabled" ]; then
       /karotz/bin/ears $1 $3 $2 $3 >>/dev/null 2>>/dev/null
   fi
}         

function dbus_EarsMove {
     dbus-send --system --type=method_call --dest=com.mindscape.karotz.Ears /com/mindscape/karotz/Ears \
     com.mindscape.karotz.KarotzInterface.move string:$uuid int32:$1 int32:$3 int32:$2 int32:$3
     
}


function EarsStep {
    dbus-send --system --type=method_call --dest=com.mindscape.karotz.Ears /com/mindscape/karotz/Ears \
com.mindscape.karotz.KarotzInterface.move string:$uuid int32:$1 int32:$3 int32:$2 int32:$3  
 
}

