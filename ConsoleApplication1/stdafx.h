// stdafx.h : fichier Include pour les fichiers Include système standard,
// ou les fichiers Include spécifiques aux projets qui sont utilisés fréquemment,
// et sont rarement modifiés
//

#pragma once

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <random>

#include "Vector2.h"
#include "Array2D.h"

struct Color
{
	Color() {};
	Color(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a) : r(_r), g(_g), b(_b), a(_a) {};
	uint8_t r,g,b,a;
};
