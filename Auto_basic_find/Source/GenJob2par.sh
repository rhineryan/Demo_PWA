#!/bin/bash
if [ $# -ne 2 ];then
  echo $0  jobname  exename
  exit -1
fi

filename=$1
exename=$2

cat<<EOF  >$filename
#!/bin/bash
cd $PWD
./$exename   > $exename.log
echo  $filename End===End  >>$exename.log
EOF

chmod +x $filename
