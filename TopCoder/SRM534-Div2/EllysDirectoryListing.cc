#include <vector>
#include <string>

using namespace std;

class EllysDirectoryListing {
    private:

    public:
        vector <string> getFiles(vector <string> files)
        {
            int n = files.size();
            if (files[n - 1] == "." || files[n - 1] == "..")
                if (files[n - 2] == "." || files[n - 2] == "..")
                    return files;

            for (int i = 0; i < n; i++)
                if (files[i] == "." || files[i] == "..") {
                    swap(files[i], files[n - 1]);
                    break;
                }

            if (files[n - 1] == "." || files[n - 1] == "..")
                if (files[n - 2] == "." || files[n - 2] == "..")
                    return files;

            for (int i = 0; i < n; i++)
                if (files[i] == "." || files[i] == "..") {
                    swap(files[i], files[n - 2]);
                    break;
                }

            return files;
        }
};
