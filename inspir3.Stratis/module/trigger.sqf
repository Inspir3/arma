/*
 *  
 */
setTrigger = {

	private ["_trg"];
	
	_trg = createTrigger["EmptyDetector", getPos player];
		_trg setTriggerArea[5,5,0,false];
_trg setTriggerActivation["CIV","PRESENT",true];
_trg setTriggerStatements["this", "hint 'Civilian near player'", "hint 'no civilian near'"]; 	
	
};
