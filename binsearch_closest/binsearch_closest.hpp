/*
 * Copyright (c) 2014 Tobias Klauser
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 */

#ifndef __BINSEARCH_CLOSEST_HPP__
#define __BINSEARCH_CLOSEST_HPP__

#include <vector>

/** Binary search for the closest value in a vector.
 *
 * This function assumes the vector to be sorted. If the value is outside
 * the range of the vector, it is clamped accordingly. If several elements
 * in the vector are equally close, the first one is returned.
 *
 * @param vec
 *   The sorted vector to search.
 * @param val
 *   Scalar value for which to search the closest element in the vector.
 * @return
 *   Index of the element in the vector that is closest to val or -1 if the
 *   vector contains no elements.
 */
template<typename T>
ssize_t binsearch_closest(const std::vector<T> vec, T val)
{
	// empty vector
	if (vec.size() < 1)
	    return -1;

	// clamp value to range of vector
	if (val < vec.at(0))
		return 0;
	if (val > vec.at(vec.size() - 1))
		return vec.size() - 1;

	size_t imin = 0;
	size_t  imax = vec.size() - 1;
	while (imax - imin > 1) {
		// determine midpoint, prevent integer overflow
		size_t imid = imin + ((imax - imin) / 2);
		if (vec.at(imid) >= val)
			imax = imid;
		else
			imin = imid;
	}

	if (imax - imin == 1 && std::abs(vec.at(imax) - val) < std::abs(vec.at(imin) - val))
		imin = imax;

	return (ssize_t)imin;
}

#endif /* __BINSEARCH_CLOSEST_HPP__ */
