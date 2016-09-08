/*
 * map_config.h
 *
 *  Created on: Aug 1, 2016
 *      Author: rdu
 */

#ifndef PLANNING_SRC_MAP_MAP_CONFIG_H_
#define PLANNING_SRC_MAP_MAP_CONFIG_H_

namespace srcl_ctrl {

enum class MapDataModel {
	SQUARE_GRID,
	QUAD_TREE,
	NOT_SPECIFIED
};

struct MapType {
	MapType():
		data_model(MapDataModel::NOT_SPECIFIED),
		data_param(0){};

	MapType(MapDataModel model, uint32_t param):
		data_model(model),
		data_param(param){};

	MapDataModel data_model;
	uint32_t data_param;
};

class MapConfig{
public:
	MapConfig():
		origin_offset_x(0),
		origin_offset_y(0){};
	~MapConfig()
	{
	};

private:
	std::string map_path_;
	MapType map_type_;
	double origin_offset_x;
	double origin_offset_y;

public:
	void SetMapPath(std::string path)
	{
		map_path_ = path;
	}

	std::string GetMapPath() { return map_path_;}

	void SetMapType(MapDataModel model, uint32_t param)
	{
		map_type_ = MapType(model, param);
	}

	MapType GetMapType() { return map_type_;}

	void SetOriginOffset(double x, double y)
	{
		origin_offset_x = x;
		origin_offset_y = y;
	}

	double GetOriginOffsetX() { return origin_offset_x; }
	double GetOriginOffsetY() { return origin_offset_y; }
};

}

#endif /* PLANNING_SRC_MAP_MAP_CONFIG_H_ */
