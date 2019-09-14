#pragma once

//SMACC
#include <smacc/smacc.h>

//USED ORTHOGNALS
#include <sm_radial_motion/orthogonals/navigation_orthogonal.h>
#include <sm_radial_motion/orthogonals/tool_orthogonal.h>

// USED BEHAVIORS
#include <sm_radial_motion/substate_behaviors.h>

// IMPORTED TEMPLATES-STATE-MACHINES NAMES
#include <sm_radial_motion_waypoints/state_names.h>

// STATE MACHINE CODE
#include <sm_radial_motion_waypoints/radial_motion_waypoints_state_machine.h>

// STATES CODE
#include <sm_radial_motion_waypoints/states/radial_motion_3.h>
#include <sm_radial_motion_waypoints/states/radial_motion_2.h>
#include <sm_radial_motion_waypoints/states/radial_motion_1.h>
#include <sm_radial_motion_waypoints/states/spinning_1.h>
#include <sm_radial_motion_waypoints/states/spinning_2.h>
#include <sm_radial_motion_waypoints/states/spinning_3.h>
