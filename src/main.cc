

#include "nbody.h"
#include "bitmap.h"
#include <unistd.h>

int main(int argc, char **argv) {
	
	uint32_t	step = MAX_STEP;	// # of timestep
	double		dt = deltaT;		// sampling interval
	uint32_t	n = N;				// # of bodies
	bool		visualize = false;	// option for visualize
	uint32_t	width = 512;
	uint32_t	height = 512;
	uint32_t	depth = 512;


	// Parse the argument first
	
	if (argc == 1){
		fprintf(stderr, "Usage: <excutable> <options>\n"
				"-n <uint>\t: The number of bodies to simulate\n"
				"-t <double>\t: The time interval of simulation\n"
				"-s <uint>\t: The number of simulation steps\n"
				"-v \t\t: Visualize option. bmp images will be generatedi\n"
				"-w/h/d <uint>\t: width/height/depth value\n"
				);
		return 1;
	}

	int opt;
	while ((opt = getopt(argc, argv, "n:t:s:v:w:h:d:")) != -1) {
		switch (opt) {
			case 'n':
				n = atoi(optarg);
				printf("N: %d\n", n); // Debugging
				break;
			case 't':
				char *endptr;
				dt = strtod(optarg, &endptr);
				printf("dt: %f\n", dt); // Debugging
				if (*endptr != '\0') {
					fprintf(stdout, "Invalid double value: %s\n", optarg);
					return 1;
				}
				break;
			case 's':
				step = atoi(optarg);
				printf("step: %d\n", step); // Debugging
				break;
			case 'v':
				visualize = true;
				printf("Visualize: %d\n", visualize); // Debugging
				break;
			case 'w':
				width = atoi(optarg);
				printf("width: %d\n", width); // Debugging
				break;
			case 'h':
				height = atoi(optarg);
				printf("height: %d\n", height); // Debugging
				break;
			case 'd':
				depth = atoi(optarg);
				printf("depth: %d\n", depth); // Debugging
				break;
			default:
				fprintf(stderr, "Usage: <excutable> <options>\n"
						"-n <uint>\t: The number of bodies to simulate\n"
						"-t <double>\t: The time interval of simulation\n"
						"-s <uint>\t: The number of simulation steps\n"
						"-v \t\t: Visualize option. bmp images will be generated\n"
						"-w/h/d <uint>\t: width/height/depth value\n"
						);
				return 1;
				
		}
	} // while loop done
	
	
	// Create Bodies
	srand(time(NULL)); // Fix the random seed
	Body *bodies = new Body[n];
	for (int i = 0; i < n; i++){
		bodies[i].randInit(width, height, depth);
	}

	// Start simulation
	for(int i = 0; i < step; i++){
		printf("\nStep: %d\n", i); // Debugging
		
		// Calculate all bodies
		for (int src_idx = 0; src_idx < n; src_idx++){
			for (int dst_idx = 0; dst_idx < n; dst_idx++){
				if (src_idx == dst_idx) continue;
				bodies[src_idx].calc_force(&bodies[dst_idx]); // calculate force
			}
			bodies[src_idx].update_next_vel(dt);
			bodies[src_idx].update_next_pos(dt);
		}
		
		// Update the pos/vel/acc values
		for (int idx = 0; idx < n; idx++){
			bodies[idx].update_acc();
			bodies[idx].update_vel();
			bodies[idx].update_pos();

		//	bodies[idx].print(stdout);
		}
		

		if (visualize) {
			char filename[20];
			sprintf(filename, "./img/%d.bmp", i);
			
			FILE *fp = fopen(filename, "wb");
			if (fp == NULL) {
				printf("Failed to open file\n");
				return 1;
			}

			struct BitmapFile bitmapfile;
			bitmapfile.init(width, height);

			for (int idx = 0; idx < n; idx++){
				bitmapfile.drawPixel(
					(uint32_t)bodies[idx].get_pos_x(), (uint32_t)bodies[idx].get_pos_y());
				printf("x: %d, y: %d\n", (uint32_t)bodies[idx].get_pos_x(), (uint32_t)bodies[idx].get_pos_y());
			}

			bitmapfile.drawBitmapFile(fp);
			
			bitmapfile.cleanup();
			fclose(fp);
		}
	}

	delete[] bodies;
	return 0;
}
