
sleep 2;							//Wait for addons init

#include "define.sqf";
#include "lib\console.sqf";			//Include debug functions (debug, info)
#include "module\keyboard.sqf";		//Include keyboard handler
#include "module\gps.sqf";			//Include gps functions (setHomeBase)

diag_log "[init.sqf] Begin";

_dllName = "Inspir3";
        
_ret = _dllName callExtension "version";
[format["version: %1", _ret]] call console_both;

_ret = _dllName callExtension "initThread";
[format["initThread: %1", _ret]] call console_both;

if (!isDedicated) then
{
	waitUntil {!isNull player};
	execVM "client\init.sqf";
};

if (isServer) then
{
	execVM "server\init.sqf";
};

diag_log "[init.sqf] End";
