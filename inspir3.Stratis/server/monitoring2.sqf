
sleep 3;
["[monitoring] In progress..."] call console_tchat;

_dllName = "Inspir3";

_ret = _dllName callExtension "gna";
[format["gna: %1", _ret]] call console_both;

sleep 2;
      
_ret = _dllName callExtension "exitThread";
[format["exitThread: %1", _ret]] call console_both;
  