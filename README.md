# Network Hero

## About

A multiplier turn-based rpg in the style of the Nintendo and Gamefreak classic series that shall not be named.
Players select a team of "cybers" and then engage in combat until only one player has any cybers left stadning.
Complexity is added through simultaneous action selection, and a fleshed out typing + statistical system. 

The user will see the client-side UI, which will allow them to select a party, and then during battle choose when
to use moves and swap cybers. This will also have display funcionality, and as a stretch goal a visual interface. 
(Command-line based for now).

## Concepts

For the project we will utilize working with the file system for development tools, networking for online play, and
threading for the server which may or may not track game state. 

## Implementation

Multiple Components:
  - Client-side UI
    - Terminal-based
    - ls-style command to list options
    - Then recognize options when typed in, prompting either new menu or sending action to server
  - Client-side network code
    - Use sockets to a server
  - Server-side network code (threaded)
    - Thread for each client
    - Listens for action from each client, when received both send both actions to both clients
  - Game math
    - Client side (for now)
    - Using two actions + game state update into new game state
  - Design 
    - Balance game somewhat
    - Fun hopefully??
  - Development tools (parsers + tools to make it easier to balance) (maybe stats tracking) (filesystems)
    - Parser for cyber stats file, to assist in development + balancing
    - Parser for move list for similar reasons
  - Stretch: Add visual UI
    - Use SDL
    - Draw sprites
    - Only if we have time

## Issues with Implemention

Many things could go wrong with this. For one thing, if a client disconnects and then reconnects, the game
states may be out of sync with each other, which could lead to a lot of issues and frustration on the part
of the players. Also, having the game math on the clientside limits design space, as there can't be any
impure functions within the game math due to the game states needing to remain independently synchronized.

Also, writing the UI loop could be tricky, as it's always fairly difficult to deal with random-ass user input.
No Jimmy stop hitting enter. Our design for the communication protocol could also have issues that we don't
see yet that we may have to deal with in the future. Also generally working with networks isn't the smoothest
so there could be numerous issues that pop up there. 

Finally, the biggest thing that could go wrong is that we have no idea if we can even design a fun game. It
would be kinda lame if everything works and the project still sucks so that would be a rough one. Finally,
parsers are pretty fiddily and annoying to write, although we have control over the format so that should alleviate
things somewhat.

