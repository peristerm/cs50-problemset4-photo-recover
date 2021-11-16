#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>


int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("you should put the file name\n");

        return 1;
    }

    FILE *f = fopen(argv[1], "r");

    if (f == NULL)
    {
        printf("file not found\n");
        return 1;
    }


    typedef uint8_t BYTE;
    BYTE buffer[512];

    size_t fileread;


    bool found_first_jpeg = false;
    bool found_jpeg_already = false;
    FILE *jpegfile;
    char filename[8];
    int counter = 0;

    while (true)
    {
        fileread = fread(buffer, sizeof(BYTE), 512, f);

        if (fileread == 0)
        {
            break;
        }
        //check if the file header is a jpg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            found_jpeg_already = true;

            //set found_first_jpeg to true
            if (found_first_jpeg == false)
            {
                found_first_jpeg = true;
            }
            //close the file you have been writing to.
            else
            {

                fclose(jpegfile);
            }

            //name the jpg file
            sprintf(filename, "%03i.jpg", counter);
            //open the new file you are going to continue writing to
            jpegfile = fopen(filename, "w");
            fwrite(buffer, sizeof(BYTE), fileread, jpegfile);
            //increase the counter by 1 to modify the jpg names accordingly
            counter++;
        }

        //if a jpeg file is already found countinue writing
        else if (found_jpeg_already == true)

        {
            fwrite(buffer, sizeof(BYTE), fileread, jpegfile);

        }


    }

    fclose(f);
    fclose(jpegfile);

    return 0;
}
