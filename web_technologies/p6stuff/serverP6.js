//Websocket stuff (using socket.io instead of ws).
var server = require('http').Server();
var io     = require('socket.io')(server,{});
server.listen(5917);
console.log("Server started.");

//Create player "class".
var Player = function(id)
{
    //Player "constructor".
    var self = {
        //Here I am just setting the x, y, z coordinates to a random position so
        //that the two cubes will not overlap when the screen is first
        //rendered.
        x: Math.floor(Math.random()*100)%2? Math.floor(Math.random()*100)%100 :
                                            -Math.floor(Math.random()*100)%100,
        y: Math.floor(Math.random()*100)%2? Math.floor(Math.random()*100)%100 :
                                            -Math.floor(Math.random()*100)%100,
        z:-(Math.floor(Math.random()*Math.floor(1000)))%1000 - 500,
        //No initial rotations.
        x_rot: 0,
        y_rot: 0,
        z_rot: 0,
        //Assign each player/socket a unique id.
        id: id,
        //The following variables determine whether a given button has been
        //pressed for a given player.
        X: false,
        Y: false,
        Z: false,
        W: false,
        A: false,
        S: false,
        D: false,
        E: false,
        C: false
    }

    //Method that determines movement.
    self.Move = function()
    {
        //Set translational and angular speeds.
        var translational_speed = 8;
        var angular_speed       = 0.1;

        //Adjust position according to button pressed.
        if(self.W)
            self.x += translational_speed;
        if(self.A)
            self.x -= translational_speed;
        if(self.S)
            self.y += translational_speed;
        if(self.D)
            self.y -= translational_speed;
        if(self.E)
            self.z += translational_speed;
        if(self.C)
            self.z -= translational_speed;
        if(self.X)
            self.x_rot += angular_speed;
        if(self.Y)
            self.y_rot += angular_speed;
        if(self.Z)
            self.z_rot += angular_speed;
    }

    return self;
}

var players = {};
var sockets = {};

io.sockets.on('connection',
    function(socket)
    {
        //Assign random id to socket/player.
        socket.id = Math.random();
        //Add socket to list of sockets.
        sockets[socket.id] = socket;

        //Create a new instance of player and give it an id.
        var player = Player(socket.id);
        //Add new player to list of players.
        players[socket.id] = player;

        //If a player leaves, disconnect them (ie delete their socket and cube).
        socket.on('disconnect',
            function()
            {
                delete sockets[socket.id];
                delete players[socket.id];
            }
        );

        //If a key press is received from a certain client, choose the
        //appropriate action.
        socket.on('keyPress',
            function(data)
            {
                if(data.inputId === 'X')
                    player.X = data.state;
                else if(data.inputId === 'Y')
                    player.Y = data.state;
                else if(data.inputId === 'Z')
                    player.Z = data.state;
                else if(data.inputId === 'W')
                    player.W = data.state;
                else if(data.inputId === 'E')
                    player.E = data.state;
                else if(data.inputId === 'C')
                    player.C = data.state;
                else if(data.inputId === 'S')
                    player.S = data.state;
                else if(data.inputId === 'A')
                    player.A = data.state;
                else if(data.inputId === 'D')
                    player.D = data.state;
            }
        );
    }
);

//This sets how often to update positions.
setInterval(function()
            {
                //Make an array of all players' attributes.
                var playerInfo = [];
                for(var i in players)
                {
                    var player = players[i];
                    //Update a chosen player's position.
                    player.Move()
                    //Push updated position to list.
                    playerInfo.push(
                    {
                        x:player.x,
                        y:player.y,
                        z:player.z,
                        x_rot: player.x_rot,
                        y_rot: player.y_rot,
                        z_rot: player.z_rot,
                    });
                }
                //Broadcast all player position updates to all sockets.
                for(var i in sockets)
                {
                    var socket = sockets[i];
                    socket.emit('updatePositions', playerInfo);
                }
            }
, 40);