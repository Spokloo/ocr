#include <stdio.h>
#include <err.h>
#include <string.h>
#include "image.h"

/*void to_grayscale_bpm(int argc, char** argv){
    if(argc != 2)
        errx(1, "Wrong number of arguments");

    FILE *imgSrc = fopen(argv[1],"r"); //Load image
    if(imgSrc == NULL)
        errx(1,"Image does not exist.");

    //Get filename and extension
    char *filename = argv[1];
    char *extension = strrchr(filename, '.');
    *extension = '\0';
    extension++;
    char *end = extension;
    while(*end != '\0')
        end++;
    char newName[end - filename];
    strcpy(newName, filename);
    strncat(newName, "_grayscale.", 12);
    strncat(newName, extension, end - extension);

    FILE *imgOut = fopen(newName,"w+"); //Create grayscale image

    int i,y;
    unsigned char byte[54];

    for(i=0;i<54;i++) //Read the 54 byte header
    {
        byte[i] = getc(imgSrc);
    }

    fwrite(byte,sizeof(unsigned char),54,imgOut);//write the header

    // extract image height and width from header
    int height = *(int*)&byte[18];
    int width = *(int*)&byte[22];

    int size = height*width;
    unsigned char buffer[size][3]; //to store the image data


    for(i=0;i<size;i++)
    {
        y = 0;
        buffer[i][2]=getc(imgSrc); //blue
        buffer[i][1]=getc(imgSrc); //green
        buffer[i][0]=getc(imgSrc); //red

        y = (buffer[i][0]*0.3) + (buffer[i][1]*0.59)	+ (buffer[i][2]*0.11);
        //y = (buffer[i][0] + buffer[i][1] + buffer[i][2]) / 3;

        putc(y,imgOut);
        putc(y,imgOut);
        putc(y,imgOut);
    }

    fclose(imgOut);
    fclose(imgSrc);
}*/

int main(int argc, char **argv){

    if(argc != 2)
        errx(1, "Give an image path as argument");
    Image wow = load_image(argv[1]);
    grayscale(&wow);
    save_image(&wow);
    free_image(&wow);
    return 0;
}
