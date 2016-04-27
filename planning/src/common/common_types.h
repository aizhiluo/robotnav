/*
 * common_types.h
 *
 *  Created on: Jan 28, 2016
 *      Author: rdu
 */

#ifndef SRC_MAP_COMMON_TYPES_H_
#define SRC_MAP_COMMON_TYPES_H_

#include <cstdint>

namespace srcl_ctrl{

typedef struct
{
	uint32_t x;
	uint32_t y;
}Position2D;

typedef struct
{
	uint32_t x;
	uint32_t y;
	uint32_t z;
}Position3D;

enum class OccupancyType
{
	FREE,
	OCCUPIED,
	MIXED,
	INTERESTED
};

typedef struct
{
	uint32_t min;
	uint32_t max;
}Range2D;

typedef struct
{
	Range2D x;
	Range2D y;
}BoundingBox;

}

#endif /* SRC_MAP_COMMON_TYPES_H_ */
