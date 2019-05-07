#!/bin/bash
if [ $# -ne 1 ];then
  echo $0  jobname
  exit -1
fi

filename=$1
cat<<EOF  >$filename
#!/bin/bash
cd $PWD
./GEtaPi0Pi0   > GEtaPi0Pi0.log
echo  $filename End===End  >>GEtaPi0Pi0.log
EOF

chmod +x $filename
