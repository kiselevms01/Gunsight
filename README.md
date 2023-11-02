# Gunsight
Rendering the sight on the screen based on the received data.
The project was created in Qt creator, version 5.15.2

Short description:
We have two projects: client and server. The sight display parameters are set on the server using sliders and then sent to the client via UDP protocol. 
Receiving and sending data is placed in a separate stream. 
As soon as the data arrives at the client, the sight is displayed in the appropriate coordinates and scale.
