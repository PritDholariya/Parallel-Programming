#!/usr/bin/env bash
####### Mail Notify / Job Name / Comment #######
#SBATCH --job-name="ping_pong"

####### Partition #######
#SBATCH --partition=all

####### Ressources #######
#SBATCH --time=0-00:05:00

####### Node Info #######
#SBATCH --exclusive
#SBATCH --nodes=1

####### Output #######
#SBATCH --output=/home/fd0005372/out/ping_pong.out.%j
#SBATCH --error=/home/fd0005372/out/ping_pong.err.%j

cd /home/fd0005372/mySubdir
mpirun -n 2 ./ping_pong