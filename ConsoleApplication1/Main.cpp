#include "stdafx.h"

#define SIZE 32
Array2D<int> Mat(SIZE, SIZE);

int  GetDistance(IntVector2 c0, IntVector2 c1)
{
	int d0 = (c0 - c1).Length2();
	int off = Mat.getWidth();
	int d1 = (c0 - IntVector2(c1.x - off, c1.y)).Length2();
	int d2 = (c0 - IntVector2(c1.x, c1.y - off)).Length2();
	int d3 = (c0 - IntVector2(c1.x + off, c1.y)).Length2();
	int d4 = (c0 - IntVector2(c1.x, c1.y + off)).Length2();
	int mind = std::min(d0, std::min(std::min(d1, d2), std::min(d3, d4)));

	d1 = (c0 - IntVector2(c1.x - off, c1.y - off)).Length2();
	d2 = (c0 - IntVector2(c1.x + off, c1.y - off)).Length2();
	d3 = (c0 - IntVector2(c1.x + off, c1.y + off)).Length2();
	d4 = (c0 - IntVector2(c1.x - off, c1.y + off)).Length2();
	mind = std::min(mind, std::min(std::min(d1, d2), std::min(d3, d4)));
	return mind;
}

void ConvertMatrixToCode(bool _normalized)
{
	std::ofstream File("code.c");
	File << "const " << (_normalized ? "float" : "int") << " DitherMatrix[" << Mat.getWidth() << "][" << Mat.getHeight() << "] = {\n";
	for (int x = 0; x < Mat.getWidth(); x++)
	{
		File << "{";
		for (int y = 0; y < Mat.getHeight(); y++)
		{
			if (_normalized)
				File << (float)Mat[x][y] / (Mat.getWidth() * Mat.getHeight()) << "f";
			else
				File << Mat[x][y];
			if (y != Mat.getHeight() - 1)
				File << ", ";
		}
		if (x != Mat.getWidth() - 1)
			File << "},\n";
		else
			File << "}";
	}
	File << "};";

	File.close();
}

int main()
{
	for (auto & m : Mat)
		m = 0;

	std::mt19937 RandomGenerator;
	std::uniform_real_distribution<float> Random(0, 200);

	for (int i = 1; i < Mat.getWidth() * Mat.getHeight(); i++)
	{
		float dmin = 0;
		IntVector2 cmin;
		for (int x0 = 0; x0 < Mat.getWidth(); x0++)
		{
			for (int y0 = 0; y0 < Mat.getHeight(); y0++)
			{
				if (Mat[x0][y0])
					continue;

				float dmin2 = INT_MAX;
				IntVector2 cmin2;
				for (int x1 = 0; x1 < Mat.getWidth(); x1++)
				{
					for (int y1 = 0; y1 < Mat.getHeight(); y1++)
					{
						if (Mat[x1][y1] == 0)
							continue;

						int d = GetDistance(IntVector2(x0, y0), IntVector2(x1, y1));
						//d += Random(RandomGenerator);
						if (d < dmin2)
						{
							dmin2 = d;
							cmin2 = IntVector2(x0, y0);
						}
					}
				}
				dmin2+=Random(RandomGenerator);

				if (dmin2 < INT_MAX && dmin2 > dmin)
				{
					dmin = dmin2;
					cmin = cmin2;
				}
			}
		}
		Mat[cmin.x][cmin.y] = i;
	}

	ConvertMatrixToCode(true);

	// Display matrix
#if 0
	for (int x = 0; x < Mat.getWidth(); x++)
	{
		for (int y = 0; y < Mat.getHeight(); y++)
		{
			std::string str = std::to_string(Mat[x][y]);
			while (str.size() < 4)
				str.push_back(' ');

			std::cout << str;
		}
		std::cout << std::endl;
	}
#else
	for (int i = 0; i < Mat.getWidth() * Mat.getHeight(); i+=1)
	{
		for (int x = 0; x < Mat.getWidth(); x++)
		{
			for (int y = 0; y < Mat.getHeight(); y++)
			{
				std::string str;
				if (Mat[x][y] < i)
					str = std::to_string(Mat[x][y]);
				while (str.size() < 4)
					str.push_back(' ');

				std::cout << str;
			}
			std::cout << std::endl;
		}
		//system("pause");
		_sleep(100);
		system("cls");
	}
#endif

    return 0;
}

