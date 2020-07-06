#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
int n_read = 0;
int n_writ = 0;
// int byte_count = 0;
FILE *pt_img = NULL;

int main(int argc, char *argv[])
{
        if (argc != 2)
        {
            printf("Error: Please input one filename\n");
            return 1;
        }

//store the address of the file they type in, in the variable pt_file. At the address pt_file points to is a FILE,
//hence the word FILE in caps.
FILE *pt_file = fopen(argv[1], "r");

if(pt_file == NULL)
{
    printf("File could not be read\n");
    return 1;
}

//copy file pointer to another called len, so you can use it to find length
//FILE *len = pt_file;

//move pointer to the last byte to find the number of bytes in the file ie. the length
// fseek(len, 0, SEEK_END);
// printf("Length: %ld\n", ftell(len));

// //create a pt_file
// fseek(pt_file, 0, SEEK_SET);

//allocate memory for the name of the string - do this here?
char * out_img = malloc(7);

do // knowing when to end
{
    BYTE * arr = malloc(512);

    //read 512 bytes starting from the address stored in pt_file to an array called arr -
    //will return 1
    n_read = fread(arr, 512, 1, pt_file);

    //if it IS the start of a jpeg, start wrriting to a file
    if (arr[0] == 0xff && arr[1] == 0xd8 && arr[2] == 0xff && (arr[3] & 0xf0) == 0xe0)
    {
        //if it's the start of a new jpeg AND the first
        if (n_writ == 0)
        {
            //What are the elements it counts
            //create a string for the filename which will be used for storing the new image
            sprintf(out_img, "%03i.jpg", 0);

            //create a new file with the name stored at first_image_name for the purposes of writing to it
            //and store the address of this new file in the pointer pt_img
            pt_img = fopen(out_img, "w");

            //write to the new file out_img_name with the the 512 BYTES in the buffer arr
            //keep track of how many jpegs you have with n_writ
            n_writ += fwrite(arr, 512, 1, pt_img);
            //fclose(pt_img);
        }

        //it's a jpeg, but not the first
        else
        {
            fclose(pt_img);
            //jpeg name is the 'last' n_writ ie. the jpeg is named the number of ALREADY WRITTEN files
            sprintf(out_img, "%03i.jpg", n_writ);

            //open a new file, called out_img, and return a pointer to it called pt_img
            pt_img = fopen(out_img, "w");

            //incriment n_writ
            n_writ += fwrite(arr, 512, 1, pt_img);

            //fclose(pt_img);
        }
    }

    //if it's not the start of a jpeg, and if there is a previous jpeg open - we won't incriment n_writ here, naturally
    else if (n_writ != 0)
    {
        fclose(pt_img);
        //open the old image, whose name is a number, but the name variable is stored in out_img
        //return a pointer to it called pt_img
        //printf("%s\n", out_img);
        pt_img = fopen(out_img, "a");

        //fprintf(pt_img,(char*) &arr, arr);
        fwrite(arr, 512, 1, pt_img);
        //fclose(pt_img);

    }
        //printf("position after moving: %ld\n", ftell(pt_file));

       free(arr);

} while (n_read == 1);
        //printf("Number of items written: %i\n", n_writ);
        free(out_img);
        //printf("Bytes read: %i\n", byte_count);
        fclose(pt_file);
}
