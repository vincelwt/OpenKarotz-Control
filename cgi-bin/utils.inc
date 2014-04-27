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
#
# ---------------------------------------------------------------------------
TYPE_VERA=1
TYPE_EEDOMUS=2
TYPE_URL=3
USER_DEFINED_TYPE=99



function Download {
URL=$1
RDIR=$2
LDIR=$3
NAME=$4
GROUP=$5
NL=$6

echo "----------------------------------------"
echo "Updating : "$NAME
wget $URL$RDIR/list.txt -O $LDIR/list.txt -q
nbline=$(cat $LDIR/list.txt | wc -l )
echo $nbline" File(s) to download"
echo "----------------------------------------"
i=1
while read line;
do
    n=$((i%$GROUP))
        if [ $n -eq 0 ]; then
               echo -n "."
                   fi
                       wget $URL$RDIR/$line -q -O $LDIR/$line
                           chmod 777 $LDIR/$line
                               i=$((i+1))
                               done < $LDIR/list.txt
                               rm -f $LDIR/list.txt >>/dev/null 2>>/dev/null
                               echo ""
                               }
# ---------------------------------------------------------------------------
# 
# ---------------------------------------------------------------------------
function KillProcess { 
   /bin/killall led  >>/dev/null 2>>/dev/null
   /bin/killall ears >>/dev/null 2>>/dev/null
   /bin/killall madplay >>/dev/null 2>>/dev/null
   /bin/killall mpd  >>/dev/null 2>>/dev/null  
   /bin/killall mplayer >>/dev/null 2>>/dev/null
}

function SendResponse {
   DATA=${1}
   echo "Server: OpenKarotz WebServer 1.0 - Massalia 2013"
   echo "Connection: close"
   echo "Accept-Ranges: bytes"
   echo "Content-Length: "${#DATA}
   #echo "Content-type: application/json"
   echo "Content-type: text/plain"
   echo ""
   echo $DATA
}


function ReadParam {  
FILE_NAME=$1
DEFAULT_VALUE=$2

     if [ -e "$1" ]; then     
        echo -n `cat $1`
     else
        echo -n $2
     fi 

} 




# ---------------------------------------------------------------------------
#
# ---------------------------------------------------------------------------
function UrlDecode  {             
    echo -e "$(sed 's/+/ /g; s/%/\\x/g')"
} 

# ---------------------------------------------------------------------------
#
# ---------------------------------------------------------------------------
UrlEncode() {
    local string="${1}"
    local strlen=${#string}
    local encoded=""
            
    for (( pos=0 ; pos<strlen ; pos++ )); do
       c=${string:$pos:1}
       case "$c" in
          [-_.~a-zA-Z0-9] )   o="${c}" ;;
          * )                 printf -v o '%%%02x' "'$c"

       esac
       encoded+="${o}"
     done
     
     echo "${encoded}" 
} 

# ---------------------------------------------------------------------------
#
# ---------------------------------------------------------------------------
function GetCmdName {
 TNAME=""
    case $1 in
      1) TNAME="VERA_SCENE";;
      2) TNAME="EEDOMUS_MACRO";;
      *) TNAME="UNKNOWN"
    esac
                                
    echo $TNAME
}

# ---------------------------------------------------------------------------
# 
# ---------------------------------------------------------------------------
function GetRfidTypeName {   
 TNAME=""
   case $1 in
      1) TNAME="FLATANOZ";;
      2) TNAME="NANOZTAG";;
      3) TNAME="ZSTAMPS";;
      *) TNAME="UNKNOWN"
    esac
    
    echo $TNAME
}

# ---------------------------------------------------------------------------
#                                                                            
# ---------------------------------------------------------------------------
function GetRfidColorName { 
 CNAME=""                          
  case $1 in 
      1)  CNAME="ROUGE";;
      2)  CNAME="BLEU";; 
      3)  CNAME="VERT";;
      4)  CNAME="JAUNE";;
      5)  CNAME="ROSE";;
      6)  CNAME="NOIR";;
      7)  CNAME="GRIS";;
      8)  CNAME="ORANGE";;
      9)  CNAME="BORDEAUX";;
      10) CNAME="BLANC";;
      *)  CNAME="UNKNOWN";;
   esac
   
   echo $CNAME
}                                            

# ---------------------------------------------------------------------------
#                                                                            
# ---------------------------------------------------------------------------
function PlaySound { 
SOUND=$1
BG=$2
  
      killall mplayer >>/dev/null 2>>/dev/null
      if [ ! -f /tmp/mplayer-control ]; then
        mknod /tmp/mplayer-control p  >>/dev/null 2>>/dev/null
      fi
      #/usr/bin/madplay $SOUND >>/dev/null 2>>/dev/null                       
      if [ "$BG" == "1" ]; then                
        mplayer -quiet -slave -input file=/tmp/mplayer-control $SOUND >>/dev/null 2>>/dev/null & 
      else
        mplayer -quiet -slave -input file=/tmp/mplayer-control $SOUND >>/dev/null 2>>/dev/null
      fi
}                                            

                                                           
# ---------------------------------------------------------------------------
#                                                                            
# ---------------------------------------------------------------------------
function StartTagRecording { 
    Leds 775577 000000 1 1
    echo "1" > $CNF_DATADIR/Run/rfid.record  >>/dev/null 2>>/dev/null
    PlaySound $CNF_DATADIR/Voice/Rfid_Start_Record.mp3 
}  


# ---------------------------------------------------------------------------
#          
# ---------------------------------------------------------------------------
function StopTagRecording {
    rm -f   $CNF_DATADIR/Run/rfid.record  >>/dev/null 2>>/dev/null
    PlaySound $CNF_DATADIR/Voice/Rfid_Stop_record.mp3  >>/dev/null 2>>/dev/null
    LedsRestore
}  


