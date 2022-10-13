#include "contrast/contrast.h"
#include "grayscale/grayscale.h"
#include "canny/canny.h"
#include "tools/image.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <err.h>

#pragma test_utils 
char *substring(char *string, int position, int length)
{
   char *pointer;
   int c;
 
   pointer = malloc(length+1);
   
   if( pointer == NULL )
       exit(1);
 
   for( c = 0 ; c < length ; c++ )
      *(pointer+c) = *((string+position-1)+c);      
       
   *(pointer+c) = '\0';
 
   return pointer;
}
void insert_substring(char *a, char *b, int position)
{
   char *f, *e;
   int length;
   
   length = strlen(a);
   
   f = substring(a, 1, position - 1 );      
   e = substring(a, position, length-position+1);

   strcpy(a, "");
   strcat(a, f);
   free(f);
   strcat(a, b);
   strcat(a, e);
   free(e);
}
#pragma endregion

void testall()
{
    Image img;
    for(size_t i = 1; i <= 6; i++)
    {
        char text[30] = "../Images_Test/image_0";
        char newName[10] = "";
        char newName2[30] = "result_";
        char nb = i + '0';
        //printf("%d\n", nb);
        insert_substring(text, &nb, 23);
        insert_substring(text, ".jpeg", 24);
        text[28] = '\0';
        printf("Work on : %s\n", text);

        img = load_image(text);
        grayscale(&img);
        canny(&img);

        strncpy(newName, text + 15, 13);
        newName[13] = '\0';
        insert_substring(newName2, newName, 8);

        save_image(&img, newName2);
        free_image(&img);
    }
}
int main(int argc, char **argv)
{
    if(strcmp(argv[1], "all") == 0)
    {
        testall();
        return 0;
    }        
    if(argc != 2)
        errx(1, "Give an image path");
    
    Image img = load_image(argv[1]);

    grayscale(&img);
    //contrast(&img, 128);
    //blur(&img);
    //unsigned int **gradients_dirs = sobel(&img);
    //non_maximum_suppression(&img, gradients_dirs);
    //threashold(&img, gradients_dirs, 110, 120);
    canny(&img);
    save_image(&img, "result.jpg");
    free_image(&img);
    return 0;
}