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

#ifndef XCSOAR_TASK_PROPERTIES_PANEL_HPP
#define XCSOAR_TASK_PROPERTIES_PANEL_HPP

#include "Widget/RowFormWidget.hpp"
#include "Form/DataField/Listener.hpp"
#include "Engine/Task/TaskBehaviour.hpp"

class TaskManagerDialog;
class OrderedTask;
class DataFieldBoolean;
class DataFieldEnum;

class TaskPropertiesPanel : public RowFormWidget,
                            private DataFieldListener {
  TaskManagerDialog &dialog;

  OrderedTask **ordered_task_pointer, *ordered_task;
  bool *task_changed;

  TaskFactoryType orig_taskType;

public:
  TaskPropertiesPanel(TaskManagerDialog &_dialog,
                      OrderedTask **_active_task, bool *_task_modified);

  void OnFAIFinishHeightChange(DataFieldBoolean &df);
  void OnTaskTypeChange(DataFieldEnum &df);

  /* virtual methods from Widget */
  virtual void Prepare(ContainerWindow &parent, const PixelRect &rc);
  virtual void ReClick();
  virtual void Show(const PixelRect &rc);
  virtual void Hide();

  /**
   * Saves the panel's properties of the task to the temporary task
   * so they can be used by other panels editing the task.
   * @return true
   */
  virtual bool Leave();

protected:
  void RefreshView();
  void ReadValues();

private:
  /* virtual methods from DataFieldListener */
  virtual void OnModified(DataField &df);
};

#endif
