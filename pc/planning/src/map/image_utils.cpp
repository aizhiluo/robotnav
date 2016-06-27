/*
 * image_utils.cpp
 *
 *  Created on: Mar 24, 2016
 *      Author: rdu
 */

#include <map/image_utils.h>

using namespace srcl_ctrl;
using namespace cv;

void ImageUtils::BinarizeImage(cv::InputArray _src, cv::OutputArray _dst, uint8_t thresh)
{
	// Prepare data structures
	Mat src = _src.getMat();
	_dst.create(src.size(), CV_8UC1);
	Mat dst = _dst.getMat();

	// Binarize grayscale image
	threshold(src, dst, thresh, 255, THRESH_BINARY);
}

bool ImageUtils::PadImageToSquared(cv::InputArray _src, cv::OutputArray _dst)
{
	// create a image with size of power of 2
	Mat src = _src.getMat();

	unsigned long img_max_side;
	unsigned long padded_size = -1;

	if(src.cols > src.rows)
		img_max_side = src.cols;
	else
		img_max_side = src.rows;

	// find the minimal size of the padded image
	for(unsigned int i = 0; i <= 16; i++)
	{
		if((img_max_side > pow(2,i)) && (img_max_side <= pow(2, i+1)))
		{
			padded_size = pow(2, i+1);
			break;
		}
	}

	if(padded_size == -1)
		return false;

	std::cout << "padded size:" << padded_size << std::endl;
	_dst.create(padded_size, padded_size, CV_8UC1);
	Mat dst = _dst.getMat();

	int left, right, top, bottom;

	left = (dst.cols - src.cols)/2;
	right = dst.cols - src.cols - left;
	top = (dst.rows - src.rows)/2;
	bottom = dst.rows - src.rows - top;

	Scalar value = Scalar(0);
	copyMakeBorder(_src, dst, top, bottom, left, right, BORDER_CONSTANT,value);

	return true;
}

bool ImageUtils::PadImageTo2Exp(cv::InputArray _src, cv::OutputArray _dst)
{
	// create a image with size of power of 2
	Mat src = _src.getMat();

	unsigned long padded_size_x = -1;
	unsigned long padded_size_y = -1;

	// find the minimal size of the padded image
	for(unsigned int i = 0; i <= 16; i++)
	{
		if((src.cols > pow(2,i)) && (src.cols <= pow(2, i+1)))
		{
			padded_size_x = pow(2, i+1);
			break;
		}
	}

	for(unsigned int i = 0; i <= 16; i++)
	{
		if((src.rows > pow(2,i)) && (src.rows <= pow(2, i+1)))
		{
			padded_size_y = pow(2, i+1);
			break;
		}
	}

	if(padded_size_x == -1 || padded_size_y == -1)
		return false;

	_dst.create(padded_size_y, padded_size_x, CV_8UC1);
	Mat dst = _dst.getMat();

	std::cout << "original size: ( " << src.cols << " , " << src.rows << " )" << std::endl;
	std::cout << "padded size: ( " << dst.cols << " , " << dst.rows << " )" << std::endl;

	int left, right, top, bottom;

	left = (dst.cols - src.cols)/2;
	right = dst.cols - src.cols - left;
	top = (dst.rows - src.rows)/2;
	bottom = dst.rows - src.rows - top;

	Scalar value = Scalar(0);
	copyMakeBorder(_src, dst, top, bottom, left, right, BORDER_CONSTANT,value);

	return true;
}

OccupancyType ImageUtils::CheckAreaOccupancy(cv::InputArray _src, BoundingBox area)
{
	Mat src = _src.getMat();

	Range rngx(area.x.min,area.x.max+1);
	Range rngy(area.y.min, area.y.max+1);

	// Attention: Points and Size go (x,y); (width,height) ,- Mat has (row,col).
	Mat checked_area = src(rngy,rngx);

	unsigned long free_points = 0;
	unsigned long occupied_points = 0;
	OccupancyType type;

	for(int i = 0; i < checked_area.cols; i++)
		for(int j = 0; j < checked_area.rows; j++)
		{
			if(checked_area.at<uchar>(Point(i,j)) > 0)
				free_points++;
			else
				occupied_points++;

			if(occupied_points !=0 && free_points != 0)
			{
				type = OccupancyType::MIXED;
				break;
			}
		}

	if(free_points !=0 && occupied_points == 0)
		type = OccupancyType::FREE;

	if(free_points ==0 && occupied_points != 0)
		type = OccupancyType::OCCUPIED;

	return type;
}
