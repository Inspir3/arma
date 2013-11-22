
var players = Array();

/*
 * Constructor
 */
function Player() { 
	this.id = 0;
	this.uid = "";
	this.pseudo = "";
}

/*
 * Display player information
 */
Player.prototype.toString = function(){
  return this.pseudo + " (" + this.id + ")";
};

//--------------------------------------------------
// SQF INTERFACE
//--------------------------------------------------

/*
 * Add a player
 */
function player_add(Id, UID, Pseudo){

	var player 		= new Player();
	player.id 		= Id;
	player.uid 		= UID;
	player.pseudo 	= Pseudo;
	
	players.push(player);
}

/*
 * Is player exists ?
 */
function player_exists(UID){

	for(var i=0;i<players.length;i++) if (players[i].uid == UID) return players[i].id;
	
	return 0;
}
