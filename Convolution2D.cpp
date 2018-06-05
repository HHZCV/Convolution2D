#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat PadZeros(Mat &I) {
	CV_Assert(I.channels() == 1);
	Mat Z = Mat::zeros(I.rows + 2, I.cols + 2, I.type());
	Rect roi(1, 1, I.rows, I.cols);
	Mat ROI(Z, roi);
	I.copyTo(ROI);
	return Z;
}

int main(int argc, char** argv)
{
	
	Mat Kernel;
	Mat I = (Mat_<int>(3, 3) <<  1, 2, 3, 4, 5, 6, 7, 8, 9);
	Mat Image = PadZeros(I);
	
	Kernel = (Mat_<int>(3, 3) << 1, 2, 1, 0, 0, 0, -1, -2, -1);
	cout << "Image is " << "\n" << format(Image, Formatter::FMT_MATLAB) << endl;
	cout << "Kernel is " << "\n" << format(Kernel, Formatter::FMT_MATLAB) << endl;
	int Kernel_halfWidth = (Kernel.rows - 1) / 2;
	Mat resultImage = I.clone();
	
	
	for (int row = 1; row < Image.rows-1; row++) {
		for (int col = 1; col < Image.cols-1; col++) {
			int sum=0;
			for (int i = -Kernel_halfWidth; i < Kernel_halfWidth+1; i++) {
				for (int j = -Kernel_halfWidth; j < Kernel_halfWidth+1; j++) {
					int p = Image.at<int>(row + i, col + j);
					int k = Kernel.at<int>(i + Kernel_halfWidth, j + Kernel_halfWidth);
					sum += (p * k);
				}
				
			}
			resultImage.at<int>(row-1, col-1) = sum;
			
		}
	}
	cout<<"Image after mask is "<<"\n"<< format(resultImage, Formatter::FMT_MATLAB) << endl;
	cin.get();
	return 0;
}


