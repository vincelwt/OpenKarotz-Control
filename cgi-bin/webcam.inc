#!/bin/bash

# ffmpeg -vcodec rawvideo -f rawvideo -pix_fmt rgb565 -s 640x480 -i /dev/camera -ss 00:00:01  -r 1 -vframes 1 -y /tmp/%d.jpg

function TakeSnapshot {  
   dbus-send --system --type=method_call --print-reply --dest=com.mindscape.karotz.Webcam /com/mindscape/karotz/Webcam com.mindscape.karotz.KarotzInterface.takeSnapshot string:1 string:"http://127.0.0.1/cgi-bin/save_snapshot" int32:50
}         
