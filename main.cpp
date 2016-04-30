#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostrem>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;
using namespace cv;

int main()
{
	const char *exampleSample = "../mag_tester/probki/SkanyRazem/dokument004.jpg";

	const char *windowName = "probka";

	struct stat sb;

	if(stat(exampleSample, &sb) == -1)
	{
		cout << "File " << exampleSample << " cannot be accessed!";
	}



	return 0;
}
