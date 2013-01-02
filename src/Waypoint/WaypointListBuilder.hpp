/*
Copyright_License {

  XCSoar Glide Computer - http://www.xcsoar.org/
  Copyright (C) 2000-2013 The XCSoar Project
  A detailed list of copyright holders can be found in the file "AUTHORS".

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
}
*/

#ifndef XCSOAR_WAYPOINT_LIST_BUILDER_HPP
#define XCSOAR_WAYPOINT_LIST_BUILDER_HPP

#include "Geo/GeoPoint.hpp"
#include "Engine/Task/Shapes/FAITrianglePointValidator.hpp"
#include "Engine/Waypoint/WaypointVisitor.hpp"

struct WaypointFilter;
class WaypointList;
class Waypoints;
struct Waypoint;

class WaypointListBuilder:
  public WaypointVisitor
{
  const WaypointFilter &filter;
  const GeoPoint location;
  WaypointList &list;
  FAITrianglePointValidator triangle_validator;

public:
  WaypointListBuilder(const WaypointFilter &_filter,
                        GeoPoint _location, WaypointList &_list,
                        OrderedTask *ordered_task, unsigned ordered_task_index)
    :filter(_filter), location(_location), list(_list),
     triangle_validator(ordered_task, ordered_task_index) {}

  void Visit(const Waypoints &waypoints);
  void Visit(const Waypoint &waypoint);
};



#endif
