#!/bin/bash
#SBATCH -J DotProduct                            # Job name
#SBATCH -N 1                                # Number of nodes
#SBATCH -n 1                               # Number of tasks
#SBATCH -o output_%j.txt                    # Standard output file
#SBATCH -e error_%j.txt                     # Standard error file
#SBATCH --mail-user=tarallo.n@northeastern.edu  # Email
#SBATCH --mail-type=ALL                     # Type of email notifications
#SBATCH --constraint=cascadelake

# Your program/command here

gcc -lm -mavx512f dot-product-AVX.c -o dot-product-AVX
./dot-product-AVX
