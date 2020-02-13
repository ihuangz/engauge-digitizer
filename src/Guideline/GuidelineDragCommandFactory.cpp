/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdAbstract.h"
#include "CmdGuidelineMoveXT.h"
#include "CmdGuidelineMoveYR.h"
#include "CmdGuidelineRemoveXT.h"
#include "CmdGuidelineRemoveYR.h"
#include "DocumentModelGuidelines.h"
#include "EngaugeAssert.h"
#include "GuidelineDragCommandFactory.h"
#include "Guidelines.h"
#include "Logger.h"

GuidelineDragCommandFactory::GuidelineDragCommandFactory ()
{
}

CmdAbstract *GuidelineDragCommandFactory::createAfterDrag (MainWindow &mainWindow,
                                                           Document &document,
                                                           const DocumentModelGuidelines &modelGuidelinesDisplay,
                                                           const DocumentModelGuidelines &modelGuidelinesDocument,
                                                           const QString &identifier,
                                                           bool draggedOffscreen)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineDragCommandFactory::GuidelineDragCommandFactory";

  GuidelineValues valuesXDisplay = modelGuidelinesDisplay.valuesX ();
  GuidelineValues valuesXDocument = modelGuidelinesDocument.valuesX ();

  GuidelineValues valuesYDisplay = modelGuidelinesDisplay.valuesY ();
  GuidelineValues valuesYDocument = modelGuidelinesDocument.valuesY ();

  // So which Guideline moved?
  bool useX = true;
  double valueBefore = 0;
  double valueAfter = 0;

  CmdAbstract *cmd = nullptr;

  if (draggedOffscreen) {

    // Delete
    if (useX) {
      cmd = new CmdGuidelineRemoveXT(mainWindow,
                                     document,
                                     identifier,
                                     valueBefore);
    } else {
      cmd = new CmdGuidelineRemoveYR(mainWindow,
                                     document,
                                     identifier,
                                     valueBefore);
    }
  } else {

    // Move
    if (useX) {
      cmd = new CmdGuidelineMoveXT(mainWindow,
                                   document,
                                   identifier,
                                   valueBefore,
                                   valueAfter);
    } else {
      cmd = new CmdGuidelineMoveYR(mainWindow,
                                   document,
                                   identifier,
                                   valueBefore,
                                   valueAfter);
    }
  }

  return cmd;
}
