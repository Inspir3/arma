#include "define.sqf";

disableSerialization;

private ["_dialog", "_buttonSetHomeBase", "_homeBaseExists"];

_dialog = findDisplay DIALOG_main;								//get controls objects
_buttonSetHomeBase = _dialog displayCtrl BUTTON_setHomeBase;

_homeBaseExists = call homeBaseAlreadyExists;

_buttonSetHomeBase ctrlShow !_homeBaseExists;					//Show or hide the button "Set home base"
