source /www/cgi-bin/url.vera
source /www/cgi-bin/url.eedomus

declare -A URLParam

function ReadUrlParam {  
 saveIFS=$IFS
  IFS='=&'
  parm=($QUERY_STRING)
  IFS=$saveIFS
  for ((i=0; i<${#parm[@]}; i+=2))
  do
      URLParam[${parm[i]}]=${parm[i+1]}
  done
}

function BuildVeraUrl {
   IP=$1
   SCENE=$2
   URL='curl -l "http://'$IP$VERA_BASE_URL$SCENE'"'
   echo -n $URL
}          

function BuildEeDomusUrl {
   IP=$1
   MACRO=$2
   USER=$3
   PASSWORD=$4
   URL='curl -l "http://'$IP$EEDOMUS_BASE_URL'&macro='$MACRO'&api_user='$USER'&api_secret='$PASSWORD'"'
   echo -n $URL
}


function GetUrl { 
URL=$1

curl -o /dev/null --silent "$1"

}  



