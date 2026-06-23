#!/usr/bin/env bash
####### Mail Notify / Job Name / Comment #######
#SBATCH --job-name="hello_world"

####### Partition #######
#SBATCH --partition=all

####### Ressources #######
#SBATCH --time=0-00:05:00

####### Node Info #######
#SBATCH --exclusive
#SBATCH --nodes=4
#SBATCH --ntasks-per-node=4

####### Output #######
#SBATCH --output=/PATH/TO/out/hello_world.out.%j
#SBATCH --error=/PATH/TO/out/hello_world.err.%j

cd /PATH/TO/out
mpirun ./hello_world
