# Nbody Visualized Gravity Simulation 

Simple Nbody Gravity Simulation and visualized to bitmap images.

# How to Use?
``` shell
# Clone the repository
git clone https://github.com/hnts03/Nbody_Visualized_Simulation.git

# cd to repository
cd Nbody_Visualized_Simulation

# make img directory
mkdir img

# build
make -C src/

# run
./nbody -n 1000 -t 2 -s 300 -v -w 512 -h 512 -d 512
```

Images will be generated inside of `img` directory with 24-bit bmp format.

