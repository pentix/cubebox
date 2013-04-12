CubeBox Multiplayer Protocol V1.1
---------------------------------


The TCP protocol section:


The TCP protocol is only used, where it really matters to send correct data.
(You probably don't want to have random-spawning blocks on your server?)
An request has a char array with 4 bytes as the header (means: without a '\0')
Login/Logout and Block changes are sent over TCP using the commands.

The response is just raw data. Depending on the first 2 bytes (a char array)
the response is smaller or bigger. The `AWAY` request doesn't require a response.


**
`USER` command - to log in

Bytes 0:		0x47
Bytes 1..25:	$Username
Bytes 26..40:	$Passwort

41 bytes need to be sent to login.

Returns:
1 Byte: 0x41 //Error
or
13 Bytes: 0x22 (float)Px (float)Py (float)Pz
**

`MAP` command - to get a cube
Bytes 0			0x33
Bytes 1..4:		$cube_x			Float
Bytes 5..8:		$cube_y			Float
Bytes 9..12:	$cube_z			Float

Returns:
1 Byte 0x40
or
8193 Bytes 0x43 (2*16*16*16)$block_types

**

`BSET` command - to set a block

Bytes 0			0x26
Bytes 1..4:		$block_type			Unsigned Short
Bytes 5..8:		$block_x			Float
Bytes 9..12:	$block_y			Float
Bytes 13..16:	$block_z			Float

17 bytes need to be sent to set a block.

Returns:
1 Byte 0x49
or
1 Byte: 0x21 //OK
**


`BREM` command - to remove an existing block

Bytes 0:		0x25
Bytes 1..4:		$block_x			Float
Bytes 5..8:		$block_y			Float
Bytes 9..12:	$block_z			Float

13 bytes need to be sent to remove an existing block.

Returns:
1 Byte: 0x45//Error
or
1 Byte: 0x24
**


`AWAY` command - to log out

Bytes 0:		0X46

1 byte need to be sent to log out.

Returns:
NOTHING
**




The UDP protocol section:

The UDP protocol is used everywhere, where the TCP control would take too
long, or cause too much traffic. We mainly use it for sending the player's
position. To reduce the traffic to the absolute minimum, this is a
one-direction protocol only, we send but we don't receive. The amount
of data we send, depends on what command we send.


**
`P` command - to send the new x position of the player to the server
We don't send every time the whole position, we only send the new
absolute position coordinates of those axis we moved on.
NOTE: We can't send only the differences! On UDP we might have
trouble because the bytes sent, are not checked at the other side.
If we would say we moved one forward and the server would understand
we moved 3 forward, we would always have a difference of 2.

Bytes 0..3:		$UserID				Integer
Bytes 4..7:		$pos_abs[x]			Float
Bytes 8..11:	$pos_abs[y]			Float
Bytes 12..15:	$pos_abs[z]			Float

16 bytes need to be sent to set a new position of a player.
**




*************************
*		EXAMPLE:		*
*************************

When logging on on the server, the client receives 5*5*5 so-called
cubes of the world around his spawning position. A cube is 16*16*16 
blocks. The server only needs to send 14 bytes for each block.
14 * (5*5*5  *  16*16*16)  =  7'168'000	Bytes
						   ~  7.2 		Megabytes
						  ____________________________
						  ----------------------------

In order to reduce this traffic, we could send the data in an order
so we don't have to send the coordinates of each block. This would
change the amount of traffic to only 2 bytes for each block.
2 * (5*5*5  *  16*16*16)   =  1'024'000	Bytes
						   ~  1 		Megabyte
						  ____________________________
						  ----------------------------

Additionally we could reduce the numbers of cubes to be sent to the
client. We would have to tell the client the size of the world first,
to send him the data in an specified order.

REMEMBER: Most of internet connections today are really fast.
It doesn't matter if you have to wait 3 or 7 seconds until the game
is loaded, but it really matters if you can only see 50 meters.
So don't configure the server too traffic-saving!
