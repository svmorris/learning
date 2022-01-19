#include <string>
#include <vector>
#include <fstream>
#include <iostream>

// this makes me cry
#include <stdio.h>
#include <errno.h>
#include <cstring>




class AssetPNG
{
public:
    AssetPNG(std::string _file_path): file_path(_file_path)
    {
        _read();
        _verify();
        _get_repored_size();
    }

    ~AssetPNG()
    {
        // Clear and delete the vector
        // to avoid memory leaks
        buffer->clear();
        delete buffer;
    }


private:
    int box_size_x;
    int box_size_y;
    std::string file_path;
    std::vector<unsigned char> *buffer;

    /*
     * Function makes opens and reads a
     * file, handling errors.
     */
    void _read()
    {
        std::ifstream fd(file_path, std::ios::binary);
        if(!fd)
        {
            fprintf(stderr, "Failed to open asset file: '%s'\n", file_path.c_str());
            exit(ENOENT);
        }
        buffer = new std::vector<unsigned char>(std::istreambuf_iterator<char>(fd), {});
        fd.close();
    }

    /*
     * Function checks file-magic
     * to make sure the file loaded
     * is a PNG
     */
    void _verify()
    {
        if ((*buffer)[1] != 'P' || (*buffer)[2] != 'N' || (*buffer)[3] != 'G')
        {
            fprintf(stderr, "ERROR: Asset file is not a png!");
            exit(EINVAL);
        }
    }


    /*
     * Get the size of the png file, as reported
     * by the png headers.
     *
     * Function loops over the contents of
     * the file until it finds the IHDR string.
     * When it does, it takes the next 2 4byte
     * big-endian numbers which will be the
     * pixel sizes of the image.
     * The reported size is put into variables
     * box_size_x and y.
     */
    void _get_repored_size()
    {
        for (int i = 0; i < buffer->size(); i++)
        {
            if((*buffer)[i] == 'I')
            {
                printf("chunk name: %c%c%c%c\n", (*buffer)[i], (*buffer)[i+1], (*buffer)[i+2], (*buffer)[i+3]);
                printf("size x: %x%x%x%x", (*buffer)[i+4], (*buffer)[i+5], (*buffer)[i+6], (*buffer)[i+8]);
                return;
            }
        }
    }

};


int main(int argc, char** argv)
{
    std::string asset_file = argv[1];
    // NOTE: should find a better way of doing this
    AssetPNG(asset_file.c_str());
}
