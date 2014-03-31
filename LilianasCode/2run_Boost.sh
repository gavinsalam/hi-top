#!/bin/bash

#$ -N BoostedTop
#$ -S /bin/bash
#$ -cwd
#$ -j y
#$ -m ea
#$ -M lilianamarisa.cunha@usc.es
#$ -t 1-100

#name
#specifies the interpreting shell for the job
#executes the job from the current working directory
#Standard error stream of the job is merged into the standard output stream: y(es) or n(o)
#send e-mail when ends or aborts
#e-mail direction


#######################################
export CERNLIB='-L/usr/lib64/cernlib/2006/lib -lkernlib -lpdflib804 -lmathlib -lpacklib -lpawlib -lgraflib'
export PATH=$PATH:/usr/lib64/openmpi/1.2.5-gcc/bin
export LD_LIBRARY_PATH=/usr/lib64/openmpi/1.2.5-gcc/lib

source /opt/expSoftware/Auger/External/root/5.30.06/bin/thisroot.sh

#PATH
export PATH=$PATH:.

#GSL
export PATH=$PATH:/home2/liliana.apolinario/Programs/GSL/gsl-1.15/bin/
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home2/liliana.apolinario/Programs/GSL/gsl-1.15/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home2/liliana.apolinario/Programs/GSL/gsl-1.15/include

#FASTJET
export PATH=$PATH:/home2/liliana.apolinario/Programs/FastJet/fastjet-3.0.6/fastjet-install/bin

#PYTHIA8
export PYTHIA8='/home2/liliana.apolinario/Programs/PYTHIA/pythia8170/'
export PYTHIA8DATA=$PYTHIA8/xmldoc
export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH\:$PYTHIA8/lib
export LD_LIBRARY_PATH=$PYTHIA8/lib:$LD_LIBRARY_PATH
#########################################



##### Variables ######
ptmin=$1

En=$2

if [ ${En} -eq 5 ] 
then
      input_file='boost5.cmnd'
else
      input_file='boost100.cmnd'
fi

output_file=`echo pt${ptmin}_En${En}TeV_${SGE_TASK_ID}.root`
arg_file=`echo arg.i${JOB_ID}_${SGE_TASK_ID}`

home_dir=`echo /home2/liliana.apolinario/Physics/BoostedTopDecay`
job_dir=`echo tmp_${JOB_ID}_${SGE_TASK_ID}`


##### Go to scratch/liliana and create job folder #####
cd /scratch/

if [ ! -d liliana ]; then
 mkdir liliana
fi

cd liliana

if [ -d $job_dir ]; then
 rm -fvR $job_dir
fi

mkdir $job_dir
cd $job_dir


### Copy files to scratch and executes ####
cp -v ${home_dir}/Boost.exe .

if [ ${En} -eq 5 ]
then
cat<<GUM > ${input_file}
Beams:idA = 2212
Beams:idB = -2212
Beams:eCM = 5500. 
Main:numberOfEvents = 10000
HadronLevel:Hadronize = off
Top:gg2ttbar = on
Top:qqbar2ttbar = on
Random:setSeed = on
Random:seed = ${SGE_TASK_ID}
GUM
else
cat<<GIM > ${input_file}
Beams:idA = 2212
Beams:idB = -2212
Beams:eCM = 100000. 
Main:numberOfEvents = 10000
HadronLevel:Hadronize = off
Top:gg2ttbar = on
Top:qqbar2ttbar = on
Random:setSeed = on
Random:seed = ${SGE_TASK_ID}
GIM
fi

cat<<FUM > ${arg_file}
${output_file}
${ptmin}
FUM

./Boost.exe < ${arg_file} ${input_file}


### Copy to home and delete from scratch
cp -v ${output_file} ${home_dir}/results/ 
#cp -v ${arg_file} ${home_dir}/results/ 
#cp -v ${input_file} ${home_dir}/results/${input_file}_${JOB_ID}_${SGE_TASK_ID}

## erase job_dir folder
cd ..
rm -fvr $job_dir

echo '!! Done All !!'
