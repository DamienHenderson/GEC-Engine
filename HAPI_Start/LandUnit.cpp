#include "LandUnit.hpp"


#include "TileDefinition.hpp"
#include "TileMap.hpp"

#include <set>
#include <unordered_set>
#include <map>

struct pathfind_node
{
	vec2<s32> pos, came_from;
	s32 weight;

	bool operator == (const pathfind_node& other) const
	{
		return pos == other.pos && weight == other.weight;
	}

	bool operator != (const pathfind_node& other) const
	{
		return !(*this == other);
	}

	bool operator < (const pathfind_node& other) const
	{
		return weight < other.weight;
	}

	bool operator <= (const pathfind_node& other) const
	{
		return *this < other || *this == other;
	}
	bool operator > (const pathfind_node& other) const
	{
		return weight > other.weight;
	}

	bool operator >= (const pathfind_node& other) const
	{
		return *this > other || *this == other;
	}
};

std::ostream& operator << (std::ostream& os, const pathfind_node& node)
{
	os << "Position: " << node.pos << "Came From: " << node.came_from << " Cost: " << node.weight;
	return os;
}

LandUnit::LandUnit()
{
}


LandUnit::~LandUnit()
{
}

void LandUnit::Pathfind(vec2<f32> destination, TileMap & tilemap)
{


	// A* algorithm here
	// needs to find the current chunk the unit is in and the chunk the destination is in
	// could be done with a point to chunk(possibly think of better name) function in the tilemap then finding the tile which the two points are contained within
	// then working from there
	// could make this more efficient / 'realistic' by only pathfinding around 10 tiles ahead to simulate the unit not being able to see very far ahead and also improve performance.


	// this took me far too long to write
	// goal = destination;

	vec2<s32> goal_tile = { (s32)floorf(destination.x) / tile_width, (s32)floorf(destination.y) / tile_height };


	TileDefinition goal_def = tilemap.GetTileDefinition(destination);

	vec2<s32> start_tile = { (s32)floorf(position_.x) / tile_width, (s32)floorf(position_.y) / tile_height };

	if (!goal_def.valid || !goal_def.passable)
	{
		return;
	}


	
	std::priority_queue <pathfind_node, std::vector<pathfind_node>, std::greater<pathfind_node>> frontier;
	// first = tile, second = came from
	std::list<vec2<s32>> visited;

	std::unordered_map<vec2<s32>, vec2<s32>, vec2_hash<s32>> came_from;
	std::unordered_map<vec2<s32>, s32, vec2_hash<s32>> cost;


	frontier.push({ start_tile, start_tile, 0 });

	
	while (!frontier.empty())
	{
		pathfind_node lowest = frontier.top();
		

		frontier.pop();

		visited.push_back(lowest.pos);

		const vec2<s32> neighbours[4] = { { lowest.pos.x, lowest.pos.y - 1 },{ lowest.pos.x, lowest.pos.y + 1 },{ lowest.pos.x + 1, lowest.pos.y },{ lowest.pos.x - 1, lowest.pos.y } };



		pathfind_node neighbour_nodes[4];

		for (int i = 0; i < 4; i++)
		{
			

			if (!tilemap.PointIsInTileMap({ (f32)(neighbours[i].x * tile_width), (f32)(neighbours[i].y * tile_height) }))
			{
				continue;
			}

			
			if (neighbours[i] == goal_tile)
			{
				came_from[neighbours[i]] = lowest.pos;
				std::cout << "found goal at: " << goal_tile << "\n";
				waypoints_.clear();
				
				
						vec2<s32> current = goal_tile;

						while (current != start_tile)
						{
							vec2<f32> waypoint{ (f32)current.x * tile_width, (f32)current.y * tile_height };
							std::cout << "Adding waypoint at: " << waypoint << "\n";
							waypoints_.push_front(waypoint);

							current = came_from[current];
						}
						return;
					
					
				
				
				std::cout << "Finished creating waypoints\n";
				return;
			}
			neighbour_nodes[i] = { neighbours[i], lowest.pos, AStarWeight(goal_tile, neighbours[i], tilemap) + lowest.weight };

			std::cout << "Checking: " << neighbours[i] << "\n";

			TileDefinition def = tilemap.GetTileDefinition({ (f32)neighbours[i].x * tile_width, (f32)neighbours[i].y * tile_height });
			if (!def.passable || !def.valid)
			{
				continue;
			}

			
			if (std::find(visited.begin(), visited.end(), neighbours[i]) != visited.end())
			{
				if (neighbour_nodes[i].weight < cost[neighbours[i]])
				{
					cost[neighbours[i]] = neighbour_nodes[i].weight;
					came_from[neighbours[i]] = neighbour_nodes[i].came_from;
					
				}

				continue;
			}
			else
			{
				
				
				

				frontier.push(neighbour_nodes[i]);
				


			}

			s32 better_path_check = lowest.weight + ((s32)abs(lowest.pos.x - neighbours[i].x) + (s32)abs(lowest.pos.y - neighbours[i].y));

			if (better_path_check >= neighbour_nodes[i].weight)
			{
				continue;
			}

			came_from[neighbours[i]] = lowest.pos;
			cost[neighbours[i]] = neighbour_nodes[i].weight;

			

			// closed.push_back(best.pos);

			
			

			visited.push_back(neighbours[i]);
		}

		// closed.push_back(lowest.pos);
		/*
		for (auto& it : came_from)
		{
			std::cout << it << "\n";
		}
		*/
		
	}
	/*
	PathFind(position_, tilemap, path, visited, goal_found);
	*/







}

