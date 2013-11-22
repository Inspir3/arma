sleep 1;
diag_log "[server/init.sqf] Begin";

//#include "db.sqf"

//call db_create;													//Create schema if doesn't exists

execVM "server\monitoring2.sqf";									//Run main loop

["Server init... OK"] call console_tchat;						//Inform the gamer

diag_log "[server/init.sqf] End";
