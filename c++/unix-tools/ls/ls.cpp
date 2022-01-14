#include <iostream>
#include <filesystem>
#include <string>

using namespace std;

void list_dirs(string folder_path);

int main(int argc, char *argv[])
{
    string folder_path;

    if (argc > 1)
    {
        folder_path = argv[1];
    } else
    {
        folder_path = ".";
    }

    list_dirs(folder_path);
    return 0;
}



void list_dirs(string folder_path)
{
    int len = 0;
    for(auto& p: filesystem::directory_iterator(folder_path))
    {
        len++;
    }
    cout << len << " files" << endl;
    cout << "----------------------------------------" << endl;

    int counter = 0;
    string *folder_contents = new string [len];
    for(auto& p: filesystem::directory_iterator(folder_path))
    {
        folder_contents[counter] = p.path();
        counter++;
    }


    for(int i = 0; i != len; i++)
    {
        string temp = folder_contents[i];

        if (temp.rfind("./", 0) == 0)
        {
            temp = temp.substr(2);
        }
        cout << temp << endl;
    }
}
