
UA="Mozilla/5.0 (Macintosh; Intel Mac OS X 10.7; rv:21.0) Gecko/20100101 Firefox/21.0"
   
function AcapelaTTS {  
   TTS=$1
   VOICE=$2
   NOCACHE=$3
   RVOICE=$4
   
   MD5FILE=$(echo "$TTS$VOICE" | md5sum | cut -d ' ' -f 1)  
   
   REQ1="client_request=CREATE_REQUEST&actionscript_version=3&client_version=1-00&client_login=asTTS&client_password=demo_web"
   CURL_PARAM=$(echo $REQ1"&client_voice="$VOICE"&client_text=\\pau=1000\\"$TTS)                                                          
   
   #echo '${CURL_PARAM}' http://vaas.acapela-group.com/Services/DemoWeb/textToMP3.php
   RESULT=`eval $(echo "curl -s --data '${CURL_PARAM}' http://vaas.acapela-group.com/Services/DemoWeb/textToMP3.php")`        

   RV=$(echo $RESULT | sed 's|retour_php=||' | cut -d\& -f1)                                                                  
   echo $( echo \"$TTS\" | UrlDecode)  > $CNF_DATADIR/Tmp/${MD5FILE}.txt                                             
   echo $( echo $RVOICE | UrlDecode)  > $CNF_DATADIR/Tmp/${MD5FILE}.voice
   eval $(echo "curl -A '${UA}' -o $CNF_DATADIR/Tmp/${MD5FILE}.mp3 $RV" )  >>/dev/null 2>>/dev/null                    
   
   PlaySound $CNF_DATADIR/Tmp/${MD5FILE}.mp3
   
   if [ "$NOCACHE" == "1" ]; then
     rm -f $CNF_DATADIR/Tmp/${MD5FILE}.mp3   >>/dev/null 2>>/dev/null
     rm -f $CNF_DATADIR/Tmp/${MD5FILE}.txt   >>/dev/null 2>>/dev/null 
   fi
   
}


function GoogleTTS {
   TTS=$1 
 
   MD5FILE=$(echo "$TTS" | md5sum | cut -d ' ' -f 1)
   eval $(echo "curl -A '${UA}' -o $CNF_DATADIR/Tmp/${MD5FILE}.mp3 'http://translate.google.com/translate_tts?tl=fr&q=${TTS}'" )  >>/dev/null 2>>/dev/null
   echo $( echo "$RAW_TTS" | UrlDecode)  > $CNF_DATADIR/Tmp/${MD5FILE}.txt 
 
   PlaySound $CNF_DATADIR/Tmp/${MD5FILE}.mp3     
}


function ProsodyTTS {
   TTS=$1
   VOICE=$2
  
    # Not Working
    # Need test
    return 
   
   MD5FILE=$(echo "$TTS" | md5sum | cut -d ' ' -f 1)
   # curl -s -d "$TTS" http://188.165.228.65/tts/Suzanne -o  $CNF_DATADIR/Tmp/test.mp3
    $(echo "curl -A '${UA}' -o $CNF_DATADIR/Tmp/${MD5FILE}.mp3 -s -data '${TTS}' http://188.165.228.65/tts/${VOICE}" )  >>/dev/null 2>>/dev/null
   echo $( echo "$RAW_TTS" | UrlDecode)  > $CNF_DATADIR/Tmp/${MD5FILE}.txt
            
   PlaySound $CNF_DATADIR/Tmp/${MD5FILE}.mp3
}
          
