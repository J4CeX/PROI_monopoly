# Board Game Simulator
(name pending)

A Monopoly board game implementation in C++ with Qt.

## Authors
- Jacek Kozakowski
- Stanisław Liszewski
- Mateusz Żmudziński

## Building
Make sure Qt 6 headers are available in the build environment.

```
mkdir build
cd build

cmake ..

make
```

If Qt is not in the user's path, adding something like `-DCMAKE_PREFIX_PATH=/absolute/path/to/qt` to the CMake command may be necessary.

## Simulation assumptions
- Game state will be saved and may be restored from a file
- Qt GUI with Qt Widgets and QtGraphicsView will be used as a user interface
- A library will be used for processing game files (in formats such as YAML or JSON)
- A subset of "Monopoly Classic" rules will be implemented
	- GUI won't implement auctions
	- Only base rules (no "Short Game" or "Time Limit Game" modes)
	- No mortgage or property deed cards, ownership of fields indicated directly
- All actions will be separately logged in a log window and saved to a log file
- A user can have at most one of "Get out of jail free" cards; the amount of these card is unlimited

## Overview of class hierarchy
### `Field`
A `Field` abstract class represents a single field on the playing board, and has an ID positioning it and a name.

`OwnableField` is its abstract subclass, representing any field that can be purchased by the players. This requires fields for:
- the owner
- the purchase price
- mortgage status
- rent (when non-owner passes it).

`Street` is a subclass of `OwnableField`. It stores the amount of houses built on it. `Station` and `Utility` are also "ownable".

`EventField` is also an abstract subclass, with `ChanceField` and `CommunityChestField` inheriting from it. This is necessary to select the correct card stack to randomize from.

Other field types are `Jail`, `GoToJail`, `Parking`, which have unique behaviors.

`FinancialField` is another subclass, which changes the player's balance.

### `Player`
The `Player` class represents a player of the game.

`name` and `pawn` fields can be chosen by the users in the GUI when starting a new game.

`balance` represents the current balance of the player; it can be negative during a round, indicating the need to auction or mortgage. Only if the player can't eliminate the deficit, are they declared `isBankrupt` and omitted from next rounds.

`position` stores the field the player is on, `inJailRounds` counts the remaining number of rounds the player spends in jail, and `hasGetOutOfJailCard` represents the player having "Get out of jail free" card.

### `EventContainer` and `EventCard`
`EventContainer` is a container storing `EventCard`s: "Community Chest" or "Chance" cards.

The `EventCard` is either:
- a payment to/from the bank
- a payment to/from all other players
- a movement to a specified field
- a movement delta-fields
- a "Get out of jail free" card

Movement cards can have extra instructions, like rolling the dice, bank payment cards can require calculating an amount based on the number of properties owned by the player.

### Supporting classes
`File`, `InFile`, `OutFile`, `Menu` are supporting classes working with loading and saving game state to files, and initializing objects.

`Game` processes the "business logic" of the game and stores references to other objects.

GUI may require additional classes, as required by the Qt framework.
