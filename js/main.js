var net = require('net');

/*
 * Listening port 8124
 */
var decoder = function(Data){
  console.log('Data: ' + Data);
};


/*
 * Listening port 8124
 */
var listener = function(Socket){
  console.log('Connected.');
  
  Socket.on('end', function() {
    console.log('Disconnected.');
  });
  
  Socket.on('data', decoder);
  
  //c.write('hello\r\n');
  //Socket.pipe(Socket);
};

var server = net.createServer(listener);

server.listen(8124, function() {
  console.log('Listen to port 8124');
  console.log('Waiting for Arma server...');
});
