# Network Hero

## About

A multiplier turn-based rpg in the style of the Nintendo and Gamefreak classic series that shall not be named.
Players select a team of "cybers" and then engage in combat until only one player has any cybers left stadning.
Complexity is added through simultaneous action selection, and a fleshed out typing + statistical system. 

The user will see the client-side UI, which will allow them to select a party, and then during battle choose when
to use moves and swap cybers. This will also have display funcionality, and as a stretch goal a visual interface. 
(Command-line based for now).

Stats and what they do:

Attack/Power: determines the damage of the cyber's attacks
Defense: determines how much damage will be negated from attacks and also determines health
S. Attack: Determines the effectiveness of special attacks held by cybers
S. Defense: Determines the amount of resistance held by cyber against opponent S. Attack
Agility: Combination of Speed, Dodge, and Accuracy stats that you would find in other games
Status (attack + resistance): Status stat determines both effectiveness of status attacks as well as resistance to oppenent's status attacks.
Element: Cybers will be typed, there will be 5 elements: fire, water, rock, air, electricity. 
Each type is strong against two other types and weak against the other two types remaining.

Move List: Each Cyber will hold 4 potential moves to draw upon within battle
    - Number of Uses (pp.): each move will have a certain amount of uses, which we will track
    - Effect: Some moves will have status effects (the strength of which will be determined by Status stat)
    - Element: moves will be typed as well, which will modify its effectiveness against opponents of different types.

## Concepts

For the project we will utilize working with the file system for development tools, networking for online play, and
threading for the server which may or may not track game state. 

## Implementation

Multiple Components:
  - Client-side UI
    - Terminal-based
    - ls-style command to list options
    - Then recognize options when typed in, prompting either new menu or sending action to server

      Essentially the UI on the client side is a REPL loop which allows the user to either select an action
      for a list, or ask for the list itself. This is a pretty easy thing to implement, as we just need to run
      a while loop with multiple states for the different levels of menu the user can be in.

  - Client-side network code
    - Use sockets to a server
      
      This is where things get slightly more complicated, as we need to design a complete system for clients to
      communicate with each other and the server. We came up with a couple of approaches, one being the traditional
      server-centric appraoch where the clients send the server their actions for the turn and then the server updates
      the game state and broadcasts it back to the client.

      For this approach we need a way of sending both actions and game state from server to client and client to server.
      Our method is to format the game state as a JSON-like list of cybers, which the client can then turn around and
      display when prompted. For sending an action, it is much more simple as each action only requires an identifier and
      then a parameter if there are multiple options.

      The other system that we thought of is a client-centric model where the clients store the game state and do the game
      math, and the server simply relays the actions on to the opposite client at the right time. In this system both the
      clients and servers send actions only, making the design a little bit simpler. This is the version that we're writing
      about in the rest of the report because it has more pitfalls, so we can make this document longer. We'll probably actually
      go with the server-based design though so that we can use things like random ranges for accuracy.

  - Server-side network code (threaded)
    - Thread for each client
    - Listens for action from each client, when received both send both actions to both clients

      Not too much to write about, just gets input and updates the game state in the server-model or relays information
      in the client model.

  - Game math
    - Client side (for now)
    - Using two actions + game state update into new game state

      Probably the biggest chunk of code. Basically each move will need a hardcoded function, and we'll need to combine
      the various stats in ways that make sense to get results that make sense. Very cool.
  - Design 
    - Balance game somewhat
    - Fun hopefully??

      This'll be hard.

  - Development tools (parsers + tools to make it easier to balance) (maybe stats tracking) (filesystems)
    - Parser for cyber stats file, to assist in development + balancing
    - Parser for move list for similar reasons

      Read plaintext files that are easier for designers to write, change it into c header files. Involves reading
      and writing from the file system.

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

