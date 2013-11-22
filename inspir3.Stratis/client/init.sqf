sleep 1;
diag_log "[client/init.sqf] Begin";

//------------------------
//Install keyboard handler
//------------------------
waituntil {!(IsNull (findDisplay 46))};
(findDisplay 46) displayAddEventHandler ["KeyDown", "_this call keyboardHandler"];

diag_log format["[client/init.sqf] Profil name: %1", profileName];

["Client init... OK"] call console_tchat;									//Inform the gamer

diag_log "[client/init.sqf] End";
