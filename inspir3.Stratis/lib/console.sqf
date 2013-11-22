/*
 * Print a message on tchat
 */
console_tchat = {
	private ["_text"];

	_text = _this select 0;

	//hint format["Touche %1 appuyée", _key];
	//titleText [_text, "PLAIN DOWN"];  		
	
	player sideChat _text;
};


/*
 * Print a message on tchat and into log file
 */
console_both = {
	private ["_text"];

	_text = _this select 0;
	
    [_text] call console_tchat;
	diag_log _text;
};

