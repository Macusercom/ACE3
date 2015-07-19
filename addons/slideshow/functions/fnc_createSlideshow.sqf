/*
 * Author: Jonpas, DaC
 * Prepares necessary variables and default image.
 *
 * Arguments:
 * 0: Objects <ARRAY>
 * 1: Controller Objects <ARRAY>
 * 2: Image Paths <ARRAY>
 * 3: Action Names <ARRAY>
 * 4: Slide Duration <NUMBER> (0 disables automatic transitions)
 *
 * Return Value:
 * Parsed List <ARRAY>
 *
 * Example:
 * [[object1, object2, object3], [controller1], ["images\image1.paa", "images\image2.paa"], ["Action1", "Action2"], 5] call ace_slideshow_fnc_createSlideshow
 *
 * Public: Yes
 */
//#define DEBUG_MODE_FULL
#include "script_component.hpp"

PARAMS_5(_objects,_controllers,_images,_names,_duration);

// Verify data
if (count _images != count _names || {count _images == 0} || {count _names == 0}) exitWith {
    diag_log "[ACE] ERROR: Slideshow Images or Names fields can NOT be empty and must have equal number of items!"
};

// Objects synced to the module
{
    _objects pushBack _x;
} forEach (synchronizedObjects _logic);

// If no controllers use objects as controllers
if (count _controllers == 0) then {
    _controllers = _objects;
};

TRACE_4("Information",_objects,_controllers,_images,_names);

// Default images on whiteboards (first image)
{
    _x setObjectTextureGlobal [0, _images select 0];
} forEach _objects;

// Number of slideshows (multiple modules support)
GVAR(slideshows) = GVAR(slideshows) + 1;
private ["_currentSlideshow"];
_currentSlideshow = GVAR(slideshows); // Local variable in case GVAR gets changed during execution of below code

// Add interactions if automatic transitions are disabled, else setup automatic transitions
if (_duration == 0) then {
    private ["_actionsObject", "_actionsClass", "_mainAction", "_slidesAction"];
    {
        // Add MainAction if one does not already exist
        _actionsObject = _x getVariable [QEGVAR(interact_menu,actions), []];
        _actionsClass = missionNamespace getVariable [format [QEGVAR(interact_menu,Act_%1), typeOf _x], []];
        if (count _actionsObject == 0 && {count _actionsClass == 0}) then {
            _mainAction = ["ACE_MainActions", localize ELSTRING(interaction,MainAction), "", {}, {true}] call EFUNC(interact_menu,createAction);
            [_x, 0, [], _mainAction] call EFUNC(interact_menu,addActionToObject);
            TRACE_2("Adding ACE_MainActions",_actionsObject,_actionsClass);
        };

        // Add Slides sub-action and populate with images
        _slidesAction = [QGVAR(Slides), localize LSTRING(Interaction), "", {}, {true}, {(_this select 2) call FUNC(addSlideActions)}, [_objects,_images,_names,_x,_currentSlideshow], [0,0,0], 2] call EFUNC(interact_menu,createAction);
        [_x, 0, ["ACE_MainActions"], _slidesAction] call EFUNC(interact_menu,addActionToObject);
    } forEach _controllers;
} else {
    // Formatted GVAR string (multiple modules support)
    private ["_varString"];
    _varString = format [QGVAR(slideshow%1), _currentSlideshow];
    TRACE_1("Current Slide",_varString);

    // Set formatted GVAR to first slide
    missionNamespace setVariable [_varString, 0];

    // Automatic transitions handler
    [FUNC(autoTransition), [_objects, _images, _varString, _duration], _duration] call EFUNC(common,waitAndExecute);
};
