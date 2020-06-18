#include <string>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <chrono>
struct Timer
{
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
        void tic() { start = std::chrono::high_resolution_clock::now(); }
	double toc()
	{
		std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start;
		return diff.count() * 1000; //ms
	}
};

int main(int argc, char* argv[]){
	std::string path = "./bgr_out.bmp";
	int resize_height = 360;
	int resize_width = 640;
	cv::Mat src; 
	cv::Mat dst;
	FILE *fp = NULL;
	int ret = 0;

	src=cv::Mat(1440, 2560, CV_8UC3);

	fp = fopen(path.c_str(), "rb");
	if(fp == nullptr)
	{
		printf("open file failed.\n");
		return -1;
	}

	ret =fread(src.data, 1, 2560*1440*3, fp);
	printf("read bytes:%d\n", ret);
	fclose(fp);
	printf("data read ok.\n");
	//imshow("src", src);
	Timer total;

	total.tic();
	cv::resize(src, dst, cv::Size(resize_width, resize_height), (0, 0), (0, 0), cv::INTER_LINEAR);
	printf("HHHHHHHHHHHHHHHHH %s total time: %lf\n", __func__, total.toc());
	printf("resisze ok\n");
	//imshow("dst", dst);

	//cv::waitKey(0);
	return 0;
}
