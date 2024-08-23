

#include "bitmap.h"

// int main(int argc, char **argv) {
// 	ofstream fout("output.bmp", ios::binary);
// 
// 	fout.write((char *) &bmpHeader, 14);
// 	fout.write((char *) &bmpInfoHeader, 40);
// 
// 	// writing pixel data
// 	size_t numberOfPixels = bmpInfoHeader.width * bmpInfoHeader.height;
// 	for (int i = 0; i < numberOfPixels; i++){
// 		fout.write((char *) &pixel, 3);
// 	}
// 	fout.close();
// 
// 	return 0;
// }
//

int main(int argc, char** argv){
	char fileName[20] = "test.bmp";
	FILE *fp = fopen(fileName, "wb");
	
	struct BmpHeader		bmpHeader;
	struct BmpInfoHeader	bmpInfoHeader;
	struct Pixel			pixel;

	bmpHeader.saveOnFile(fp);
	bmpInfoHeader.saveOnFile(fp);

	size_t numberOfPixels = bmpInfoHeader.width * bmpInfoHeader.height;
	for (int i = 0; i < numberOfPixels; i++){
		pixel.saveOnFile(fp);
	}

	fclose(fp);
}
