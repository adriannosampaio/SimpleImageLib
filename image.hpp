#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <stdexcept>
#include <sstream>

namespace SimpleImageLib
{

	const int MAX_CHANNELS = 3;

	namespace internal
	{
		class Pixel
		{
		private:
			float *m_pixelBase;
			int m_nChannels;
		public:
			Pixel(float* pixel, int numChannels) :
				m_pixelBase(pixel),
				m_nChannels(numChannels){}

			float& operator[](int i)
			{
				#ifdef DEBUG
				if(i >= 0 && i < m_nChannels)
				{
					std::stringstream ss;
					ss 	<< "Error trying to access channel "
						<< i << "/" << m_nChannels;
					throw std::out_of_range(ss.str());
				}
				#endif

				return *(m_pixelBase + i);
			}
		};
	

		class Row
		{
		private:
			float *m_rowBase;
			int m_width;
			int m_nChannels;
		public:
			Row(float* rowBase, int width, int numChannels) :
				m_rowBase(rowBase),
				m_width(width),
				m_nChannels(numChannels){}

			internal::Pixel operator[](int i)
			{
				#ifdef DEBUG
				if(i >= 0 && i < m_width)
				{
					std::stringstream ss;
					ss 	<< "Error trying to access column "
						<< i << "/" << m_width;
					throw std::out_of_range(ss.str());
				}
				#endif

				return internal::Pixel(
					m_rowBase + i * m_nChannels, 
					m_nChannels
				);
			}
		};
	}


	/** Class that represents an image in memory, 
	*	independently of the file extension.
	*	It works as an interface with the image data,
	*	allowing the user to manipulate and read the image
	*	pixels as needed
	*
	*/
	class Image
	{
	private:
		
		/** Width of the image
		*/
		int m_width;

		/** Height of the image
		*/
		int m_height;
		
		/** Raw pixel data of the image. All of the components
		*	are placed side-by-side in a one-dimensional array.
		*	For instance, if the image is in RGB mode, the 
		*	memory layout would be:
		*
		*	data = |R1|G1|B1| ... |Ri|Gi|Bi|...|RN|GN|BN|
		*
		*	With N = width * height
		*/
		float *m_data;

		/** Number of pixel channels, e.g.:
		*
		*	- Monochromatic image = 1
		*	- RGB image 		  = 3
		*	- HSV Image  		  = 3
		*/
		int m_numberOfChannels;

	public:

		Image(int width, int height, int nChannels=3) : 
			m_width(width),
			m_height(height),
			m_numberOfChannels(nChannels)
		{
			m_data = new float[width * height]();
		}

		~Image()
		{
			delete[] m_data;
		}

		internal::Row operator[](int i)
		{
			int rowBase = i * m_width;
			return internal::Row(
				m_data + rowBase,
				m_width,
				m_numberOfChannels
			);
		}
	};

}



#endif