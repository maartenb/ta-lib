/* TA-LIB Copyright (c) 1999-2003, Mario Fortier
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 *
 * - Neither name of author nor the names of its contributors
 *   may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*********************************************************************
 * This file contains only TA functions starting with the letter 'L' *
 *********************************************************************/
#include <stddef.h>
#include "ta_abstract.h"
#include "ta_def_ui.h"

/* Follow the 3 steps defined below for adding a new TA Function to this
 * file.
 */

/****************************************************************************
 * Step 1 - Define here the interface to your TA functions with
 *          the macro DEF_FUNCTION.
 *
 ****************************************************************************/

/* LINEARREG BEGIN */
static const TA_InputParameterInfo    *TA_LINEARREG_Inputs[]    =
{
  &TA_DEF_UI_Input_Real,
  NULL
};

static const TA_OutputParameterInfo *TA_LINEARREG_Outputs[]   =
{
  &TA_DEF_UI_Output_Real,
  NULL
};

static const TA_OptInputParameterInfo *TA_LINEARREG_OptInputs[] =
{ &TA_DEF_UI_TimePeriod_14_MINIMUM2,
  NULL
};

DEF_FUNCTION( LINEARREG,           /* name */
              TA_GroupId_Statistic,/* groupId */
              "Linear Regression", /* hint */
              NULL,                /* helpFile */
              TA_FUNC_FLG_OVERLAP, /* flags */
              NULL                 /* analysis function */
             );
/* LINEARREG END */

/* LINEARREG_SLOPE BEGIN */
static const TA_InputParameterInfo    *TA_LINEARREG_SLOPE_Inputs[]    =
{
  &TA_DEF_UI_Input_Real,
  NULL
};

static const TA_OutputParameterInfo *TA_LINEARREG_SLOPE_Outputs[]   =
{
  &TA_DEF_UI_Output_Real,
  NULL
};

static const TA_OptInputParameterInfo *TA_LINEARREG_SLOPE_OptInputs[] =
{ &TA_DEF_UI_TimePeriod_14_MINIMUM2,
  NULL
};

DEF_FUNCTION( LINEARREG_SLOPE,     /* name */
              TA_GroupId_Statistic,/* groupId */
              "Linear Regression Slope", /* hint */
              NULL,                /* helpFile */
              0,                   /* flags */
              NULL                 /* analysis function */
             );
/* LINEARREG_SLOPE END */

/* LINEARREG_ANGLE BEGIN */
static const TA_InputParameterInfo    *TA_LINEARREG_ANGLE_Inputs[]    =
{
  &TA_DEF_UI_Input_Real,
  NULL
};

static const TA_OutputParameterInfo *TA_LINEARREG_ANGLE_Outputs[]   =
{
  &TA_DEF_UI_Output_Real,
  NULL
};

static const TA_OptInputParameterInfo *TA_LINEARREG_ANGLE_OptInputs[] =
{ &TA_DEF_UI_TimePeriod_14_MINIMUM2,
  NULL
};

DEF_FUNCTION( LINEARREG_ANGLE,           /* name */
              TA_GroupId_Statistic,/* groupId */
              "Linear Regression Angle", /* hint */
              NULL,                /* helpFile */
              0,                   /* flags */
              NULL                 /* analysis function */
             );
/* LINEARREG_ANGLE END */

/* LINEARREG_INTERCEPT BEGIN */
static const TA_InputParameterInfo    *TA_LINEARREG_INTERCEPT_Inputs[]    =
{
  &TA_DEF_UI_Input_Real,
  NULL
};

static const TA_OutputParameterInfo *TA_LINEARREG_INTERCEPT_Outputs[]   =
{
  &TA_DEF_UI_Output_Real,
  NULL
};

static const TA_OptInputParameterInfo *TA_LINEARREG_INTERCEPT_OptInputs[] =
{ &TA_DEF_UI_TimePeriod_14_MINIMUM2,
  NULL
};

DEF_FUNCTION( LINEARREG_INTERCEPT,           /* name */
              TA_GroupId_Statistic,/* groupId */
              "Linear Regression Intercept", /* hint */
              NULL,                /* helpFile */
              TA_FUNC_FLG_OVERLAP, /* flags */
              NULL                 /* analysis function */
             );
/* LINEARREG_INTERCEPT END */

/****************************************************************************
 * Step 2 - Add your TA function to the table.
 *          Order is not important. Must be NULL terminated.
 ****************************************************************************/
const TA_FuncDef *TA_DEF_TableL[] =
{
   ADD_TO_TABLE(LINEARREG),
   ADD_TO_TABLE(LINEARREG_SLOPE),
   ADD_TO_TABLE(LINEARREG_ANGLE),
   ADD_TO_TABLE(LINEARREG_INTERCEPT),
   NULL
};


/* Do not modify the following line. */
const unsigned int TA_DEF_TableLSize =
              ((sizeof(TA_DEF_TableL)/sizeof(TA_FuncDef *))-1);


/****************************************************************************
 * Step 3 - Make sure "gen_code" is executed for generating all other
 *          source files derived from this one.
 *          You can then re-compile the library as usual and you are done!
 ****************************************************************************/
