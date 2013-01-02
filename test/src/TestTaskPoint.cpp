/* Copyright_License {

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

#include "Engine/Task/Points/TaskPoint.hpp"
#include "Engine/Navigation/Aircraft.hpp"
#include "Geo/GeoVector.hpp"
#include "TestUtil.hpp"

class DummyTaskPoint: public TaskPoint
{
  AircraftState dummy_state;

public:
  friend class TaskPointTest;

  DummyTaskPoint(TaskPointType _type, const GeoPoint &_location,
                 const fixed _elevation)
    :TaskPoint(_type, _location, _elevation) {}

  virtual GeoVector GetVectorRemaining(const GeoPoint &reference) const {
    return GeoVector();
  }

  virtual GeoVector GetVectorPlanned() const {
    return GeoVector();
  }

  virtual GeoVector GetVectorTravelled() const {
    return GeoVector();
  }

  virtual bool HasEntered() const {
    return false;
  }

  virtual const AircraftState& GetEnteredState() const {
    return dummy_state;
  }

  virtual fixed GetElevation() const {
    return fixed(0);
  }
};

class TaskPointTest
{
public:
  void Run();
};

void
TaskPointTest::Run()
{
  GeoPoint gp1(Angle::Degrees(20), Angle::Degrees(50));
  GeoPoint gp2(Angle::Degrees(21), Angle::Degrees(50));

  DummyTaskPoint tp1(TaskPointType::AST, gp1, fixed(1234));
  DummyTaskPoint tp2(TaskPointType::AAT, gp2, fixed(1337));
  DummyTaskPoint tp3(TaskPointType::START, gp1, fixed(1234));
  DummyTaskPoint tp4(TaskPointType::FINISH, gp2, fixed(1337));

  ok1(tp1.IsIntermediatePoint());
  ok1(tp1.GetType() == TaskPointType::AST);
  ok1(equals(tp1.GetBaseElevation(), 1234));
  ok1(!tp1.HasTarget());
  ok1(equals(tp1.Distance(gp2), gp1.Distance(gp2)));
  ok1(equals(tp1.GetLocation(), gp1));

  ok1(tp2.IsIntermediatePoint());
  ok1(tp2.GetType() == TaskPointType::AAT);
  ok1(tp2.HasTarget());

  ok1(!tp3.IsIntermediatePoint());
  ok1(tp3.GetType() == TaskPointType::START);
  ok1(!tp3.HasTarget());

  ok1(!tp4.IsIntermediatePoint());
  ok1(tp4.GetType() == TaskPointType::FINISH);
  ok1(!tp4.HasTarget());
}

int main(int argc, char **argv)
{
  plan_tests(15);

  TaskPointTest test;
  test.Run();

  return exit_status();
}
